#include<iostream>
#include<cstring>
class RString{
    char* data;
    public:

    // move constructor
    RString(RString&& righthHandVar){
        std::cout<<"Move constructor Called \n"<<std::endl;

        data=righthHandVar.data;  // Pointer transfer

        righthHandVar.data=nullptr; // Old object empty

    }

    //Move Assigment
    RString& operator=(RString&& rightHandVar){
        std::cout<<"Move Assigment Called \n"<<std::endl;

         if (this != &rightHandVar)
        {
            delete[] data;       // Purani memory hatao

            data = rightHandVar.data;   // Ownership transfer

            rightHandVar.data = nullptr;
        }

        return *this;
    }

    public:
    RString(const char* str){
        std::cout<<"Constructor Called \n"<<std::endl;
        
        data=new char[strlen(str)+1];
        strcpy(data,str);

    }

    ~RString(){
        std::cout<<"Destructor called"<<std::endl;
        delete[] data;
    }

    RString(const RString& other)
    {
        std::cout << "Copy Constructor Called\n";

        data = new char[strlen(other.data) + 1];
        strcpy(data, other.data);
    }

    RString& operator=(const RString& other)
    {
        std::cout << "Copy Assignment Called\n";

        if (this != &other)
        {
            delete[] data;

            data = new char[strlen(other.data) + 1];
            strcpy(data, other.data);
        }

        return *this;
    }

    void Print(){
        if(data){
            std::cout<<data<<std::endl;
        }else{
            std::cout<<"Empty Object"<<std::endl;
        }
    }
};
int main(){
    
    RString myname("Rohit");

    std::cout << "\nBefore Move\n";
    myname.Print();

    std::cout << "\nMove Constructor\n";

    RString s2 = std::move(myname);

    myname.Print();
    s2.Print();

    std::cout << "\nMove Assignment\n";

    RString s3("Programming");

    s3 = std::move(s2);

    s2.Print();
    s3.Print();

    return 0;
}