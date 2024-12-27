#include<iostream>
#include<fstream>
#include <unistd.h>
using namespace std;

int main()
{
    cout<<"Wait Reading Data from File"<<endl;
    

    ifstream objReadDataFromFile;
    objReadDataFromFile.open("read.txt");

    string sLineFromFile;

    while(getline(objReadDataFromFile,sLineFromFile)){
        cout<<sLineFromFile<<endl;
        sleep(1);
    }

    cout<<"Reading Data Sucessfull"<<endl;


    return 0;
}
