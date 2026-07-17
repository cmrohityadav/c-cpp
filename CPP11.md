
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
