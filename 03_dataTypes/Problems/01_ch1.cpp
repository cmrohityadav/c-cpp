// Tea Information Display Write a program that declares variables to store the type of tea, its price per kilogram (float), and its rating (char). Use data types effectively and print them in a formatted output using escape sequences.
#include<iostream>
#include<string>
int main(){
    std::cout<<"Enter Type of chai\n";
    std::string sTypeOfChai;
    getline(std::cin,sTypeOfChai);
    
    std::cout<<"price of chai \n";
    float fPriceOfChai;
    std::cin>>fPriceOfChai;

    char cGradeOfChai;
    std::cout<<"enter the grad of chai"<<std::endl;
    std::cin>>cGradeOfChai;

    std::cout<<"You have "<< sTypeOfChai<< " of "<<fPriceOfChai<< " and its grade is "<<cGradeOfChai;








    return 0;
}