#include<iostream>

class Student{
    private:
    std::string student_name;
    int mark;

    public:
    Student(std::string name,int mark):student_name(name),mark(mark){}

    friend void checkAndVerifyResult(const Student& s);
};

void checkAndVerifyResult(const Student& student){
    std::cout<<"Student Name: "<<student.student_name<<std::endl;
    std::cout<<"Marks: "<<student.mark<<std::endl;

    if(student.mark>=35){
            std::cout<<"Status: Pass"<<std::endl;
    }else{
            std::cout<<"Status: Fail"<<std::endl;
    }

}

int main(){
    Student rohit("rohit",78);
    checkAndVerifyResult(rohit);

    Student rahul("rahul",34);
    checkAndVerifyResult(rahul);

    return 0;
}