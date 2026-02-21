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
- [Pointers](#pointers)
- [Reference](#reference)
- [Type Conversion](#type-conversion)
- [Arrays](#Arrays)
- [Comments](#comments)
- [Comments](#comments)
- [OOP](#oop)
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

## Pointers

### unique_ptr
- Ek object ka single owner hota hai.
- Ek ghar ka ek hi malik
- new → owner fixed → scope khatam → delete automatic
- `unique_ptr` almost hamesha heap (dynamic memory) ke object ko manage karta hai.
- unique_ptr sirf heap allocated object ke liye use karo.
- unique_ptr ka kaam memory banana nahi hai ->Ownership manage karta hai
- Memory create hoti hai : `make_unique` se
- make_unique → heap me object create karta hai
-  unique_ptr generally heap objects manage karta hai
-  unique_ptr khud stack pe ho sakta hai
```bash
std::unique_ptr<Type> ptr = std::make_unique<Type>(constructor_arguments);
```

#### Properties of unique pointer
##### const unique_ptr can't be copied

##### We cannot create the copy of unique_ptr
```cpp
std::unique_ptr<int> p1 = std::make_unique<int>(20);

// std::unique_ptr<int> p2(p1);   // ❌ Error

 std::unique_ptr<int> p3 = p1;   // ❌ Error: copy not allowed
```
##### We can pass the ownership using std::move()
```cpp
#include <iostream>
#include <memory>

int main() {
    std::unique_ptr<int> p1 = std::make_unique<int>(30);

    std::unique_ptr<int> p2 = std::move(p1);  // Ownership transferred

    if (!p1)
        std::cout << "p1 is now null\n";

    std::cout << "p2 value: " << *p2 << "\n";
}
```
##### Memory deletion is guaranteed in normal exit and exception exit
```cpp
#include <memory>

void func() {
    std::unique_ptr<int> ptr = std::make_unique<int>(100);
}  // Memory automatically deleted here

void funcException() {
    std::unique_ptr<int> ptr = std::make_unique<int>(200);
    throw std::runtime_error("Error occurred");
}

int main() {
    try {
        funcException();
    } catch (...) {
        std::cout << "Exception caught\n";
    }
}
```

### shared_ptr
- Ek object ke multiple owners ho sakte hain.
- Ek ghar ke kai malik (joint ownership).
- new → reference count start = 1
- Har copy → reference count ++
- Jab last owner scope se bahar → delete automatic
- shared_ptr bhi generally heap (dynamic memory) ke object ko manage karta hai.
- shared_ptr sirf heap allocated object ke liye use karo.
- shared_ptr ka kaam memory banana nahi hai → Ownership manage karta hai
- Memory create hoti hai: make_shared se
- make_shared → heap me object create karta hai
- shared_ptr generally heap objects manage karta hai
- shared_ptr khud stack pe ho sakta hai
```cpp
std::shared_ptr<Type> ptr = std::make_shared<Type>(constructor_arguments);
```
#### Properties of shared_ptr
##### shared_ptr can be copied
✔ Copy allowed
✔ Reference count increase hota hai
```cpp
#include <iostream>
#include <memory>

int main() {
    std::shared_ptr<int> p1 = std::make_shared<int>(20);

    std::shared_ptr<int> p2 = p1;   // ✅ Copy allowed

    std::cout << "p1 count: " << p1.use_count() << "\n";
    std::cout << "p2 count: " << p2.use_count() << "\n";
}

```
- use_count() object ka hota hai, pointer ka nahi.

##### Ownership shared hota hai (Reference Counting)
```cpp
#include <iostream>
#include <memory>

int main() {
    std::shared_ptr<int> p1 = std::make_shared<int>(50);

    {
        std::shared_ptr<int> p2 = p1;
        std::cout << "Inside block count: " << p1.use_count() << "\n";
    } // p2 destroyed here

    std::cout << "Outside block count: " << p1.use_count() << "\n";
}

```

##### Memory deletion is automatic (Normal + Exception)
```cpp
void func() {
    std::shared_ptr<int> ptr = std::make_shared<int>(100);
}  // Memory deleted when ref count becomes 0

/////////////////
#include <iostream>
#include <memory>

void funcException() {
    std::shared_ptr<int> ptr = std::make_shared<int>(200);
    throw std::runtime_error("Error occurred");
}

int main() {
    try {
        funcException();
    } catch (...) {
        std::cout << "Exception caught\n";
    }
}

```
## Reference
- A reference is an alias (another name) for an existing variable
```c++
int a = 5, b = 10;

// int& r;        // ❌ Error – must initialize
   
int& r = a;    // r refers to the same memory as a
// r actually a ka dusra naam (alias) hai

r = b;       // ❌ doesn't rebind, just assigns value

int& r = nullptr;  // ❌ Not allowed
```

## Type Conversion
- ek data type ko dusre data type me convert krna
### Implicit Type Conversion (Automatic)
- Isme compiler khud conversion karta hai.
- Isko `Type Promotion` bhi kehte hain
```c++
int a = 5;
double b = a;   // int automatically double ban gaya
```
- Smaller → Larger Type
- Isko kehte hain `Upcasting` / `Widening` Conversion
```bash
char → int
int → long
int → double
float → double
```
### Explicit Type Conversion (Manual / Type Casting)
- Isme programmer khud conversion karta hai
- Isko `Type Casting` bhi kehte hain.
1. C-Style Casting
2. static_cast
3. dynamic_cast
4. const_cast
5. reinterpret_cast
#### C-Style Casting
```cpp
double d = 5.7;
int a = (int)d;  // 5 ban jayega
```
- Risky hota hai
- Data loss ho sakta hai

#### static_cast
```cpp
double d = 5.7;
int a = static_cast<int>(d);
```
- Compile-time pe check hota hai
- Safer than C-style

#### dynamic_cast
- Runtime pe check karta hai.
- Mostly inheritance mein use hota hai
- dynamic_cast C++ ka ek runtime type casting operator hai jo mainly inheritance (polymorphism) ke case me use hota hai
- Ye ensure karta hai ki cast safe hai ya nahi, aur agar cast galat ho to:
1. Pointer case me → nullptr return karta hai
2. Reference case me → std::bad_cast exception throw karta hai
```cpp
#include <iostream>
using namespace std;

class A {
public:
    virtual void func() { }   // Must have at least one virtual function
};

class B : public A {
public:
    void show() {
        cout << "Class B\n";
    }
};

int main() {
    A* ptr = new B();  // Base class pointer pointing to Derived object

    B* bptr = dynamic_cast<B*>(ptr);

    if (bptr != nullptr) {
        cout << "Cast successful\n";
        bptr->show();
    } else {
        cout << "Cast failed\n";
    }
}

```
- STORY
```bash
class Animal {
public:
    virtual void speak() {
        cout << "Animal sound\n";
    }
};

class Dog : public Animal {
public:
    void bark() {
        cout << "Barking\n";
    }
};

class Cat : public Animal {
public:
    void meow() {
        cout << "Meow\n";
    }
};


----------------------------
Animal* a = new Dog();

------------------------------
Ab problem
a->bark();   // ❌ Error

Kyuki compiler ko sirf itna pata hai ki pointer Animal* hai
Usko nahi pata ki ye actually Dog hai

--------------------------
Memory me Dog object hai.
Lekin pointer Animal type ka hai.
Toh agar hume Dog ka special function (bark()) call karna ho to?
-----------------------------
Pehle check karna padega ki kya ye sach me Dog hai ya nahi.

Yahi
 kaam karta hai dynamic_cast
----------------------------
Wo runtime pe check karta hai:

"Ye Animal pointer actually Dog object ko point kar raha hai kya?"

Agar haan → safe conversion
Agar nahi → nullptr
-----------------------------

Animal* a = new Dog();

Dog* d = dynamic_cast<Dog*>(a);

if(d != nullptr) {
    d->bark();   // Safe
}

-----------------------------
Ab feel karo:

Agar object Dog hai → bark chalega

Agar object Cat hota → d = nullptr
--------------
Base class pointer/reference se derived class ka object safely nikalna ho
----------------------------

```


#### const_cast
- Ye sirf constness change karta hai, data type change nahi karta
- const remove karta hai
- const add karta hai
- Pointer & reference pe kaam karta hai
- Value pe directly apply nahi hota
- Lekin actual object agar originally const hai, aur aap usko modify karte ho → Undefined Behavior
- `const_cast<new_type>(expression);`
```cpp
   const int a=10;

    const int* ptr=&a;

    int* newValue=const_cast<int*>(ptr);

    *newValue=20; //// ❌ Undefined Behavior

    cout<<"value of a: "<<a<<endl; //10
    cout<<"value of newValue: "<<*newValue<<endl; //20

```
```cpp
int a=10;

    const int* ptr=&a;

    int* newValue=const_cast<int*>(ptr);

    *newValue=20;

    std::cout<<*newValue<<std::endl; //20 
    std::cout<<a<<std::endl; //20 
```



#### reinterpret_cast

## Function
- pass by reference/pointer is faster than pass by value in function Parameter
- `void function(const int x)` : Do NOT allow modification of x inside this function

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
- [class](#class)
- [Object](#object)
- [Access Modifiers](#access-modifiers)
- [Constructor](#constructor)
- [this](#this)
- [Static](#static-in-class)
- [Inheritance](#inheritance)
- [Compile vs Run Time Binding](#compile-vs-run-time-binding)
- [Virtual function](#virtual-function)
- []()
- [Override](#Override)
- [final ](#final)
- [Polymorphism](#Polymorphism)
- [Pure Virtual Function](#pure-virtual-function)
- [Abstract class](#abstract-class)
- [Interface](#Interface)
- [Inline](#inline)
- [Diamond Problem](#diamond-problem)
- [Virtual Base Classes](#virtual-base-classes)


### Class
- A class is nothing, but a blue print that is used to create Object
- It's User Defined Data Type
- It defines properties (data) and behaviors (methods).
- Just like SBI Form.docx, original form(Class)it is only a template., isse print krke xerox photo copy (object)

### Object
---
- An Object is nothing but a particular instance of a class
- Just like Xerox copy, we can create n number of piece
### Access Specifiers
- ``private`` Members are accessible only within the class. This is the default access level for classmembers.
- `public` Members are accessible from outside the class
- `protected` Members are accessible with in the class and its derived classes
(used in inheritance)
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
    //automatic storage allocation(Memory allocated on stack)
    //Constructor runs automatically
    //Destructor runs automatically when scope ends

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


   
    // dynamic storage allocation (Allocates memory on the heap)
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
- `->  =  (*pointer).`
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

### Accessing Class Members
- `Public Members`: Public members can be accessed directly using the dot operator
(.) on the object
- `Private Members`: Private members cannot be accessed directly from outside the
class.
They can only be accessed through public member functions (`getters and
setters`).
```cpp
class Strategy {
private:
    int orderQty;

public:
    void setOrderQty(int qty) {
        orderQty = qty;
    }

    int getOrderQty() {
        return orderQty;
    }
};

Strategy s1;
s1.setOrderQty(100);   // ✅ correct
// s1.orderQty = 100;  ❌ error (private)
```
- `Protected` :Member class ke andar aur uske derived (child) classes ke andar accessible hoga, lekin outside world se direct access nahi hoga

### Constructor
- This is an special function that is used to `initilize the member variables` during object creation
- Constructors have the `same name as the class `and
do `not have a return type`, **not even void**
1. Default
2. Parameterized
3. Copy
- [Default Constructor](#default-constructor)
- [Parameterized Constructor](#parameterized-constructor)
- [why to delete default constructor while designing any system?](#why-to-delete-default-constructor-while-designing-any-system)
- [Constructor Initializer List](#constructor-initializer-list)
- [Normal Initialization](#normal-initialization)
- [Copy Constructor](#copy-constructor)
- [Example of Shallow/Deep Copy, Copy constructor,Copy Assignment Operator](#example-of-shallowdeep-copy-copy-constructorcopy-assignment-operator)
- [Move ](TODO)
- [RAII](TODO)
- []()
- []()

#### Default Constructor
- A default constructor is a constructor that takes no arguments. It is automatically called when an object is created without any initial values.
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
- A copy constructor is a constructor that initializes an object using
another object of the same class. It is used to create a copy of an existing object
- A copy constructor is a special constructor that creates a new object by copying an existing object of the same class
- The copy constructor is automatically called in these situations
- `Compiler khud ka copy constructor provide krta hai`
- `ClassName(const ClassName& other);`
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
- If you do not define a copy constructor, the compiler automatically provides one.
- This is called the default copy constructor
- The compiler-generated copy constructor does: `Shallow Copy`
- sirf value copy krta hai, aagar koi pointer hua to uska address copy karega, memory ka data nhi
##### Drawback of using default copy constructor
- The default copy constructor performs a `shallow copy of pointers`, causing multiple objects to own the same memory, which leads to double deletion and undefined behavior
```cpp
#include <iostream>
#include <string>

using namespace std;

class OrderBuilder
{
public:
    OrderBuilder(string name, int id)
    {
        exchangeName = name;
        exchangeId = id;
    }

    int exchangeId;
    string exchangeName;
};

class Strategy
{
    double orderQty;
    double price;
    string userName;
    OrderBuilder* ob;

public:
    Strategy(double qty, double prc, string name)
        : orderQty(qty), price(prc), userName(name)
    {
        cout << "Inside constructor" << endl;
        OrderBuilder* obj = new OrderBuilder("NSE", 107);
        ob = obj;
    }

    ~Strategy()
    {
        cout << "Destructor called" << endl;
        delete ob;
    }

    void PrintStrategy()
    {
        cout << "OrderQty:\t" << orderQty << endl;
        cout << "Price:\t\t" << price << endl;
        cout << "UserName:\t" << userName << endl;
        cout << "ExchangeName:\t" << ob->exchangeName << endl;
    }
};

int main()
{
    Strategy* obj1 = new Strategy(10, 100.0, "rohit");
    obj1->PrintStrategy();

    Strategy obj2(*obj1);   // DEFAULT COPY CONSTRUCTOR (SHALLOW COPY)

    delete obj1;            

    obj2.PrintStrategy();  

    return 0;
}

```
##### Deep copy

```cpp
#include <iostream>
#include <string>

using namespace std;

class OrderBuilder
{
public:
    int exchangeId;
    string exchangeName;

    OrderBuilder(string name, int id)
        : exchangeId(id), exchangeName(name)
    {
    }

    // Copy constructor
    OrderBuilder(const OrderBuilder& other)
        : exchangeId(other.exchangeId),
          exchangeName(other.exchangeName)
    {
    }
};

class Strategy
{
    double orderQty;
    double price;
    string userName;
    OrderBuilder* ob;

public:
    // Constructor
    Strategy(double qty, double prc, string name)
        : orderQty(qty), price(prc), userName(name)
    {
        cout << "Inside constructor" << endl;
        ob = new OrderBuilder("NSE", 107);
    }

    //  Deep copy constructor
    Strategy(const Strategy& other)
        : orderQty(other.orderQty),
          price(other.price),
          userName(other.userName)
    {
        cout << "Inside deep copy constructor" << endl;
        ob = new OrderBuilder(*other.ob); // DEEP COPY
    }

    // Destructor
    ~Strategy()
    {
        cout << "Destructor called" << endl;
        delete ob;
    }

    void PrintStrategy() const
    {
        cout << "OrderQty:\t" << orderQty << endl;
        cout << "Price:\t\t" << price << endl;
        cout << "UserName:\t" << userName << endl;
        cout << "ExchangeName:\t" << ob->exchangeName << endl;
        cout << "ExchangeId:\t" << ob->exchangeId << endl;
        cout << "-------------------------" << endl;
    }
};

int main()
{
    Strategy* obj1 = new Strategy(10, 100.0, "rohit");
    obj1->PrintStrategy();

    Strategy obj2(*obj1);   // ✅ DEEP COPY

    delete obj1;            // obj2 is still valid

    obj2.PrintStrategy();  

    return 0;
}

```
#### Properties of Copy constructor
- Copy constructor has the same name as the class and no return type.
- It takes a reference to an object of the same class as an argument.
- It is invoked automatically when a new object is created as a copy of an existing object.
- The user can define their own copy constructor; if not defined, the compiler provides a default one.
- The default copy constructor performs a **shallow copy**.
- To perform a **deep copy**, the user must define their own copy constructor.
- When an object is passed **by value** to a function, the copy constructor is called.

- Copy constructor overloading is **limited**:
  - Valid forms:
    ```cpp
    Strategy(const Strategy& obj);
    Strategy(Strategy& obj);
    ```
  - Invalid form:
    ```cpp
    Strategy(Strategy obj); // causes infinite recursion
    ```
#### Copy Assigment Operator
```cpp
int main()
{
    Strategy obj1 = Strategy(10, 100);

    Strategy obj2 = obj1;   // Copy constructor called

    Strategy obj3 = Strategy(100, 120);

    obj2 = obj3;            // Copy assignment operator called
}
```
- Strategy obj2 = obj1;
- Copy constructor is called (object creation + initialization)
- obj2 = obj3;
- Copy assignment operator is called (assignment between already existing objects).
- Copy assignment operator is used when:
    - Both objects already exist
    - One object is assigned to another using = operator

#### Example of Shallow/Deep Copy, Copy constructor,Copy Assignment Operator
```cpp
#include<iostream>
class Box{
   int* len;
public: 
   void Volume(){
    std::cout<<"Volume: "<<(*len)*(*len)*(*len)<<std::endl;
   }

  Box(int length){
    len=new int(length);
  }
  ~Box(){
    delete len;
  }
   
};

class Circle{
  int* radius;

  public:
  void Area(){
    std::cout<<"Area: "<<3.14*(*radius)*(*radius)<<std::endl;
  }

  Circle(int rad){
    radius=new int(rad);
  }

  //  Deep copy constructor
  Circle(const Circle& other){
    radius=new int(*other.radius);
  }

  //Copy Assignment Operator
  Circle& operator=(const Circle& other) {
        // other → reference to the right-hand object
        if (this == &other) //this → points to the object that called the function
            return *this; 

        delete radius;
        radius = new int(*other.radius);
        return *this;
    }

  ~Circle(){
    delete radius;
  }
};
int main(){

  //Shallow Copy Example
  Box b1(10);

  Box b2=b1; //// Copy constructor called

  b1.Volume();

  b2.Volume();

  //Deep Copy Example
  Circle c1(5);
  Circle c2=c1;   // Copy constructor called
  Circle c3(10); 

  c1.Area();
  c2.Area();
  c3.Area();
  
  c3=c1; //c3.operator=(c1);  // Copy assignment operator called
  c3.Area();

  return 0;
}
```
### Destructor
- It is special function, which is executed when an object of class is destroyed 
- It has the **same name as the class**, preceded by a **tilde (`~`)**.
- A destructor has **no return type** and **takes no parameters**.
- It is used to **release resources** such as dynamically allocated memory, files, or network connections.
- A class can have **only one destructor** (destructors cannot be overloaded).
- It is called automatically:
  - When an object goes out of scope
  - When a program ends
  - When `delete` is used on a dynamically allocated object

```cpp
#include<iostream>

class Strategy{
    public:
    int* pInt;

    Strategy(){
        std::cout<<"Constructor Called"<<std::endl;
        pInt=new int(10);
    }

    ~Strategy(){
        std::cout<<"Destructor Called"<<std::endl;
        delete pInt;
    }
};


int main(){

    Strategy obj;
    std::cout<<"Inside main: "<<*obj.pInt<<std::endl;
    {
        Strategy obj1;
        std::cout<<"Inside block: "<<*obj1.pInt<<std::endl;
    }
    std::cout<<"block end here"<<std::endl;
    
    return 0;
}

```
### this
- This is a special pointer to an object which is calling the member function
- It is implicitly passed to all the member function
- this ek pointer hota hai jo current object ka address store karta hai
```cpp
class Strategy {
public:
    int qty;

    void set(int val) {
        qty = val;
    }
};

Strategy s1;
s1.set(10);
//#########################
// Hum likte hai
s1.set(10);
//Compiler internally samajhta hai
Demoxyz_set(&d1, 10);
```
#### Properties/uses of this keyword
- this works as a pointer to the object
- this  is avalible in all the `non-static` member function
- this is a constant pointer
- It is used to differentiate b/w member variable and paramter with same name
- It is used to return the object itself

### static in class

```cpp
#include<iostream>
#include<string>

class OrderBook{
    public:
    int orderQty;
    int price;
    static std::string brokerName;

    OrderBook(int ordderQty,int price){
        this->orderQty=ordderQty;
        this->price=price;
    }
};

std::string OrderBook::brokerName="Rohit";
int main(){
    std::cout<<"Broker Name: "<<OrderBook::brokerName<<std::endl;

    OrderBook ob(100,10);

    std::cout<<ob.brokerName<<std::endl;

    OrderBook ob2(200,5);

    std::cout<<ob2.brokerName<<std::endl;

    return 0;
}
```
#### Static Data Member
- Belongs to the class
- Single copy shared by all objects
```cpp
class A {
public:
    static int x;
};

int A::x = 10;

//access
A::x;
```
#### Static Member Function (no static variable inside)
- Belongs to the class
- Can access only static members
- Cannot access non-static members (this not available)
```cpp
#include <iostream>
using namespace std;

class OrderBook {
public:
    static string brokerName;
    int orderQty;
    static void showBroker() {
        cout << brokerName << endl;// cout << orderQty; // ERROR

    }
};

string OrderBook::brokerName = "Rohit";

int main() {
    OrderBook::showBroker();
}


```

#### Static Function USING Static Member
```cpp
class OrderBook {
public:
    static int count;

    static void increment() {
        count++;
    }
};

int OrderBook::count = 0;
```
#### Static Function HAVING a Static Local Variable
- Static local variable:
    - Created once
    - Retains value between calls
- Scope: function only
- Lifetime: entire program
```cpp
class Test {
public:
    static void counter() {
        static int x = 0;  // local static
        x++;
        cout << x << endl;
    }
};

int main() {
    Test::counter(); // 1
    Test::counter(); // 2
    Test::counter(); // 3
}
```
#### Normal (Non-static) Function with Static Local Variable
- Now the function belongs to objects, but the static variable is still shared
```cpp
class Test {
public:
    void counter() {
        static int x = 0;
        x++;
        cout << x << endl;
    }
};

int main() {
    Test a, b;
    a.counter(); // 1
    b.counter(); // 2
    a.counter(); // 3
}
```
#### Normal Function + Static Class Member
```cpp
class OrderBook {
public:
    static int totalOrders;

    void addOrder() {
        totalOrders++;
    }
};

int OrderBook::totalOrders = 0;

int main(){
OrderBook o1, o2;

o1.addOrder();
o2.addOrder();

cout << OrderBook::totalOrders; // 2

    
}
```
- Function is per-object
- Data is shared
#### rememebr
```bash
Static member variable → shared across objects

Static member function → no this, only static data

Static local variable → remembers value between calls

Non-static function + static variable → still shared

Static function + static variable → shared & class-level
```
```cpp
#include<iostream>
#include<string>
class Strategy{
    private:
    int orderQty;
    static int strategyCount;
    public:
    static std::string companyName;

    Strategy(int Qty):orderQty(Qty){
        std::cout<<"Constructor called"<<std::endl;
    }

    void PlaceOrder(){
        std::cout<<"Placing the order in the market"<<std::endl;
        strategyCount++;
    }

    static void DisplayTotalStrategies(){
        std::cout<<"Total count of strategy\t"<<strategyCount<<std::endl;
    }

    void DisplayQty(){
        std::cout<<"OrderQty:\t"<<orderQty<<std::endl;
    }

    static void DisplayCompanyName(){
        //we can't able to use non-static member inside the static function
        std::cout << "Company:\t" << companyName << std::endl;
    }
};

std::string Strategy::companyName="rohit pvt ltd";
int Strategy::strategyCount=0;

int main(){
    std::cout<<Strategy::companyName<<std::endl;
    Strategy obj(100);
    
    obj.DisplayQty();
    obj.DisplayCompanyName();
    Strategy::DisplayCompanyName();


    Strategy twoleg(200);
    twoleg.PlaceOrder();

    Strategy fourleg(400);
    fourleg.PlaceOrder();

    Strategy::DisplayTotalStrategies();
    
    return 0;
}
```

### Inheritance
- Mechanism to reuse the methods/behaviour of one class to another class
- A `base class` (also called a parent class or superclass) is an existing class from which other classes can inherit. It defines the common properties and behaviors that are shared by all derived classes.

- A `derived class` (also called a child class or subclass) is a class that
inherits from a base class. It can add new properties and behaviors or override
existing ones

[Single Inheritance](#Single-Inheritance)
[Multiple  Inheritance](#multiple--inheritance)
[Multilevel Inheritance](#multilevel-inheritance)
[Hierarchical Inheritance](#hierarchical-inheritance)
[Hybrid Inheritance](#hybrid-inheritance)
[]()

```cpp
 class DerivedClass : access-specifier BaseClass {
// Derived class members
}```

- Example 
```cpp
#include<iostream>

class Base{
    public:
    int x=10;
    void function(){
        std::cout<<"Printing using base class function"<<std::endl;
    }
};

class Derived: public Base{
    public:
    void function1(){
        std::cout<<"Output from derived class "<<std::endl;
        std::cout<<"Value of x : "<<x<<std::endl;
    }
};

int main(){

    Derived d;
    d.function();
    d.function1();

    Base b;
    b.function();
    return 0;
}
```

#### Single Inheritance
- Child class is derived from the single Base Cclass only

```cpp
#include <iostream>
using namespace std;

class Parent {
public:
    void show() {
        cout << "This is Parent class" << endl;
    }
};

class Child : public Parent {
public:
    void display() {
        cout << "This is Child class" << endl;
    }
};

int main() {
    Child c;
    c.show();     // inherited from Parent
    c.display();  // Child's own function
    return 0;
}
```

#### Multiple  Inheritance
- Child class is serived from multiple base classes
```cpp
#include <iostream>
using namespace std;

class A {
public:
    void funcA() {
        cout << "Class A function" << endl;
    }
};

class B {
public:
    void funcB() {
        cout << "Class B function" << endl;
    }
};

class C : public A, public B {
public:
    void funcC() {
        cout << "Class C function" << endl;
    }
};

int main() {
    C obj;
    obj.funcA();
    obj.funcB();
    obj.funcC();
    return 0;
}
```
#### Multilevel Inheritance
- A class is derived from another derived class
```cpp
#include <iostream>
using namespace std;

class GrandParent {
public:
    void gp() {
        cout << "Grandparent class" << endl;
    }
};

class Parent : public GrandParent {
public:
    void p() {
        cout << "Parent class" << endl;
    }
};

class Child : public Parent {
public:
    void c() {
        cout << "Child class" << endl;
    }
};

int main() {
    Child obj;
    obj.gp();
    obj.p();
    obj.c();
    return 0;
}

```
#### Hierarchical Inheritance
- Multiple child classes are derived from one single base class
```cpp
#include <iostream>
using namespace std;

class Base {
public:
    void show() {
        cout << "Base class" << endl;
    }
};

class Child1 : public Base {
public:
    void display1() {
        cout << "Child1 class" << endl;
    }
};

class Child2 : public Base {
public:
    void display2() {
        cout << "Child2 class" << endl;
    }
};

int main() {
    Child1 c1;
    Child2 c2;

    c1.show();
    c1.display1();

    c2.show();
    c2.display2();
    return 0;
}

```

#### Hybrid Inheritance
- Combination of two or more types of inheritance (e.g., multiple + multilevel)
```cpp
#include <iostream>
using namespace std;

class A {
public:
    void funcA() {
        cout << "Class A" << endl;
    }
};

class B : public A {
public:
    void funcB() {
        cout << "Class B" << endl;
    }
};

class C {
public:
    void funcC() {
        cout << "Class C" << endl;
    }
};

class D : public B, public C {
public:
    void funcD() {
        cout << "Class D" << endl;
    }
};

int main() {
    D obj;
    obj.funcA();
    obj.funcB();
    obj.funcC();
    obj.funcD();
    return 0;
}

```
- **Constructors:** When a `derived class object is created`, the `base class constructor` is called `first`, followed by the derived class constructor

- **Destructors:** When a `derived class object is destroyed`, the `derived class destructor is called first`, followed by the base class destructor
- C++ always calls constructors in the order of declaration and destructors in reverse
```cpp
#include <iostream>
using namespace std;

// Base classes
class A {
public:
    A() { cout << "A constructor\n"; }
    ~A() { cout << "A destructor\n"; }
};

class B {
public:
    B() { cout << "B constructor\n"; }
    ~B() { cout << "B destructor\n"; }
};

class C {
public:
    C() { cout << "C constructor\n"; }
    ~C() { cout << "C destructor\n"; }
};

// Derived class inheriting from multiple bases
class D : public A, public B, public C {
public:
    D() { cout << "D constructor\n"; }
    ~D() { cout << "D destructor\n"; }
};

int main() {
    D obj;
    return 0;
}

/*
A constructor
B constructor
C constructor
D constructor
D destructor
C destructor
B destructor
A destructor

*/
```

```bash
| Situation                                                  | What happens                                      |
| ---------------------------------------------------------- | ------------------------------------------------- |
| Object created on stack                                    | Destructors called automatically in reverse order |
| Object created on heap, deleted via derived pointer        | Derived → Base destructors called automatically   |
| Object deleted via base pointer without virtual destructor | Only base destructor called → Undefined behavior  |


```
### Access Modifiers
```bash
| Access specifier | Same class | Derived class | Outside class |
| ---------------- | ---------- | ------------- | ------------- |
| **public**       | ✔️ Yes     | ✔️ Yes        | ✔️ Yes        |
| **protected**    | ✔️ Yes     | ✔️ Yes        | ❌ No          |
| **private**      | ✔️ Yes     | ❌ No          | ❌ No          |


```
- Inheritance of class using access modifiers
```cpp
#include<iostream>
class ParentStrategy{
    public:

    double order_qty;
    double price;

    ParentStrategy(double qty,double price):order_qty(qty),price(price){};
    
    void PriceStrategy(){
        std::cout<<"order_qty:\t"<<order_qty<<std::endl;
        std::cout<<"Price: \t"<<price<<std::endl;
    } 

    void SubmitStrategy(){
        std::cout<<"Submitting the order to the Exchange"<<std::endl;
    }


    protected:
    void ModifyStrategy(){
        std::cout<<"Modifying the strategy"<<std::endl;

    }


    private:
    void CancleStrategy(){
        std::cout<<"Cancel the Startegy "<<std::endl;
    }

};

class Strategy:public ParentStrategy{
    public:
    Strategy(double qty,double price):ParentStrategy(qty,price){};
    
    void CreateStrategy(){
        std::cout<<"Strategy creation is doing...."<<std::endl;
        SubmitStrategy();

        ModifyStrategy();

        //CancleStrategy(); //private member are not allow
    }
};
int main(){
    Strategy s(100,23.50);

    s.PriceStrategy();
    s.SubmitStrategy();
    s.CreateStrategy();

    //s.ModifyStrategy(); // protected member are not allow 

    //s.CancleStrategy();  //private member are not allow
    return 0;
    
}

```

#### Access Modifiers vs Inheritance Modes
- Different modes of inheritance
- Parent class member → How it appears in Child class
- Dabadaba: Private> Protected> Public
```bash
| **Inheritance Mode** | **Public member** | **Protected member** | **Private member** |
| -------------------- | ----------------- | -------------------- | ------------------ |
| **Public**           | Public            | Protected            | ❌ Not accessible   |
| **Protected**        | Protected         | Protected            | ❌ Not accessible   |
| **Private**          | Private           | Private              | ❌ Not accessible   |

```


### Compile vs Run Time Binding
- assume derived class me X function hai, same function Parent class me bhi hai to konsa excute hoga 
#### Compile Time Binding
- Compiler can decide at compile time itself which function to excecute
- Early binding
- 
```cpp
#include<iostream>

class Animal{
  public:
  void Speak(){
    std::cout<<"Speak"<<std::endl;
  }
};
class Dog: public Animal{
  public:
  void Speak(){
    std::cout<<"Bhowwwwwwwwwwwwww"<<std::endl;
  }
};
class Cat:public Animal{
  public:
  void Speak(){
    std::cout<<"Meowwwwwwwwwwwww"<<std::endl;
  }
};
int main(){

  Animal a;
  a.Speak();

  Dog d;
  d.Speak();

  Cat c;
  c.Speak();

  Animal* pA=new Animal();
  pA->Speak();//Speak

  Animal* pAD=new Dog();
  pAD->Speak(); //Speak

  Dog* pDD=new Dog();
  pDD->Speak(); //Bhowwwwwwwwwwwwww

  return 0;
}
```


#### Run Time Binding
- Compiler decides at runtime which function to execute
- Late binding
- It take extra time so we avoid for latency application
- 
```cpp
#include <iostream>
using namespace std;

class Animal {
public:
    virtual void Speak() {   // virtual lagaya
        cout << "Speak" << endl;
    }
    virtual ~Animal(){} // Destructor ko bhi virtual karna best practice hai
};

class Dog : public Animal {
public:
    void Speak() override {  // override optional but good practice
        cout << "Bhowwwwwwwwwwwwww" << endl;
    }
};

class Cat : public Animal {
public:
    void Speak() override {
        cout << "Meowwwwwwwwwwwww" << endl;
    }
};

int main() {
    Animal a;
    a.Speak(); // Speak

    Dog d;
    d.Speak(); // Bhowwwwwwwwwwwwww

    Cat c;
    c.Speak(); // Meowwwwwwwwwwwww

    Animal* pA = new Animal();
    pA->Speak(); // Speak

    Animal* pAD = new Dog();
    pAD->Speak(); // Bhowwwwwwwwwwwwww ✅ runtime polymorphism

    Dog* pDD = new Dog();
    pDD->Speak(); // Bhowwwwwwwwwwwwww

    delete pA;
    delete pAD;
    
    return 0;
}

```

### Virtual function
- A virtual function is a `function in a base class` that can be `overridden in` a `derived class`
- Its key feature: C++ decides at runtime which `function to call` based on the `actual object type`, `not the pointer type`
- This is called runtime polymorphism
- In C++, member variables depend on the pointer (or reference) type, not the actual object type
- Non-virtual function → pointer type hi decide karta hai
- In C++, member functions (if declared virtual) depend on the actual object type at runtime, not the pointer or reference type
- Agar derived class ne override nahi kiya, base class ka function call hoga
- **STORY**
```bash

class Animal {
public:
    virtual void sound() {
        cout << "Animal sound\n";
    }
};

class Dog : public Animal {
public:
    void sound() {
        cout << "Dog barks\n";
    }
};

class Cat : public Animal {
public:
    void sound() {
        cout << "Cat meows\n";
    }
};

//Compile time pe kya banta hai?

Jab koi class me virtual function hota hai, compiler us class ke liye ek vtable (virtual table) banata hai.

Vtable me function pointers hote hain, jo actual function addresses store karte hain.

Vtables banti hain
Animal vtable:
[ Animal::sound ]

Dog vtable:
[ Dog::sound ]

Cat vtable:
[ Cat::sound ]

//Virtual call ka rule banta hai
a->sound();   // sound is virtual
Wo direct jump nahi likhta,
wo likhta hai:
"runtime pe object ke vptr se function uthana"



Animal* a = new Dog();
Runtime pe ye hota hai:

Heap me Dog object ke liye memory allocate
Dog constructor chalta hai
Constructor vptr set karta hai

Dog object memory:
+-------+------------+
| vptr  | Dog data   |
+-------+------------+

vptr → Dog vtable


a->sound();

Ab actual magic
Runtime pe steps:

1. a → Dog object ko point kar raha hai
2. Dog object ke andar ka vptr uthaya
3. vptr → Dog vtable
4. Dog vtable ka sound() slot dekha
5. Usme address mila → Dog::sound
6. Dog::sound() call ho gaya


///Same pointer, different behavior
Animal* a;

a = new Dog();
a->sound();   // Dog barks

a = new Cat();
a->sound();   // Cat meows

THIS is runtime polymorphism


//gar virtual hata do
void sound(); // not virtual

❌ vtable nahi
❌ vptr nahi

Compiler bolega:
"pointer Animal ka hai → Animal::sound()"

```
- Compile time: vtables + rules bante hain
- Runtime: object banta hai → vptr set hota hai
- Call time: vptr decide karta hai kaunsa function chalega



#### Properties of Virtual function

1. **Used for Runtime Polymorphism**  
   - Virtual functions enable **runtime (dynamic) polymorphism** in C++.

2. **Declared with `virtual` Keyword in Base Class**  
   - Only the base class function needs to be declared as `virtual`.

3. **Cannot be Static**  
   - A virtual function **cannot** be declared as `static`.

4. **Should be Used via Reference or Pointer of Base Class**  
   - To get runtime polymorphism effect, call the virtual function using:
     - Base class pointer, or  
     - Base class reference

5. **Not Mandatory for Derived Class to Override**  
   - Derived class may or may not override the base class virtual function.

6. **Always Defined in Base Class**  
   - Base class should provide a definition.  
   - If needed, derived class can **override** it.

#### Advantage of compile time binding
- Performance
- Type safety
- Predictibilty

#### Override
- override ek `compile-time check` hai jo ensure karta hai ki derived class ka function exactly base class ke virtual function ko override kar raha ho
- Ye function base class ke virtual function ko override kar raha hai, base class me function jarur virtaul rhna chahiye hai
- Agar match nahi hua → compile-time error do
- Signature mismatch se bachne ke liye
```cpp
class Derived : public Base {
public:
    void show() override {   // Compiler verify karega
        cout << "Derived class show function" << endl;
    }
};

```

#### final 
##### final with Function
- Agar aap chahte hain ki `koi derived class` kisi function ko override na kar sake, to final use karte hain.
- final ka real matlab tab hota hai jab function virtual ho base class me
```cpp
class Base {
public:
    virtual void show() final {
        cout << "Base show function" << endl;
    }
};

class Derived : public Base {
public:
    void show() override {  // ❌ Error // derived function override nhi kr skta ab
        cout << "Derived show function" << endl;
    }
};
```
##### final with Class
- Agar aap chahte hain ki koi class inherit na ho sake, to class ke sath final lagate hain.
- Yaha virtual ki koi zarurat nahi
```cpp
class Base final { //Is class ko inherit nahi kiya ja sakta
};

class Derived : public Base {  // ❌ Error koi class ab derive nhi kr skta
};
```
### Polymorphism
```bash

Polymorphism
│
├── 1️⃣ Compile-Time Polymorphism (Static Binding)
│   │
│   ├── 🔹 Function Overloading
│   │      - Same function name
│   │      - Different parameter list
│   │      - Same class
│   │
│   └── 🔹 Operator Overloading
│          - Operators ko redefine karna
│          - Same operator
│          - Different behavior for user-defined type
│
└── 2️⃣ Run-Time Polymorphism (Dynamic Binding)
    │
    └── 🔹 Function Overriding
           - Parent class function
           - Child class me same signature
           - virtual keyword required

```
#### Function Overloading
- Same function name butdiffer in parameters

#### Why to use virtual destructor in c++?
- Agar destructor virtual nahi hoga, to sirf base class ka destructor call hoga — derived class ka nahi
- Isse resource leak ho sakta hai (memory leak, file handle leak, etc.)

```cpp
#include <iostream>
using namespace std;

class Base {
public:
    ~Base() {
        cout << "Base Destructor\n";
    }
};

class Derived : public Base {
public:
    ~Derived() {
        cout << "Derived Destructor\n";
    }
};

int main() {
    Base* ptr = new Derived();
    delete ptr;   // Problem here
    //output:  Base Destructor
}

```


- Agar class me koi bhi virtual function hai, to destructor ko bhi virtual bana do




```bash
delete ptr
   ↓
(vtable se) Derived destructor call
   ↓
Derived ka kaam complete
   ↓
Automatic Base destructor call
   ↓
Memory free

```
- Conceptually Derived destructor aisa hota hai
```bash
Derived::~Derived() {
    // Derived cleanup

    Base::~Base();  // compiler automatically call karta hai
}

```

```cpp
#include <iostream>
using namespace std;

class Base {
public:
   virtual ~Base() {
        cout << "Base Destructor\n";
    }
};

class Derived1 : public Base {
public:
    ~Derived1() {
        cout << "Derived1 Destructor\n";
    }
};

class Derived2: public Derived1{
    public:
    ~Derived2(){
        cout<<"Derived2 destructor"<<endl;  }
};



int main() {
    Base* ptr = new Derived2();
    delete ptr;   // Problem here
   
    /*
    //output: 
    Derived2 destructor
    Derived1 Destructor
    Base Destructor
    */
}

```
#### What is Object Slicing in C++?
- Object slicing tab hota hai jab ek derived class object ko base class object me copy kiya jata hai (by value) 
- aur derived ka extra part “cut” ho jata hai
- Isliye isko slicing kehte hain (jaise object ka kuch hissa kat gaya)
- Object slicing happens only with pass by value.
- Derived ka extra data remove ho jata hai.
- Polymorphism break ho jata hai.
- Avoid by using `Base&` or `Base*`

```cpp
#include <iostream>
using namespace std;

class Base {
public:
    virtual void show(){
    cout<<"This is the base class"<<endl;
   }
};

class Derived:public Base{
    public:
    void show(){
        cout<<"This is the derived class"<<endl;
    }
};

void Excute(Base& obj){
    obj.show();
}

int main() {
   
   Derived objDerived;
   Excute(objDerived);
}
```

### Pure Virtual Function
- A pure virtual function ek aisa virtual function hota hai `jiska base class me implementation nahi hota`, aur derived class ko usko implement karna hi padta hai
-  `virtual ReturnType FunctionName(Parameters) = 0;`
```cpp
class Base {
public:
    virtual void show() = 0;   // Pure virtual function
};
```
- = 0 ka matlab hai → function pure virtual hai
- Base class abstract class ban jati hai
- Is class ka object directly create nahi kar sakte
- Mandatory override in Derived class

### Abstract class
- Aisi class jisme `at least ek pure virtual function` ho
- Abstract class = Interface + Some implementation
- Data members ho sakte hain 
- Constructors ho sakte hain 
- Normal functions ho sakte hain 
- Pure virtual functions ho sakte hain 
- Partial implementation de sakti hai 
```cpp
class Vehicle {
protected:
    int speed;

public:
    void start() {   // implemented function
        cout << "Vehicle started\n";
    }

    virtual void drive() = 0;  // pure virtual
};

```

### Interface
- `Sirf pure virtual functions` hote hain
- Koi data member nahi hota (design practice),Usually avoided
- Usually virtual destructor hota hai,Usually avoided
- Partial implementation NO(no logic)
- Interface = Only rules, no logic
```cpp
class Driveable {
public:
    virtual void drive() = 0;
    virtual void stop() = 0;
    virtual ~IDriveable() {}
};
```
#### inline 
- Inline function wo function hota hai jise compiler call karne ke bajay uski body ko directly us jagah insert kar deta hai jahan function call kiya gaya ho
- Isse function call ka extra overhead (jaise stack me jump karna) kam ho jata hai, aur program thoda fast ho sakta hai
```cpp
inline return_type function_name(parameters) {
    // function body
}
```
- Program ki speed badh sakti hai (especially small functions me)
- Function call overhead kam hota hai
- Agar function bada ho to code size badh sakta hai
- Har baar inline ho ye jaruri nahi (compiler decide karta hai)

### Diamond Problem
```bash
class A {
public:
    int x;
};

class B : public A {};

class C : public A {};

class D : public B, public C {};

/////////////////////////////////

        A
       / \
      B   C
       \  /
         D
```
- Diamond problem tab hota hai jab multiple inheritance me ek hi base class do baar inherit ho jati hai
- Solution is `Virtual Base Classes`
### Virtual Base Classes
- Wo base class jo multiple inheritance me ek hi copy share karne ke liye virtual keyword ke saath inherit hoti hai
- Jo class multiple inheritance me virtual keyword ke saath inherit hoti hai, wahi virtual base class ban jaati hai
- Virtual base: Constructor sirf most derived class call karti hai
- Jo class final object banata hai, wahi most derived
- Virtual base constructor → Intermediate base constructors → Most derived constructor
- Virtual base class ka constructor sabse derived object (most derived class) se call hota hai, intermediate base classes nahi
- Yaha A virtual base class hai
```cpp
class A { };

//B aur C → intermediate bases
class B : virtual public A { };
class C : virtual public A { };
class D : public B, public C { }; //D → most derived
```
```bash
    D
   / \
  B   C
   \ /
    A  <- single shared instance

```
- Virtual base class ka constructor pehle call hota hai (A)
- Fir normal base classes (B → C)
- Fir most derived class (D)

### Misc
#### Why do we use const keyword after function declaration
```cpp
class ABC {
    int x = 10;

public:
    void function() const {
        std::cout << x;
        // x = x + 10;  ❌ Error
    }
};
```
- This function promises NOT to modify any data members of the class.
```cpp
void function(int a) const {
    a = a + 10;  // ✅ Allowed
}
```





## Multithreading

### Process
- Process is nothing but a programm/code in excecution
- Executable file run hoti hai tab process banta hai
- - Jab **executable file run hoti hai**, tab OS ek **process** create karta hai
- - Har process ka apna **memory space** aur **resources** hote hain
- Har process ke paas **kam se kam ek thread (main thread)** hota hai
```bash
+--------------------------------------------------+
|                     PROCESS                      |
|                                                  |
|  Code Segment (.text)                            |
|  Initialized Data (.data)                        |
|  Uninitialized Data (.bss)                       |
|  Heap Memory                                     |
|  Stack Memory                                    |
|                                                  |
|  File Descriptors (stdin, stdout, stderr, files) |
|  Environment Variables                           |
|  Process ID (PID)                                |
|  Parent Process ID (PPID)                        |
|  CPU Registers (saved state)                     |
|  Scheduling Information                          |
|                                                  |
|  +-------------+   +-------------+               |
|  |  Thread 1   |   |  Thread 2   |               |
|  |   Stack     |   |   Stack     |               |
|  +-------------+   +-------------+               |
|                                                  |
+--------------------------------------------------+


```
- **Code Segment (.text)**
- Compiled program instructions (read-only)
- **Initialized Data (.data)**
- Global/static variables with initial value
- **Uninitialized Data (.bss)** 
- Global/static variables without init value
- **Heap Memory**
- Dynamic memory allocation (new / malloc)
- Shared among all threads of the process
-  **Stack Memory**
- Stores function calls, local variables, return addresses
- Each thread has its own stack
- **File Descriptors**
- Integer references to open files and I/O resources
- References to open files, stdin/stdout 
- Shared among threads in the same process
- **Environment Variables**
- Key-value pairs used to configure process behavior
- Examples: PATH, HOME, USER
- Inherited by child processes
- **Process ID (PID)**
- Unique identifier assigned to a process by the OS
- Used for process management and signaling
- **Parent Process ID (PPID)**
- PID of the process that created this process
- Helps maintain process hierarchy
- **CPU Registers (Saved State)**
- Stores execution state of the process
- Includes program counter, stack pointer, flags, etc.
- Used during context switching
- **Scheduling Information**
- Priority, state (running, waiting, stopped)
- Determines when and how long the process runs on CPU


### Thread
- Thread is a light-weight process that executes some part of the code
- Multiple threads can exist within the same process
- Threads use the same memory and resources of a process, but each thread runs its own tasks separately

```bash
+----------------------------------+
|              THREAD              |
|                                  |
|  Thread ID (TID)                  |
|  Program Counter (PC)             |
|  CPU Registers                    |
|  Stack (local variables)          |
|                                  |
|  Shares with process:             |
|  - Code Segment                   |
|  - Data Segment                   |
|  - Heap                           |
|  - Open Files                     |
|                                  |
+----------------------------------+

```

```bash

| Process | Thread |
|---------|--------|
| Communication time between two processes is **high** | Communication time between two threads is **less** |
| Process consumes **more resources** | Thread consumes **fewer resources** |
| Termination of one process **does not affect** other processes | If one thread terminates due to an error, **all its threads terminate** |
| Process termination time is **high** | Thread termination time is **less** |
| Process creation time is **high** | Thread creation time is **less** |
| Processes **do not share data** | Threads **share data** |
| Communication between processes takes place using: **Shared memory** or **Message passing** | Communication between threads takes place using: **Shared memory** |


```
### Basic Program of Threading
```cpp
#include<iostream>
#include<thread>
#include<chrono>

void function1(){
    std::cout<<"Hello from Function1"<<std::endl;
    
    std::this_thread::sleep_for(std::chrono::seconds(5));

    std::cout << "Function1 finished" << std::endl;
}

void function2(){
    std::cout<<"Hello from Function2"<<std::endl;
}
void function3(){
    std::cout<<"Hello from Function3"<<std::endl;
}
int main(){

    std::thread t1(function1);
    std::cout<<"Thread t1 created"<<std::endl;

    std::thread t2(function2);
    std::cout<<"Thread t2 created"<<std::endl;

    t1.join(); //WAIT POINT
    std::cout<<"Join t1"<<std::endl;

    std::thread t3(function3);
    std::cout<<"Thread t3 created"<<std::endl;
    t3.join();
    std::cout<<"Join t3"<<std::endl;


    t2.join();
    std::cout<<"Join t2"<<std::endl;


    return 0;
}
```
```bash
# To run it
g++ -pthread main.cpp
```

### Passing Values to a Thread Function
```cpp
#include<iostream>
#include<thread>
#include<chrono>

void quantumCalculation(int a, int b){
    int msec=0;
    while(msec<100){
        std::cout<<"Calculating Quantum Addition...."<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        msec++;
    }

    std::cout<<"Final calculation: "<<a+b<<std::endl;
}

void quantumCalculationMul(int a, int b){
    int msec=0;
    while(msec<500){
        std::cout<<"Calculating Quantum Multiply...."<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        msec++;
    }

    std::cout<<"Final calculation Multiply: "<<a*b<<std::endl;
}
int main(){

    std::thread t1(quantumCalculation,10,10);
    std::thread t2(quantumCalculationMul,50,10);

    t1.join();
    t2.join();
    return 0;
}
```

### Critical Section
- Critical section is part of code where two processes/threads share the common resources 
- Example printer,CPU(shared data structures),Shared variables / memory
-  due to this Race Condition Occur
- **critical section problem**
```cpp
#include<iostream>
#include<thread>

int sharedVariable=0;

void functionInc(){
    std::cout<<" "<<sharedVariable<<" "<<std::endl;
    sharedVariable++;
}
int main(){

    std::thread arrThreads[5];

    for(int i=0;i<5;i++){
        arrThreads[i]= std::thread(functionInc);
    }

    for(int i=0;i<5;i++){
        arrThreads[i].join();
    }

    return 0;
}
```
```cpp
#include<iostream>
#include<thread>
#include<chrono>

int balance=100;
void Deposite(int amt){
    int temp=balance;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    temp=temp+amt;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    balance=temp;
}

int main(){

    std::thread t1(Deposite,50);
    std::thread t2(Deposite,100);
    std::thread t3(Deposite,10);
    std::thread t4(Deposite,10);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    std::cout<<"Balance: "<<balance<<std::endl;

    return 0;
}
```

### Mutex
- Mutex is a synchronization primtive used to protect `shared resource` being accessed by multiple threads/process simultaneously
- Har `shared resource` ke liye alag mutex
- Mutex protects data, not function
- Same mutex object ko multiple functions me use kar sakte ho
BUT sirf us shared resource ko protect karne ke liye
- Multiple mutex + different lock order → `deadlock` almost guaranteed
- Lock multiple mutex in same order everywhere
```cpp
#include<iostream>
#include<thread>
#include<chrono>
#include<mutex>

int balance=100;
std::mutex mtx;
void Deposite(int amt){
    mtx.lock();
    
    int temp=balance;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    temp=temp+amt;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    balance=temp;

    mtx.unlock();
}

int main(){

    std::thread t1(Deposite,50);
    std::thread t2(Deposite,100);
    std::thread t3(Deposite,10);
    std::thread t4(Deposite,10);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    std::cout<<"Balance: "<<balance<<std::endl;

    return 0;
}
```

### Different Types of Mutex
1. Mutex
2. recuresive mutex
3. timed mutex
4. recursive time mutex
5. shared mutex
6. shared timed mutex





















