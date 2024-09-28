#include <iostream>
#include <string>
using namespace std;

int main()
{

    string cUserTea;
    int teaQuantity;
    cout << "What would you like to order" << endl;

    getline(cin, cUserTea);

    cout << "how man cups " << cUserTea << " would you like to hvae?";

cin>>teaQuantity;
cout<<teaQuantity<<endl;
cout<<cUserTea<<endl;
     return 0;
}
