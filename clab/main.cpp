#include<iostream>
using namespace std;
class Base {
public:
    virtual void f() { cout << "Base\n"; }
};

class Derived : public Base {
    void f(){
      cout << "Derived\n";
    }
};

int main() {
    Base* ptr = new Derived();
    ptr->f(); // ✅ Output: Base
}
