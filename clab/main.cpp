#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
   std::cout<<std::setfill('-');

   std::cout<<std::setw(10)<<"Hello"<<std::endl;
   std::cout<<std::setw(10)<<"hey"<<std::endl;

   std::cout<<std::setfill('=');

   std::cout<<std::setw(10)<<"R"<<std::endl;
   std::cout<<std::setw(10)<<"1234567890"<<std::endl;
   std::cout<<std::setw(10)<<"12345678901112"<<std::endl;
/*
-----Hello
-------hey
=========R
1234567890
12345678901112
*/

// -------------------------
    // right alignment
    // -------------------------
    cout << "===== RIGHT ALIGNMENT =====\n";

    cout << setfill('-');

    cout << "|" << setw(10) << "Hi" << "|\n";
    cout << "|" << setw(10) << "Hello" << "|\n";
    cout << "|" << setw(10) << "Welcome" << "|\n";

    cout << endl;

    // -------------------------
    // left alignment
    // -------------------------
    cout << "===== LEFT ALIGNMENT =====\n";

    cout << left;

    cout << "|" << setw(10) << "Hi" << "|\n";
    cout << "|" << setw(10) << "Hello" << "|\n";
    cout << "|" << setw(10) << "Welcome" << "|\n";

    cout << endl;

    // -------------------------
    // right alignment again
    // -------------------------
    cout << "===== RIGHT AGAIN =====\n";

    cout << right;

    cout << "|" << setw(10) << "Hi" << "|\n";
    cout << "|" << setw(10) << "Hello" << "|\n";

    cout << endl;

    // -------------------------
    // setfill change
    // -------------------------
    cout << "===== setfill('*') =====\n";

    cout << setfill('*');

    cout << "|" << setw(10) << "A" << "|\n";
    cout << "|" << setw(10) << "ABC" << "|\n";

    cout << endl;

    // -------------------------
    // width equal and greater
    // -------------------------
    cout << "===== WIDTH TEST =====\n";

    cout << "|" << setw(10) << "1234567890" << "|\n";
    cout << "|" << setw(10) << "123456789012345" << "|\n";

}