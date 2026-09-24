<!-- SEO Meta Tags
Description: libmyutils is a C utility library for Linux, built as a static (.a) and shared (.so) library with recursive Makefiles, man pages and Git releases.
Keywords: C library, static library, shared library, dynamic linking, Makefile, GCC, Linux, man pages, operating systems, systems programming
author: Muhammad Zohaib Khan
canonical: https://github.com/ZohaibCodez/BSDSF24M016-OS-A01
-->

<!-- Open Graph
og:type: website
og:url: https://github.com/ZohaibCodez/BSDSF24M016-OS-A01
og:title: libmyutils - C Utility Library with Static and Dynamic Linking
og:description: A modular C utility library built as both a static (.a) and shared (.so) library, with recursive Makefiles, Linux man pages, an install target and versioned GitHub releases.
og:site_name: libmyutils
og:locale: en_US
-->

<!-- Twitter Card
twitter:card: summary_large_image
twitter:url: https://github.com/ZohaibCodez/BSDSF24M016-OS-A01
twitter:title: libmyutils - C Utility Library with Static and Dynamic Linking
twitter:description: A modular C utility library built as both a static (.a) and shared (.so) library, with recursive Makefiles, Linux man pages and GitHub releases.
-->

<!-- GitHub Metadata
topics: c, operating-systems, static-library, shared-library, makefile, linux, man-pages, gcc, systems-programming, dynamic-linking
languages: C, Makefile
-->

<div align="center">

# ⚙️ libmyutils

### A C Utility Library for Linux: Static & Dynamic Linking, Makefiles and Man Pages

[![C](https://img.shields.io/badge/C-GNU17-A8B9CC?logo=c&logoColor=white)](#-tech-stack)
[![GCC](https://img.shields.io/badge/compiler-GCC-FFCC00?logo=gnu&logoColor=black)](#-tech-stack)
[![Make](https://img.shields.io/badge/build-GNU%20Make-427819?logo=gnu&logoColor=white)](#-makefile-targets)
[![Linux](https://img.shields.io/badge/platform-Linux-FCC624?logo=linux&logoColor=black)](#-getting-started)
[![Course](https://img.shields.io/badge/course-Operating%20Systems-blue.svg)](#-acknowledgments)

[![Release](https://img.shields.io/github/v/release/ZohaibCodez/BSDSF24M016-OS-A01)](https://github.com/ZohaibCodez/BSDSF24M016-OS-A01/releases)
[![Last Commit](https://img.shields.io/github/last-commit/ZohaibCodez/BSDSF24M016-OS-A01)](https://github.com/ZohaibCodez/BSDSF24M016-OS-A01/commits/main)
[![Repo Size](https://img.shields.io/github/repo-size/ZohaibCodez/BSDSF24M016-OS-A01)](https://github.com/ZohaibCodez/BSDSF24M016-OS-A01)

[**Releases**](https://github.com/ZohaibCodez/BSDSF24M016-OS-A01/releases) • [**Report**](REPORT.md) • [**Library API**](#-library-api)

</div>

---

## 📋 Table of Contents

- [About](#-about)
- [Features](#-features)
- [Tech Stack](#-tech-stack)
- [Project Structure](#-project-structure)
- [Getting Started](#-getting-started)
- [Usage](#-usage)
- [Library API](#-library-api)
- [Makefile Targets](#-makefile-targets)
- [Binary Analysis](#-binary-analysis)
- [Versions and Git Workflow](#-versions-and-git-workflow)
- [Troubleshooting](#-troubleshooting)
- [Author](#-author)
- [Acknowledgments](#-acknowledgments)

---

## 🎯 About

**libmyutils** is a small, modular **C utility library** for Linux. It provides custom string functions and file utilities, and a driver program (`client`) that tests every function.

The project was built for **Operating Systems – Programming Assignment 01** at PUCIT. Its main goal is to show the complete workflow of a multi-file C project: modular code with header files, automated builds with **recursive Makefiles**, building and linking a **static library (`.a`)** and a **shared library (`.so`)**, writing **Linux man pages**, an `install` target, and versioned **Git tags and GitHub releases**.

The same library is linked two ways, so the difference between **static linking** and **dynamic linking** can be observed directly with tools like `nm`, `readelf`, `ldd` and `size`. A full analysis is in [REPORT.md](REPORT.md).

---

## ✨ Features

<table>
  <tr>
    <td>

**🔤 String Functions**
- `mystrlen` – string length
- `mystrcpy` – copy a string
- `mystrncpy` – copy at most *n* characters
- `mystrcat` – append a string

    </td>
    <td>

**📁 File Functions**
- `wordCount` – count lines, words and characters (like `wc`)
- `mygrep` – collect lines that contain a pattern (like `grep`)

    </td>
  </tr>
  <tr>
    <td>

**📦 Build and Linking**
- Recursive Makefiles with macros and multiple targets
- Static library `libmyutils.a` (`ar`, `ranlib`)
- Shared library `libmyutils.so` (`-fPIC`, `-shared`)

    </td>
    <td>

**📖 Documentation and Install**
- Man pages for every function (section 3)
- Man page for the `client` program (section 1)
- `make install` / `make uninstall` targets

    </td>
  </tr>
</table>

---

## 🛠️ Tech Stack

| Category | Tools |
|----------|-------|
| **Language** | C (GNU17, GCC default) |
| **Compiler** | GCC |
| **Build** | GNU Make (recursive Makefiles) |
| **Libraries** | `ar`, `ranlib`, `gcc -shared -fPIC` |
| **Analysis** | `nm`, `readelf`, `ldd`, `size` |
| **Docs** | groff / `man` |
| **Version Control** | Git, GitHub Releases |

---

## 🗂️ Project Structure

```text
BSDSF24M016-OS-A01/
├── 📁 include/               # Header files
│   ├── mystrfunctions.h
│   └── myfilefunctions.h
├── 📁 src/                   # Source code + src/Makefile
│   ├── main.c                # Driver program that tests all functions
│   ├── mystrfunctions.c
│   ├── myfilefunctions.c
│   └── Makefile
├── 📁 man/
│   ├── man1/client.1         # Man page for the client program
│   └── man3/*.3              # Man pages for each library function
├── 📁 obj/                   # Object files (generated)
├── 📁 lib/                   # libmyutils.a and libmyutils.so (generated)
├── 📁 bin/                   # client_static and client_dynamic (generated)
├── 📄 Makefile               # Top-level Makefile (build, run, install)
├── 📄 REPORT.md              # Analysis report
└── 📄 README.md              # You are here
```

Generated files in `obj/`, `lib/` and `bin/` are ignored by Git (see `.gitignore`). Compiled binaries are published in the [Releases](https://github.com/ZohaibCodez/BSDSF24M016-OS-A01/releases) instead.

---

## 🚀 Getting Started

### Prerequisites

- ✅ Linux (tested on Ubuntu under WSL)
- ✅ GCC, GNU Make and binutils (`ar`, `nm`, `readelf`)
- ✅ `man-db` for viewing man pages

```bash
sudo apt update
sudo apt install build-essential man-db
```

### Build

```bash
git clone https://github.com/ZohaibCodez/BSDSF24M016-OS-A01.git
cd BSDSF24M016-OS-A01
make
```

This builds:

| Output | Description |
|--------|-------------|
| `lib/libmyutils.a` | Static library |
| `lib/libmyutils.so` | Shared (dynamic) library |
| `bin/client_static` | Client linked against the static library |
| `bin/client_dynamic` | Client linked against the shared library |

---

## 💻 Usage

### Run the static client

```bash
make run
# or
./bin/client_static
```

### Run the dynamic client

The dynamic loader must know where `libmyutils.so` is:

```bash
export LD_LIBRARY_PATH=$PWD/lib:$LD_LIBRARY_PATH
./bin/client_dynamic
# or, without changing your shell:
make run-dynamic
```

### Expected output

```text
--- Testing String Functions ---
mystrlen("Hello") = 5 (expected 5)
mystrlen("") = 0 (expected 0)
mystrcpy -> "Hello", copied 5 chars (expected 5)
mystrcat -> "Hello, World", new length 12 (expected 12)
mystrncpy(n=4) -> "Oper", copied 4 chars (expected Oper, 4)

--- Testing File Functions ---
wordCount: lines=3 words=11 chars=68 (expected 3, 11, 68)
mygrep("systems"): 2 match(es) (expected 2)
  Operating systems are fun
  systems programming in C
```

### Install system-wide

```bash
make                 # build as a normal user first
sudo make install    # installs client + man pages under /usr/local
client               # run from any directory
man client
man mystrlen
sudo make uninstall  # remove everything that was installed
```

### Use the library in your own program

```c
#include <stdio.h>
#include "mystrfunctions.h"

int main(void) {
    char buf[32];
    mystrcpy(buf, "Hello");
    mystrcat(buf, ", World");
    printf("%s (%d chars)\n", buf, mystrlen(buf));
    return 0;
}
```

```bash
# Static linking
gcc myprog.c -Iinclude -Llib -l:libmyutils.a -o myprog

# Dynamic linking
gcc myprog.c -Iinclude -Llib -lmyutils -o myprog
LD_LIBRARY_PATH=$PWD/lib ./myprog
```

---

## 📚 Library API

| Function | Description | Returns |
|----------|-------------|---------|
| `int mystrlen(const char *s)` | Length of `s`, without the null byte | Length, or `-1` if `s` is NULL |
| `int mystrcpy(char *dest, const char *src)` | Copies `src` (with null byte) into `dest` | Characters copied, or `-1` |
| `int mystrncpy(char *dest, const char *src, int n)` | Copies at most `n` characters; pads with null bytes if `src` is shorter | Characters copied, or `-1` |
| `int mystrcat(char *dest, const char *src)` | Appends `src` to the end of `dest` | New length of `dest`, or `-1` |
| `int wordCount(FILE *file, int *lines, int *words, int *chars)` | Counts lines, words and characters from the current position to EOF | `0` on success, `-1` on failure |
| `int mygrep(FILE *fp, const char *search_str, char ***matches)` | Stores every line containing `search_str` in a newly allocated array | Number of matches, or `-1` on failure |

> ⚠️ **Note**: `mystrncpy` does **not** add a null byte if `src` has `n` or more characters.
> 📖 **Note**: The caller must `free()` each string returned by `mygrep`, and then the array itself.

Full details are in the man pages: `man -l man/man3/mygrep.3`.

---

## 🔧 Makefile Targets

| Command | Action |
|---------|--------|
| `make` | Build both libraries and both clients |
| `make static` | Build `libmyutils.a` and `bin/client_static` |
| `make dynamic` | Build `libmyutils.so` and `bin/client_dynamic` |
| `make run` | Build and run the static client |
| `make run-dynamic` | Build and run the dynamic client with `LD_LIBRARY_PATH` set |
| `make clean` | Remove object files, libraries and binaries |
| `sudo make install` | Install `client` to `/usr/local/bin` and man pages to `/usr/local/share/man` |
| `sudo make uninstall` | Remove the installed files |

The top-level `Makefile` calls `src/Makefile` with `$(MAKE) -C src` (recursive make).

---

## 🔍 Binary Analysis

```bash
ar -t lib/libmyutils.a                    # list object files inside the static library
nm bin/client_static | grep mystr         # T = code copied into the executable
nm bin/client_dynamic | grep mystr        # U = resolved at run time from the .so
nm -D lib/libmyutils.so                   # symbols exported by the shared library
readelf -s bin/client_static | grep my    # symbol table with type and size
ldd bin/client_dynamic                    # shared libraries resolved by the loader
size bin/client_static bin/client_dynamic # compare code (text) section sizes
```

The results of this analysis are explained in [REPORT.md](REPORT.md).

---

## 🌿 Versions and Git Workflow

Each feature was developed on its own branch, merged into `main`, and released with an annotated tag.

| Version | Branch | Description |
|---------|--------|-------------|
| [`v0.1.1-multifile`](https://github.com/ZohaibCodez/BSDSF24M016-OS-A01/releases/tag/v0.1.1-multifile) | `multifile-build` | Multi-file build with recursive Makefiles |
| [`v0.2.1-static`](https://github.com/ZohaibCodez/BSDSF24M016-OS-A01/releases/tag/v0.2.1-static) | `static-build` | Static library `libmyutils.a` |
| [`v0.3.1-dynamic`](https://github.com/ZohaibCodez/BSDSF24M016-OS-A01/releases/tag/v0.3.1-dynamic) | `dynamic-build` | Shared library `libmyutils.so` |
| [`v0.4.1-final`](https://github.com/ZohaibCodez/BSDSF24M016-OS-A01/releases/tag/v0.4.1-final) | `man-pages` | Man pages and install target |

---

## 🐛 Troubleshooting

**`cannot open shared object file: libmyutils.so`**
The dynamic loader cannot find the library. Run `export LD_LIBRARY_PATH=$PWD/lib:$LD_LIBRARY_PATH`, or use `make run-dynamic`.

**`Permission denied` when running `make`**
The build was probably run with `sudo`, so the files belong to root. Fix it with `sudo chown -R $USER:$USER obj lib bin`. Always run `make` before `sudo make install`.

**`Makefile: missing separator`**
Recipe lines in a Makefile must start with a TAB character, not spaces.

**`client: No such file or directory` after uninstall**
The shell remembers the old path. Run `hash -r`.

**Downloaded binary gives `Permission denied`**
Browsers do not keep Linux permissions. Run `chmod +x client_static`.

---

## 👤 Author

**Muhammad Zohaib Khan** – BS Data Science, PUCIT (BSDSF24M016)

- GitHub: [@ZohaibCodez](https://github.com/ZohaibCodez)
- LinkedIn: [ZohaibCodez](https://linkedin.com/in/ZohaibCodez)
- Email: itxlevicodez@gmail.com

---

## 🙏 Acknowledgments

- **Dr. Muhammad Arif Butt**, Instructor, Operating Systems, PUCIT
- [GNU Make Manual](https://www.gnu.org/software/make/manual/)
- [GCC Documentation](https://gcc.gnu.org/onlinedocs/)
- Linux `man-pages` project

---

<div align="center">

**libmyutils** • Built with 🖤 by Zohaib Khan

⭐ Star this repo if you find it helpful!

</div>
