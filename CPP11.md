
# Content
- []()
- []()
- []()
- []()
- [Move Semantic](#move-semantic)
## auto keyword
- compiler  variable ka type khud determine (deduce) karta hai
- auto use karne par compiler initializer dekhkar type decide karta hai
- Initializer dena mandatory hai
- `auto variable_name = value;`
```cpp
#include<iostream>

int main(){

   auto scrip="TCS"; // const char*
   auto ltp=2044.55; //double
   auto qty=105; //int

   std::cout<<"Stock Name: "<<scrip<<std::endl;
   std::cout<<"Stock LTP: "<<ltp<<std::endl;
   std::cout<<"Stock Qty: "<<qty<<std::endl;

    return 0;
}
```
- Using auto with STL Iterator
```cpp
// Without auto
std::vector<int>::iterator it = v.begin();

// With auto
auto it = v.begin();
```

- `decltype` C++ ka keyword hai jo kisi expression ka type nikalta hai
```cpp
template <typename T, typename U>
auto multiply(T a, U b) -> decltype(a * b) {
    return a * b;
}
```

- [C++ 14 ](/CPP14.md#auto)


## Range based loop
- Its simplifies iterating over coolections like arrays, vectors and other containers(array,vector,list,set,map,unordered_map,string,custom containers)
```cpp

for(element_declaration:collection){
    //Codetoexecute
}

vector<int> v = {1, 2, 3, 4};

for (int x : v) { //Here x is copy
    cout << x << " ";
}

//Compiler roughly isko convert karta hai bus samjhne k liye
auto begin = v.begin();
auto end = v.end();

for (; begin != end; ++begin) {
    int x = *begin;
}
```
- Copy Hoti Hai
```cpp
#include <iostream>
#include<vector>
int main()
{
    std::vector<int>ltp={1,2,3,4,5};
    for(int x:ltp){
          x+=10;
    }

    for(int x:ltp){
         std::cout<<x<<std::endl;
    }
    return 0;
}
```
- Reference Use Karo Agar Modify Karna Hai
```cpp
#include <iostream>
#include<vector>
int main()
{
    std::vector<int>ltp={1,2,3,4,5};
    for(int& x:ltp){
          x+=10;
    }

    for(int x:ltp){
         std::cout<<x<<std::endl;
    }
    return 0;
}

// Most Used in Production)
for (const int &x : ltp) { //Agar sirf read karna hai
    cout << x << " ";
}
```
### NOTES
- Avoid Modifying During Range Based Loop Iteration
- Modifying the range (e.g., adding or removing elements) while iterating can lead
to undefined behavior


## nullptr
### 0
- Purane C++ me 0 ko null pointer ke liye bhi use kiya jata tha
```cpp
int* ptr = 0;
```
- Pointer kisi valid memory ko point nahi kar raha
- Lekin 0 asal me integer literal hai
- `int x=0;`
- Yahan bhi 0 integer hai
- To compiler ko context dekhna padta tha
### NULL
- Above confusion ko kam karne ke liye C/C++ me NULL introduce hua
- `int *ptr = NULL;`
```txt
Kai compilers me:

#define NULL 0

int *ptr = NULL; means  int *ptr = 0;

// Problem
void fun(int)
{
    cout << "int";
}

void fun(char*)
{
    cout << "pointer";
}

int main()
{
    fun(NULL);
}
```

### nullptr
- `T* ptr = nullptr;` // ptr is a null pointer of type T*
```cpp
int* ptr = nullptr;

int x=nullptr; //Error: cannot convert null ptr to int
```
- Its new keyword `nullptr`
- Ye integer nahi hai
- Ye ek special null pointer literal hai
- nullptr ka apna alag type hota hai jiska naam hai: `std::nullptr_t`
- Ye har pointer type (int*, char*, double*, void*, etc.) me automatically convert ho sakta hai
- Ye integers ya floating-point types me convert nahi hota, isliye type-safe hai


## Uniform Initialization
- Uniform Initialization, also known as brace initialization or list initialization, was introduced in C++11 to provide a single, consistent, and intuitive way to initialize objects
- Using curly braces ({}), programmers can initialize a wide variety of data types, including: Variables,Arrays,Structures (struct),Classes,Standard Library containers (such as std::vector, std::array, and std::map)

- `type variable{value};`
```cpp
int x{10};
double pi{3.14159};
char grade{'A'};
bool flag{true};
std::string s{"Hello"};
Point p{1,2};
std::vector<int> v{1,2,3,4};
int arr[]{1,2,3};
int* ptr = new int{42};
auto x{42};
```
### Why we need Uniform Initialization
1. Too many initialization syntaxes(IN OLD C++)
```cpp
int a = 5;
int b(5);

std::string s("abc");

Point p(1,2);

int arr[] = {1,2,3};
```
2. Prevent narrowing conversions
```cpp
int x = 3.9;
// x = 3
// The decimal part disappears : No warning is required

// With Braces
int x{3.9};
// Compiler error!

```
3. Initialize everything the same way

```cpp
class Student
{
public:
    Student(std::string name,int age)
    {
    }
};

Student s{"Bob",20};
```
- The constructor is still called
- Braces don't remove constructors
- They just change the syntax
-  std::initializer_list


## constexpr
- It is a powerful feature that enables compile-time evaluation of expressions, functions, and objects
- By marking variables,functions, and objects as constexpr, you instruct the compiler to evaluate them at
compile time, leading to potential performance improvements, reduced runtime
overhead, and enhanced code safety
### constexpr Variables
```cpp
// constexpr T variable = value;
constexpr int x = 42; // x is a compile-time constant
```

### function
- Agar tumhare paas saari information compile time pe hai, to mera function abhi hi execute kar do. Program run hone ka wait mat karo
- Compile-time execution me sirf wohi kaam allowed hain jo compiler khud calculate kar sake
```cpp
constexpr T function_name(parameters) {
// Function body
}

```
```cpp
// Normal

#include <iostream>
int square(int x){
    return x*x;
}
int main()
{
    int num=square(5);
    std::cout<<num<<std::endl;

    return 0;
}
/*
Compile Time
--------------
Function ban gaya

Run Time
--------------
square(5)
25
*/


// constexpr
#include <iostream>
constexpr int square(int x){
    return x*x;
}
int main()
{
    constexpr int num=square(5);
    std::cout<<num<<std::endl;

    return 0;
}

```
- Rule for Compile-time evaluation
1. Function compile-time executable hona chahiye
2. Arguments compile-time known hone chahiye
3. Agar context compile-time demand karta hai, to compiler ko compile time pe evaluate karna hi padega

## Lambda Expressions
- Ek chhota anonymous (naam bina) function jo wahi par bana aur wahi use ho gaya
- Compiler lambdas ko mostly inline kar deta hai
- Overuse mat karo
```cpp

[capture](parameters)->returnType{
    body
}

auto sum = [](int a,int b){
    return a+b;
};

```
### capture [] 
- Outside ke kaunse variables andar laane hain?
- Default  bahar ka kuchh bhi access nhi
#### Capture by Value [=]
- Captures all variables by value. The lambda creates a copy of each variable.
- sab de do par by Value(copy)
```cpp
int x=10;

auto f=[=](){ //Sabki photocopy lao
    cout<<x;
};
```

#### Capture by Reference [&]
- Captures all variables by reference. The lambda accesses the original variables
- sab dedo par  by reference 
```cpp
int x=10;

auto f=[&](){ //Sab original lao
    x++;
};
```

#### Specific Capture
- Captures specific variables by value or reference
- [a,&b]
- a ki copy dedo
- b original dedo

#### Mixed Capture
- Combines capture by value and capture by reference
- [=,&b]
- Sabki copy
- Except b
- b original
#### Capture `this`
- Captures the this pointer to access member variables and functions of the enclosing class.
```cpp
class MyClass {
    int value = 42;
    public:
    void print() {
        auto lambda = [this]() { std::cout << value; };
        lambda();
    }
};
```
### Parameters 
- bilkul normal function jaise
### return
```cpp
auto add=[](int a ,int b) -> int{
    return a+b;
};
```

### Uses of Lambda Expressions
#### Passing Behavior to Algorithms
- Algorithms (sort, for_each, transform, count_if) ko behavior dene ke liye sabse zyada use hota hai
```cpp
std::vector<int> vec={3,1,4,1,5};

std::sort(vec.begin(),vec.end(),[](int a,int b){return a>b;});
```
#### Event Handling and Callbacks
```cpp
button.onClick([](){
    cout<<"Button clicked";
});
```
- Callback = Ek function jo tum kisi dusre function ko dete ho, taaki woh us function ko baad me jab zarurat ho tab call kare
- Abhi function mat chalao. Main (system/library) jab sahi time samjhu, tab ise call karunga
```cpp
#include <iostream>

void execute(void (*func)()) {
    std::cout << "Before callback\n";

    func();

    std::cout << "After callback\n";
}

int main() {
    execute([]() {
        std::cout << "I am callback\n";
    });
}
```
## Move Semantic
- Copy Nah kro, Ownership transfer kar do
```txt
Lvalue
↓
Naam wala object
↓
Copy hota hai

-------------------------

Rvalue
↓
Temporary object
↓
Move ho sakta hai

-------------------------

&&
↓
Rvalue Reference

-------------------------

std::move()
↓
Object ko rvalue ki tarah treat karo
(copy nahi, move constructor ko chance do)

-------------------------

Move Constructor
↓
Pointer/Resource transfer
↓
Old object -> nullptr

-------------------------

std::forward()
↓
Template mein original nature preserve karta hai
Lvalue -> Lvalue
Rvalue -> Rvalue
```
### Lvalue
```txt
Jiska naam ho

int x = 10;

Yahaan: x
ek lvalue hai

Kyun?

Dobara use kar sakte ho
Kyuki iska naam hai.
Memory location hai

```

### Rvalue
```txt
Temporary value.

10

Ya

5 + 3

Ya

x + 2

Ye sab temporary values hain.
Inka koi naam nahi hota
Memory permanently nahi

```
```cpp
int a = 5;

a            // lvalue

20           // rvalue

a+5          // rvalue

a*2          // rvalue

std::string("Hello")   // rvalue
```

### Lvalue reference
### Rvalue reference
```cpp
int &&r = 5 + 3;
```
### move constructor and destructure
```cpp
#include<iostream>
#include<cstring>
class RString{
    char* data;
    public:

    // move constructor
    RString(RString&& righthHandVar){
        std::cout<<"Move constructor Called \n"<<std::endl;

        data=righthHandVar.data;  // Pointer transfer

        righthHandVar.data=nullptr; // Old object empty

    }

    //Move Assigment
    RString& operator=(RString&& rightHandVar){
        std::cout<<"Move Assigment Called \n"<<std::endl;

         if (this != &rightHandVar)
        {
            delete[] data;       // Purani memory hatao

            data = rightHandVar.data;   // Ownership transfer

            rightHandVar.data = nullptr;
        }

        return *this;
    }

    public:
    RString(const char* str){
        std::cout<<"Constructor Called \n"<<std::endl;
        
        data=new char[strlen(str)+1];
        strcpy(data,str);

    }

    ~RString(){
        std::cout<<"Destructor called"<<std::endl;
        delete[] data;
    }

    RString(const RString& other)
    {
        std::cout << "Copy Constructor Called\n";

        data = new char[strlen(other.data) + 1];
        strcpy(data, other.data);
    }

    RString& operator=(const RString& other)
    {
        std::cout << "Copy Assignment Called\n";

        if (this != &other)
        {
            delete[] data;

            data = new char[strlen(other.data) + 1];
            strcpy(data, other.data);
        }

        return *this;
    }

    void Print(){
        if(data){
            std::cout<<data<<std::endl;
        }else{
            std::cout<<"Empty Object"<<std::endl;
        }
    }
};
int main(){
    
    RString myname("Rohit");

    std::cout << "\nBefore Move\n";
    myname.Print();

    std::cout << "\nMove Constructor\n";

    RString s2 = std::move(myname);

    myname.Print();
    s2.Print();

    std::cout << "\nMove Assignment\n";

    RString s3("Programming");

    s3 = std::move(s2);

    s2.Print();
    s3.Print();

    return 0;
}
```
### std::move
- yeh compiler ko bolta hai: Is object ko ab temporary (rvalue) ki tarah treat karo
- Kyunki isi wajah se compiler copy constructor ki jagah move constructor choose karta hai
- Agar possible ho to is object ko copy mat karo, move kar lo
- std::move kuch move nahi karta. Ye sirf object ko rvalue bana kar compiler ko batata hai ki "is object ko agar type support karta hai, to copy ki jagah move constructor/assignment use kar lo." Actual data ya ownership transfer std::move nahi, balki us type ka move constructor ya move assignment operator karta hai
- std::move internally kya hai?
```cpp
template<typename T>
T&& move(T& obj)
{
    return static_cast<T&&>(obj);
}
```
- Data move tab hota hai jab move constructor ya move assignment operator call hota hai
- Kab std::move use kare?
- Jab tum object ko aage use nahi karna chahte
- Example: dost ko bag dena hai
```txt
Option 1: Copy

Tum bag ki saari books ki photocopy karwao.

Tum
 |
Bag
 |
Books
Laptop
Notebook

↓

Copy

Tum                  Dost
 |                     |
Bag                  Bag
 |                     |
Books               Books
Laptop              Laptop
Notebook            Notebook

Sab kuch duplicate ho gaya.

Ye expensive hai.

Time bhi laga.
Memory bhi lagi.



Option 2: Move

Tum seedha bag usko de do.

Before

Tum
 |
Bag

↓

Move

Tum         Dost
 |            |
Empty       Bag

Na copy hui.
Na memory lagi.

Sirf ownership transfer hui.

Yehi Move Semantics hai.

```



### std::forward

