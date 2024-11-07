#include<iostream>
using namespace std;


class BankAccount{
    private:
    string sAccountNumber;
    double dBalance;

    public:
    BankAccount(string sAccNum,double dInitialBalance){
        sAccountNumber=sAccNum;
        dBalance=dInitialBalance;
    }

    //getter
    double getBalance()const{
        return  dBalance;
    }

    //method to deposit money
    void deposit(double dAmount){
        if(dAmount>0){
            dBalance+=dAmount;
            cout<<"Deposited Amount :"<<dAmount<<endl;
        }else{
            cout<<"Invalid deposit amount"<<endl;
        }
    }

    //withdraw
    void withdraw(double dAmount){
        if(dAmount>0 && dAmount<=dBalance){
            dBalance-=dAmount;
        }else{
            cout<<"Invalid Withdrawn Amount"<<endl;
        }
    }

};
int main()
{
    BankAccount myAcccount("123456",5000);

   cout<< myAcccount.getBalance()<<endl;

   myAcccount.deposit(10000);
   cout<< myAcccount.getBalance()<<endl;


    return 0;
}
