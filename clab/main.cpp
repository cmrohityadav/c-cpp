#include<iostream>

class Strategy{
    public:
    int* pInt;

    Strategy(){
        std::cout<<"Constructor Called"<<std::endl;
        pInt=new int(10);
    }

    ~Strategy(){
        std::cout<<"Destructor Called"<<std::endl;
        delete pInt;
    }
};


int main(){

    Strategy obj;
    std::cout<<"Inside main: "<<*obj.pInt<<std::endl;
    {
        Strategy obj1;
        std::cout<<"Inside block: "<<*obj1.pInt<<std::endl;
    }
    std::cout<<"block end here"<<std::endl;
    
    return 0;
}