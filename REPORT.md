## Feature 2: Multi-file Build

# Operating Systems – Programming Assignment 01 Report

## Feature 2: Multi-file Project using Make Utility

### Q1. Explain the linking rule `$(TARGET): $(OBJECTS)`. How does it differ from a rule that links against a library?

In my `src/Makefile`, the linking rule is:

    $(TARGET): $(OBJECTS)
    	$(CC) $(OBJECTS) -o $@

Here, `$(TARGET)` is `../bin/client` and `$(OBJECTS)` is the list of object files
(`main.o`, `mystrfunctions.o`, `myfilefunctions.o`). The rule means: "to build
`client`, all these object files must exist first. If any of them is newer than
`client`, run the link command again." The linker takes all the object files and
joins them into one executable. The code of every function is copied into `client`.

In this rule, the program depends directly on each individual object file.
In a rule that links against a library, the executable depends on the library file
instead (for example `libmyutils.a`), and the link command uses special flags:

    $(TARGET): main.o $(LIB_DIR)/libmyutils.a
    	$(CC) main.o -L$(LIB_DIR) -lmyutils -o $@

- `-L` tells the linker which folder to search for libraries.
- `-l` tells it which library to use (`-lmyutils` means `libmyutils.a` or `libmyutils.so`).

So the main difference is: in Feature 2 we link our own object files directly, while
with a library, the functions are first packed into a library file, and the linker
picks only the needed code from that library.

### Q2. What is a git tag and why is it useful? What is the difference between a simple tag and an annotated tag?

A git tag is a permanent name given to one specific commit, like a bookmark.
Branches keep moving forward when new commits are added, but a tag always points
to the same commit. Tags are mainly used to mark versions, such as `v0.1.1-multifile`.
They are useful because we can always go back to the exact code of a version, compare
versions, and create releases from them.

- **Lightweight (simple) tag:** only a name that points to a commit. It stores no extra
  information. Created with `git tag v1.0`.
- **Annotated tag:** a full git object that stores the tagger's name, email, date, and
  a message. Created with `git tag -a v1.0 -m "message"`. It can be viewed with
  `git show v1.0`.

Annotated tags are recommended for releases because they record who created the
version, when, and why.

### Q3. What is the purpose of a GitHub Release? What is the significance of attaching binaries?

A GitHub Release is built on top of a git tag. It gives a version a title, a
description (release notes), and downloadable files. It is the official way to
publish a stable version of a project for users.

Attaching binaries such as the `client` executable means users can download and run
the program directly, without installing a compiler or building the source code
themselves. It also keeps the repository clean: the git repository stores only source
code (build outputs are ignored using `.gitignore`), while compiled files are
distributed through releases.

## Feature 3: Creating and Using a Static Library

### Q1. Compare the Makefile from Part 2 and Part 3. What are the key differences in the variables and rules that enable the creation of a static library?

In Part 2, the Makefile had one list of object files (`OBJECTS`) containing
`main.o`, `mystrfunctions.o` and `myfilefunctions.o`, and one rule linked all of them
directly into `bin/client`.

In Part 3, the Makefile was changed in these ways:

- **Object files are split into two groups:** `LIB_OBJS` (the library code:
  `mystrfunctions.o`, `myfilefunctions.o`) and `MAIN_OBJ` (`main.o`, the program).
- **New variables for the library:** `AR = ar`, `ARFLAGS = rcs`, `RANLIB = ranlib`,
  `LIB_DIR = ../lib`, `LIB_NAME = myutils`, and `STATIC_LIB = $(LIB_DIR)/libmyutils.a`.
- **A new rule to create the archive:**

      $(STATIC_LIB): $(LIB_OBJS)
      	$(AR) $(ARFLAGS) $@ $^
      	$(RANLIB) $@

  It bundles all library object files into `libmyutils.a`. `$^` means all dependencies.
- **A changed linking rule:**

      $(TARGET): $(MAIN_OBJ) $(STATIC_LIB)
      	$(CC) $(MAIN_OBJ) -L$(LIB_DIR) -l$(LIB_NAME) -o $@

  Only `main.o` is linked directly. The library is linked using `-L` (the folder to
  search for libraries) and `-l` (the library name). The target depends on the library
  file, so if the library changes, the program is relinked.
- The object files must come **before** the library in the link command, because the
  linker reads files from left to right and only takes code from an archive that is
  needed by files it has already seen.

### Q2. What is the purpose of the `ar` command? Why is `ranlib` often used immediately after it?

`ar` (archiver) combines several object files into one archive file, which is a static
library (`.a`). I used `ar rcs lib/libmyutils.a mystrfunctions.o myfilefunctions.o`:

- `r` inserts the object files into the archive (replaces them if they already exist),
- `c` creates the archive if it does not exist,
- `s` writes a symbol index.

`ar -t lib/libmyutils.a` lists the members of the archive, which in my case are
`mystrfunctions.o` and `myfilefunctions.o`.

`ranlib` creates an index (symbol table) inside the archive. The index tells the linker
which object file contains which function, so the linker can find symbols quickly
without searching every object file. In older systems, `ar` did not create this index,
so `ranlib` had to be run after it. Modern `ar` creates the index with the `s` option,
so `ranlib` is not strictly needed, but it is still commonly used for compatibility.

### Q3. When you run `nm` on `client_static`, are symbols like `mystrlen` present? What does this tell you about how static linking works?

Yes. Running `nm bin/client_static` shows:

    00000000000016e3 T mystrlen
    0000000000001723 T mystrcpy
    000000000000179d T mystrncpy
    000000000000183c T mystrcat
    0000000000001a23 T mygrep

The letter `T` means the function is defined in the text (code) section of the
executable. In comparison, `nm obj/main.o` shows `U mystrlen`, which means `main.o`
only uses the function but does not contain its code.

This shows that in static linking, the linker copies the machine code of the needed
functions from the library into the executable at build time. The addresses also
changed: in `mystrfunctions.o`, `mystrlen` was at address `0`, but in the executable
it is at `0x16e3`, because the linker assigned final addresses (relocation).

As a result, `client_static` does not need `libmyutils.a` to run. This is confirmed by
`ldd bin/client_static`, which does not list `libmyutils` at all. Only the standard C
library (`libc.so.6`) is still linked dynamically, because gcc links the C library
dynamically by default.
