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

## Feature 4: Creating and Using a Dynamic Library

### Q1. What is Position-Independent Code (-fPIC) and why is it a fundamental requirement for creating shared libraries?

Position-Independent Code (PIC) is machine code that runs correctly no matter at which
memory address it is loaded. The `-fPIC` flag tells gcc to generate such code.

A shared library can be loaded at a different address in every process that uses it.
I observed this directly: in two runs of `ldd bin/client_dynamic`, `libmyutils.so` was
loaded at `0x725fc0bb6000` and then at `0x7807766fa000`. Linux randomizes these
addresses on every run (Address Space Layout Randomization, ASLR).

If the library contained fixed (absolute) addresses, the dynamic loader would have to
modify the code for each process, so every process would need its own modified copy,
and the code could not be shared in memory. With PIC, the code uses addresses relative
to the current instruction, and calls to external functions and accesses to global data
go through a table called the Global Offset Table (GOT). At run time, the loader only
fills in this table, and the code itself is never changed. Because of this, one copy
of the library's code in RAM can be shared by many processes at the same time, which
is the main purpose of a shared library.

I also tried building the shared library from object files compiled without `-fPIC`,
and on my system (Ubuntu) it still linked. This is because modern Ubuntu gcc generates
position-independent code by default (it builds PIE executables). On systems where
this is not the default, the linker refuses and asks to "recompile with -fPIC".
Therefore `-fPIC` is still used explicitly, so the build is correct on any system.

In my Makefile, only the library object files are compiled with `-fPIC`, using the
target-specific variable `$(LIB_OBJS): CFLAGS += $(PICFLAGS)`. `main.o` does not need it.

### Q2. Explain the difference in file size between your static and dynamic clients. Why does this difference exist?

Output of `ls -lh bin/` and `size`:

| File | Size on disk | text (code) section |
|---|---|---|
| `client_static` | 24K | 5868 bytes |
| `client_dynamic` | 20K | 4231 bytes |

`client_static` is larger because at build time the linker copied the machine code of
`mystrlen`, `mystrcpy`, `mystrncpy`, `mystrcat`, `wordCount` and `mygrep` from
`libmyutils.a` into the executable. `nm` shows these functions as `T` (defined) in
`client_static`. `client_dynamic` does not contain this code: `nm` shows them as `U`
(undefined), and the code exists only in `libmyutils.so`. The `size` command confirms
this: the text (code) section of `client_static` is 1637 bytes larger.

In my project the difference is small for two reasons: my library is very small, and
the standard C library (`libc`) is linked dynamically in both clients by default
(`ldd` lists `libc.so.6` for both). To see the full effect, I linked the program
completely statically:

    gcc -static obj/main.o lib/libmyutils.a -o /tmp/client_full_static

This executable was **818K**, and `ldd` reported "not a dynamic executable", because
the whole C library was copied into it. This shows that in real programs static linking
can make executables much larger, while dynamic linking keeps them small and lets many
programs share one copy of a library in memory.

### Q3. What is LD_LIBRARY_PATH? Why was it necessary to set it, and what does this tell you about the responsibilities of the dynamic loader?

`LD_LIBRARY_PATH` is an environment variable that contains a list of directories
(separated by `:`) where the dynamic loader searches for shared libraries before the
default system locations.

When I first ran `./bin/client_dynamic`, it failed with:

    error while loading shared libraries: libmyutils.so: cannot open shared object file: No such file or directory

and `ldd bin/client_dynamic` showed `libmyutils.so => not found`. The `-L` flag was
only used by the linker at build time. At run time, a different program, the dynamic
loader (`/lib64/ld-linux-x86-64.so.2`), must find the library. It searches only
specific places: paths stored inside the executable (RPATH/RUNPATH), directories in
`LD_LIBRARY_PATH`, the system library cache (`/etc/ld.so.cache`), and default
directories such as `/lib` and `/usr/lib`. My project's `lib` directory was in none of
these.

After running `export LD_LIBRARY_PATH=$PWD/lib:$LD_LIBRARY_PATH`, the program ran
correctly, and `ldd` showed:

    libmyutils.so => /home/dev_zohaib/UNI/5th-Semester/OS/ASSIGNMENTS/BSDSF24M016-OS-A01/lib/libmyutils.so

This setting is temporary and applies only to the current terminal session. My
top-level Makefile also has a `run-dynamic` target that sets the variable for a single
command: `LD_LIBRARY_PATH=$(LIB_DIR) ./bin/client_dynamic`.

This shows that the dynamic loader is responsible for finding the shared libraries a
program needs, loading them into the process's memory (at a randomized address), and
resolving the addresses of the functions the program uses, all before `main()` starts.
If it cannot find a required library, the program cannot start at all.
