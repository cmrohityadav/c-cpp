#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    ofstream objWriteInFile;
    objWriteInFile.open("objWriteInFile.txt");

    vector<int> vct(5);
    cout << "Enter numbers : ";
    for (int i = 0; i < 5; i++)
    {
        cin >> vct[i];
    }
    cout << endl;
    cout << "Entered Value : ";

    for (int i = 0; i < 5; i++)
    {
        cout << vct[i] << " ";
    }
    cout << endl;

    objWriteInFile << "Original Data :";
    for (int i = 0; i < 5; i++)
    {
        objWriteInFile << vct[i] << " ";
    }

    // applying sorting
    sort(vct.begin(), vct.end());
    cout << "Sorted Value : ";

    for (int i = 0; i < 5; i++)
    {
        cout << vct[i] << " ";
    }
    cout << endl;
    objWriteInFile << "\nSorted5  Data :";
    for (int i = 0; i < 5; i++)
    {
        objWriteInFile << vct[i] << " ";
    }

    return 0;
}
