
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