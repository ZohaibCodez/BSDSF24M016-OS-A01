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
