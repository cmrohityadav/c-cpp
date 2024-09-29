#include <iostream>
using namespace std;
/*

and/&&

 or/||

*/
int main()
{

    bool bIsStudent;
    int iCups;
    cout << "Are you a student (1 for YES and 0 for NO)\n";
    cin >> bIsStudent;
    cout << "How many cups of tea have you purchased\n";
    cin >> iCups;

    if (bIsStudent || iCups > 15)
    {
        cout<<"You are eligible for discount\n";
    }
    else
    {
        cout << "You are NOT eligible for discount\n";
    }
    return 0;
}
