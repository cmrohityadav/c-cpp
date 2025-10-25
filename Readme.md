# C++
- C++ is a cross-platform language that can be used to create high-performance applications.

- C++ was developed by Bjarne Stroustrup, as an extension to the C language.

- C++ gives programmers a high level of control over system resources and memory.

# Content
- [Why C++](#why-c)
- [C++ Dev Tools](#c-dev-tools)
- [compilation-](#cc-compilation-pipeline)
- [Comments](#comments)

## Why C++
- Systems programming
- Games
- Critical Programming

## C++ Dev Tools
### IDES
---
#### Windows
- Visual Studio code
- MS Visual Studio
- CodeLite
#### Linux
- Visual Studio code
- Qt Creator
- CodeLite
#### Mac
- Visual Studio code
- XCode
- CodeLite

### Compilers
---
#### Windows
- Mingw
- Msvc
- Clang llvm
#### Linux
- GCC
- Clang llvm
#### Mac
- GCC
- Clang llvm
- Clang Apple

### Intallations
#### windows
- winlibs

#### Linux
- GCC
- Clang llvm
    - Ubantu
        - apt-get install gcc
        - apt-get install g++
        - apt-get install gdb


## C/C++ compilation pipeline
1. High-Level Language (HLL) — the source file
You start with a source file, e.g. file.cpp (C++), file.c (C). This is human-readable code containing comments, preprocessor directives (#include, #define), function definitions, types, etc.

```cpp
#include <iostream>
#define SQR(x) ((x)*(x))

int main() {
    int a = 5;
    std::cout << SQR(a) << "\n";
    return 0;
}
```
2. Preprocessing (gcc -E) → produces file.i
What the preprocessor does
- Removes/handles comments. All // and /* ... */ comments are removed
- Expands #include directives. For #include <...> and #include "..." it replaces the directive by the contents of the included header file (searching the include paths)
- Expands macros. #define macros are expanded (object-like and function-like macros).
- Processes conditional compilation. #if, #ifdef, #ifndef, #else, #endif are evaluated and only active code is kept.
- Injects line markers. The preprocessor may insert # lineno "filename" markers to help the compiler track original source locations
```bash
gcc -E file.cpp -o file.i
```
- file.i is the preprocessor output (a pure C/C++ program with all includes expanded and macros processed). It is still source code (but expanded), ready for the compiler frontend.


3. Compilation (frontend) (gcc -S) → produces assembly file.S / file.s

What the compiler frontend does
- Parses the preprocessed source into an abstract syntax tree (AST).
- Performs semantic analysis: type checking, overload resolution (C++), template instantiation, diagnostics.
- Applies optimizations at the high-level IR (if enabled with -O flags).
- Generates assembly language for the target architecture.
```bash
gcc -S file.i -o file.S     # produce assembly
# or directly from source:
g++ -S file.cpp -o file.S   # using the C++ frontend
```
- file.S (or file.s) — assembler source code, textual assembly instructions (architecture specific, e.g. x86-64 AT&T or Intel syntax depending on assembler flags).

- The assembly contains function labels, instructions, data directives, references to external symbols.


4. Assembling (gcc -c) → produces object file file.o
What the assembler does
- Translates assembly text into machine code (binary instructions).

Produces a relocatable object file containing:

Machine code bytes.

Data bytes.

Symbol table (local and global symbols).

Relocation entries (places in the code/data that refer to addresses not yet known).

Section table (e.g., .text, .data, .bss, .rodata, .symtab).

The object file format on Linux is typically ELF (.o is an ELF relocatable object).
```bash
gcc -c file.S -o file.o
# or compile & assemble from C++ in one step:
g++ -c file.cpp -o file.o
```
5. Linking (Linker / Loader) → produces executable (e.g., a.out)

This stage resolves symbol references among object files and libraries and produces either:

A final executable (ELF executable) or

A shared object (.so) if building a library.

There are two closely related roles:

Linker (ld) — combines object files and libraries, resolves relocations, produces the final binary on disk.

Loader (dynamic loader at runtime, e.g. ld-linux.so) — loads the executable into memory at runtime, resolves dynamic links (shared libraries), and transfers control to main.
```bash
gcc file.o -o a.out
# or compile & link in one step:
g++ file.cpp -o a.out
```

## Comments
- Single line
```cpp
// this is ignore by compilar 
//This is for programmer
```

- Multi line
```cpp
/*
int a=0;
int b=2;
*/
```

##

