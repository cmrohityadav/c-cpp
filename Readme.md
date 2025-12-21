# C++
- C++ is a cross-platform language that can be used to create high-performance applications.

- C++ was developed by Bjarne Stroustrup, as an extension to the C language.

- C++ gives programmers a high level of control over system resources and memory.

# Content
- [Why C++](#why-c)
- [C++ Dev Tools](#c-dev-tools)
- [compilation-](#cc-compilation-pipeline)
- [Comments](#comments)
- [Erros and Warnings](#Erros-and-Warnings)
- [Statements](#Statements)
- [Data input and output](#Data-input-and-output)
- [C++ core language Vs Standard library Vs STL](#C-core-language-Vs-Standard-library-Vs-STL)
- [Arrays](#Arrays)
- [Comments](#comments)
- [Comments](#comments)
- [OOP](#opp)
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
1. **High-Level Language (HLL) — the source file**
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
2. **Preprocessing (gcc -E) → produces file.i**
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


3. *Compilation (frontend) (gcc -S) → produces assembly file.S / file.s*

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


4. **Assembling (gcc -c) → produces object file file.o**
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
5. **Linking (Linker / Loader) → produces executable (e.g., a.out)**

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

## Erros and Warnings
When we write a C/C++ program, it passes through multiple stages
- Preprocessing → Compilation → Assembling → Linking → Execution
1. **Compile Time Errors**
- Errors that occur before the program is executed — i.e., during compilation.
- These stop the compiler from generating the executable file
- When the compiler encounters something it can’t understand (invalid syntax, undeclared variable, type mismatch, etc.), it throws compile-time errors
- They prevent creation of .o or a.out file.

| Type                      | Description                            | Example                                      |
| ------------------------- | -------------------------------------- | -------------------------------------------- |
| **Syntax Error**          | Invalid grammar or punctuation in code | `int a = ;` → missing value                  |
| **Type Error**            | Using wrong type in an operation       | `int x = "hello";`                           |
| **Undeclared Identifier** | Using variable/function not declared   | `cout << a;` → `a` undeclared                |
| **Missing Header**        | Using function without proper header   | `printf("hi");` without `#include <stdio.h>` |
| **Missing Semicolon**     | Forgetting `;` after statement         | `int a = 5`                                  |
| **Scope Error**           | Using variable out of its scope        | variable declared inside block used outside  |


2. **Runtime Erros**
- Errors that occur while the program is running, i.e., after successful compilation.
- The compiler doesn’t detect these because syntax is valid, but something goes wrong during execution (e.g., division by zero, invalid memory access, file not found).

| Type                         | Description                                    | Example                                         |
| ---------------------------- | ---------------------------------------------- | ----------------------------------------------- |
| **Division by Zero**         | Mathematical invalid operation                 | `int x = 10 / 0;`                               |
| **Segmentation Fault**       | Invalid memory access (e.g., null pointer)     | `int *p = NULL; *p = 10;`                       |
| **File Handling Error**      | Trying to open missing file                    | `fopen("abc.txt", "r")` when file doesn’t exist |
| **Memory Leak / Corruption** | Forgetting to `free()` memory or double delete | `delete ptr; delete ptr;`                       |
| **Array Index Out of Bound** | Accessing beyond valid index                   | `arr[10]` when array size = 5                   |
| **Invalid Input**            | User enters unexpected data type               | expecting `int`, user types `abc`               |



3. **Warnings**
- A warning is not an error — it’s a gentle alert from the compiler saying:
“Your code looks suspicious — it might cause problems, but I’ll still compile it.”
- The compiler still produces output, but you should fix warnings to avoid hidden bugs.

| Type                       | Description                           | Example                        |
| -------------------------- | ------------------------------------- | ------------------------------ |
| **Unused Variable**        | Declared but never used               | `int x = 10;` but not used     |
| **Type Conversion Loss**   | Assigning larger type to smaller type | `int x = 3.14;`                |
| **Uninitialized Variable** | Using variable without initialization | `int a; std::cout << a;`       |
| **Deprecated Function**    | Using outdated APIs                   | `gets()` is deprecated         |
| **Implicit Declaration**   | Using function without prototype      | `printf()` without `<stdio.h>` |

## Statements
- After every statement we put `;`
- A statement is basically one complete instruction for the compiler
```cpp
int amount=100;
amount=amount+100;
```
## Data input and output

### stdin (input)
```cpp
#include <iostream>
using namespace std;

int main() {
    int age;
    cout << "Enter your age: ";
    cin >> age;      // takes input from user
    cout << "You entered: " << age;
    return 0;
}
```
- cin means `character input`.
- The operator `>>` is called the `extraction operator` (extracts data from input stream).
- You can take multiple inputs in one line by spacing
```cpp
int a, b;
cin >> a >> b;   // input like: 10 20
```
- Reading data with spaces
```cpp
std::string fullname;
std::getline(std::cin,fullname);
```
### stdout
- Standard output stream (terminal / screen)
```cpp
#include<iostream>

int main(){
    std::cout<<"Hello Rohit"<<std::endl;
    return 0;
}
```
- cout means `character output`
- The operator `<<` is called the `insertion operator` 
- **inserts data into output stream**
- Buffered — output may be delayed until flushed or newline
- `std::endl` = end line + flush buffer (forces immediate output, unlike \n)


### clog (log stream)

```cpp
#include <iostream>

int main() {
    std::clog << "Program started successfully..." << std::endl;
    return 0;
}
```
- `clog` stands for character log
- Used for logging and informational messages
- Buffered — messages may be delayed until flushed


### stderr
```cpp
#include <iostream>

int main() {
    std::cerr << "Error: Invalid input!" << std::endl;
    return 0;
}
```
- `cerr` means character error
- Used for error or diagnostic messages
- `Unbuffered` — output appears immediately (no need to flush)
- Typically displayed on the same console, but can be redirected separately
 - `./a.out 2> error.txt`


| Command                                | What happens                                           |
| -------------------------------------- | ------------------------------------------------------ |
| `./a.out`                              | Everything prints on terminal                          |
| `./a.out > output.txt`                  | Only `std::cout` → file, errors/logs still on terminal |
| `./a.out > output.txt 2> error_log.txt` | Output and errors/logs go to separate files            |
| `./a.out > all_output.txt 2>&1`        | Everything goes into one file                          |

## C++ core language Vs Standard library Vs STL
```
┌────────────────────────────────────────────┐
│          C++ Core Language                 │
│  (keywords, syntax, templates, classes)    │
└──────────────┬─────────────────────────────┘
               │
               ▼
┌────────────────────────────────────────────┐
│          C++ Standard Library              │
│  (I/O, strings, threading, filesystem, etc.) │
│      ┌────────────────────────────┐         │
│      │          STL               │         │
│      │ (containers + algorithms)  │         │
│      └────────────────────────────┘         │
└────────────────────────────────────────────┘
```

### C++ Core Language
- C++ ke khud ke language ke rules, keywords aur syntax. 
- Jaise `if, for, class, template, new, delete` : ye sab woh cheezein hain jo compiler seedhe samajhta hai. 
- Yahaan koi ready-made tools/code nahi hote, sirf language ke building blocks milte hain jisse tum apna logic likhte ho.
- Bina koi headers include kiye.

### C++ Standard Library
- Ab jab language ban gayi, to uske upar ek bada toolbox chahiye jisme common kaam ke liye ready code ho. 
- Ye hi hai C++ Standard Library, isme I/O `(std::cout, std::cin), strings, threads, files, time functions,` sab milta hai. 
- Hame har baar zero se likhne ki zarurat nahi; ye library tumhare liye heavy lifting karti hai.

### STL (Standard Template Library)
- The STL is actually a subset of the C++ Standard Library
- Jahan pe tumhe milte hain containers `(vector, map, list) aur algorithms (sort, find, etc.)`. 
- Ye sab templates pe based hote hain, matlab generic aur fast. 
- STL ne C++ ko “powerful but elegant” banaya, kyunki ab tum reusable aur efficient code likh sakte ho bina wheel dubara banaye.

## Arrays
- An array is a collection of elements of the **same type**, **stored contiguously in memory**.
- It’s like ek rail coach — sab compartments (elements) ek ke baad ek lagte hain.
-   ```cpp
    dataType nameOfArray[size]
    ```
### Declaring & Initializing Arrays
```cpp
// uninitialized (garbage values)
int arr[5];
int a[5];    

// initialized
int b[5] = {1, 2, 3, 4, 5}; 

// size auto-calculated (3)
int c[]  = {10, 20, 30};    
```
- arr is NOT a pointer —> it’s an array of 5 integers.
- Lekin jab hum `arr` ko kisi function me pass karte ho ya kisi pointer variable me assign karte ho yas as `expression` use krte ho,
tab compiler usko “decay” kara deta hai — i.e. `&arr[0]` bana deta hai

```cpp
// What actually happens here

int arr[5] = {10, 20, 30, 40, 50};

int* p = arr;
// arr DECAYS to &arr[0]

// Compiler internally treats it like
int* p = &arr[0];
```
### Pointer Arithmetic in array
```cpp
int p[5]={10,20,30,40,50};
//p is an array of 5 integers, stored in contiguous memory

// When used in expressions, p decays into pointer to first element &p[0]

// p means &p[0] 

p + 1   
// means: address of p[0] + (1 * sizeof(int))
// moves pointer ahead by 4 bytes (if int = 4 bytes)
// i.e. points to p[1]

p + 2   
// means: address of p[0] + (2 * sizeof(int))
// points to p[2]



// Dereferencing & Indexing
p[i] == *(p + i)


*(p+0) == *(p)
// dereferences p[0] → gives 20

*(p + 1) 
// dereferences p[1] → gives 20
*(p + 2) // dereferences p[2] → gives 30

// Similarly:
p[0] == *(p + 0) == arr[0] == 10
p[1] == *(p + 1) == arr[1] == 20
p[2] == *(p + 2) == arr[2] == 30
p[3] == *(p + 3) == arr[3] == 40
p[4] == *(p + 4) == arr[4] == 50

```
### Notes
- `arr` = poora ghar (memory block)
- `&arr` = us ghar ka address
- `arr` jab decay hota hai, to us ghar ke pehle kamre (first element) ka address ban jaata hai
- par `arr` khud koi "pointer" nahi hai — `wo address rakhta nahi`, `wo address hai`
```cpp
int arr[5] = {10, 20, 30, 40, 50};
int *p = arr;
int (*ptr)[5] = &arr;

//arr     = pointer to 1st int       → moves +4 bytes per increment
//ptr   = pointer to entire array  → moves +20 bytes per increment

```
```bash
arr
+------+------+------+------+------+
| 10   | 20   | 30   | 40   | 50   |
+------+------+------+------+------+
^
|
Array object starts *here*


# Visualize (Assume int = 4 bytes)
# Memory Layout

arr (array object)
0x1000 → 10
0x1004 → 20
0x1008 → 30
0x100C → 40
0x1010 → 50

So:

arr        == &arr[0] == 0x1000
&arr       == 0x1000  (same numeric, different TYPE)

```
- Size of Array: `sizeof(arr)/sizeof(arr[0]);`
- After c++17: `int size {std::size(arr)};`

### Arrays of characters






## OOP
### Class
- A class is nothing, but a blue print that is used to create Object
- It's User Defined Data Type
- It defines properties (data) and behaviors (methods).
- Just like SBI Form.docx, original form(Class)it is only a template., isse print krke xerox photo copy (object)

### Object
---
- An Object is nothing but a particular instance of a class
- Just like Xerox copy, we can create n number of piece

```c++
class Animal {
    public: //access modifier

    // properties/member data/member variable
    string name;
    int age;


    //methods/member method/class method,function
    void sound() {
        cout << "Animal makes a sound" << endl;
    }
};
// main.cpp
int main() {
    Animal a1;   // Object creation
    a1.name = "Dog";
    a1.age = 5;

    a1.sound();  // Calling method

    return 0;
}
```
```cpp
class Strategy{
 int orderQty;
 double price;
 int userId;
 string userName;
};

//main.cpp
int main{
    //automatic storage allocation
    Strategy s1;

    s1.orderQty=100;
    s1.price=50.02;
    s1.userId=123456;
    s1.userName="cmrohityadav"

    Strategy Profit10X;

    Profit10X.orderQty=1000;
    Profit10X.price=500.02;
    Profit10X.userId=123456;
    Profit10X.userName="cmrohityadav"


   
    // dynamic storage allocation
    Strategy* dynamicProfit = new Strategy();

    dynamicProfit->orderQty = 1000;
    dynamicProfit->price = 500.02;
    dynamicProfit->userId = 123456;
    dynamicProfit->userName = "cmrohityadav";

    delete dynamicProfit;   // free heap memory

    return 0;
}

```
### **automatic storage allocation**
- Memory is allocated automatically
- The object is stored in stack memory
- The constructor (if any) is called automatically
- You do not manually free memory
- The destructor is called automatically when main() ends
- C++ handles everything automatically based on scope

### **dynamic storage allocation**
- Memory for the object is allocated at runtime
- Memory is allocated in the heap
```bash
new Strategy();
1. Reserves heap memory
2. Calls the constructor of Strategy
3. Returns the address of the allocated object
```
- `dynamicProfit` is a pointer that stores the address of the object
```bash
dynamicProfit->orderQty = 1000; <==>(*dynamicProfit).orderQty = 1000;
```
### **Deallocating Memory**
- Memory allocated using `new` must be released using `delete`
- Prevents memory leaks
- Calls the destructor of the class

### **Mermory Picture Visualize**
- `Strategy* dynamicProfit = new Strategy();`
```bash
Stack:                     Heap:
dynamicProfit  ───────▶  [ Strategy Object Data ]
(pointer)                (orderQty, price, userId...)

```
- `dynamicProfit` → stack me pointer
- Actual object → heap me data
- Pointer sirf address pakad ke baitha hai
```bash
# Jab tum likhte ho
delete dynamicProfit;

1. Heap se data udd gaya
2. RAM free ho gayi
3. Object destroy ho gaya
4. Destructor call ho chuka
```
```bash
Stack:                     Heap:
dynamicProfit  ───────▶  ❌  (memory free / reusable)
(pointer)
```
- Heap ka data gaya 
- Pointer ab bhi wahi address yaad kar raha hai 
- Isliye ye dangerous state hai
```bash
# Is moment pe pointer ka haal
dynamicProfit->orderQty = 100;  // 💥 CRASH / undefined

1. Pointer zinda hai
2. Jisko point kar raha tha wo mar chuka hai

```
- Ye hota hai `Dangling` Pointer
- Isliye hum likhte hain
```cpp
delete dynamicProfit;
dynamicProfit = nullptr;
```

### Access Modifiers
- Access modifiers decide kaun kya access kar sakta hai (data members & functions)
- **public**
- Sab jagah se accessible
- Class ke andar
- Class ke bahar
- Derived (child) class se bhi

- **private**
- `Sirf` class ke andar accessible
- Bahar se `nhi`
- Derived class se bhi `nhi`
- **protected**
- Class ke andar
- Derived class ke andar
- Bahar se `nhi `

### Constructor
- This is an special function that is used to `initilize the member variables` during object creation

#### Default Constructor
- A special constructor `automatically` generated by class if some constructor is `not defined by the programmer`
- If you define any constructor, C++ stops creating the default constructor for you
```cpp
class Strategy{
    public:
    int qty;
    double price;
    std::string userName;

    Strategy(){
        qty=10;
        price=10.5;
        userName="TraderRohit";
    }

};
```
#### Parameterized Constructor
- A Special constructor that accepts one or more parameter during Object creation

```cpp
class Strategy{
    public:
    int qty;
    double price;
    std::string userName;

    Strategy(int orderQty,double orderPrice,std::string userID){
       qty=orderQty;
       price=orderPrice;
       userName=userID;
    }

};
//main
Strategy s(10,10.5,"traderrohit");
```
- Professional C++ Way
```cpp
class Strategy {
public:
    int qty;
    double price;
    std::string userName;

    //  Default Constructor
    Strategy() : qty(0), price(0.0), userName("NA") {
        std::cout << "Default constructor called\n";
    }

    //  Parameterized Constructor
    Strategy(int orderQty, double orderPrice, std::string userID)
        : qty(orderQty), price(orderPrice), userName(userID) {
        std::cout << "Parameterized constructor called\n";
    }

    //  Default arguments
    Strategy(int orderQty = 0,
             double orderPrice = 0.0,
             std::string userID = "NA")
        : qty(orderQty), price(orderPrice), userName(userID) {
        std::cout << "Constructor called\n";
    }

};
```

#### why to delete default constructor while designing any system?
- Koi object jab banta hai tabhi kuchh valid value k sath banna hai to help krta hai,
- bante waqt hi value dalo warna error dega
- Delete the default constructor and never define it.
- Prevent invalid objects
- Enforce correctness
- Catch bugs at compile time
```cpp
#include <iostream>
#include <string>

class Strategy {
public:
    int qty;
    double price;
    std::string userName;

    Strategy(int orderQty, double orderPrice, std::string userID) {
        qty = orderQty;
        price = orderPrice;
        userName = userID;
    }

    Strategy() = delete;  

    void Print() {
        std::cout << price << std::endl;
        std::cout << qty << std::endl;
        std::cout << userName << std::endl;
    }
};

int main() {
    Strategy s1(10, 50.2, "trader");
    s1.Print();
    return 0;
}


```
#### Constructor Initializer List
```cpp
class Student {
    int roll;
    std::string name;

public:
    Student(int r, std::string n)
        : roll(r), name(n) {}   // initializer list
};
```
##### Advantages
- Directly initializes data members
- More efficient (no extra assignment)
- Mandatory for:
    - const data members
    - reference members
    - member objects without default constructors
    - base class initialization
- Preferred in modern C++
##### Disadvantages
- Initialization order is fixed by member declaration (not list order)
- Slightly harder to understand for beginners
- Cannot include complex logic (only initialization)
#### Normal Initialization
```cpp
class Student {
    int roll;
    std::string name;

public:
    Student(int r, std::string n) {
        roll = r;      // assignment
        name = n;      // assignment
    }
};
```
##### Advantages
- Easy to read and understand
- Good for simple classes and beginners
- Allows complex logic, conditions, loops

##### Disadvantages
- Less efficient (default initialization + assignment)
- Cannot initialize:
    - const members
    - reference members
    - member objects without default constructors
- Not suitable for performance-critical code
#### Copy Constructor
- A copy constructor is a special constructor that creates a new object by copying an existing object of the same class
- The copy constructor is automatically called in these situations
1. When an object is initialized from another object
```cpp
Person p1;
Person p2 = p1;   // copy constructor
```
2. When passing object by value to a function
```cpp
void display(Person p); // p is a copy
```
3. When returning object by value
```cpp
Person createPerson() {
    Person p;
    return p;   // copy constructor (or move)
}
```
```cpp
class Strategy {
public:
    int qty;
    double price;
    std::string userName;

    Strategy(int orderQty, double orderPrice, std::string userID)
        : qty(orderQty), price(orderPrice), userName(userID) {}

    Strategy(const Strategy& other) {
        std::cout << "Copy constructor called\n";
        qty = other.qty;
        price = other.price;
        userName = other.userName;
    }


};

int main() {
    Strategy s1(1, 2.0, "A");

    Strategy s2 = s1;   // copy constructor

    // Modern C++ Best Practice
    Strategy s3(s1);    // copy constructor
    Strategy s4{ s1 };

}

```









