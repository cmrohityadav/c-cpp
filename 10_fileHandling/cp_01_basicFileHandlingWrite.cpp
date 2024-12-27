#include<iostream>
#include <fstream>

using namespace std;

int main(){
    
    ofstream fout; //To open file(write data)
    fout.open("write.txt");

    fout<<"This is line 1\n";
    fout<<"This is line 2\n";
    fout.close();

    return 0;
}