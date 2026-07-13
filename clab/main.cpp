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