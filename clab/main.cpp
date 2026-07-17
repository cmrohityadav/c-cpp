#include <iostream>
using namespace std;
void fun(int)
{
    cout << "int";
}

void fun(char*)
{
    cout << "pointer";
}

// int main()
// {
//     fun(nullptr);
// }
int main()
{
        fun(0);
        fun(nullptr);
}