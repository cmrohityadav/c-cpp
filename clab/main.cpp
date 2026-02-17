#include<iostream>
class Box{
   int* len;
public: 
   void Volume(){
    std::cout<<"Volume: "<<(*len)*(*len)*(*len)<<std::endl;
   }

  Box(int length){
    len=new int(length);
  }
  ~Box(){
    delete len;
  }
   
};

class Circle{
  int* radius;

  public:
  void Area(){
    std::cout<<"Area: "<<3.14*(*radius)*(*radius)<<std::endl;
  }

  Circle(int rad){
    radius=new int(rad);
  }

  //  Deep copy constructor
  Circle(const Circle& other){
    radius=new int(*other.radius);
  }

  //Copy Assignment Operator
  Circle& operator=(const Circle& other) {
        if (this == &other)
            return *this;

        delete radius;
        radius = new int(*other.radius);
        return *this;
    }

  ~Circle(){
    delete radius;
  }
};
int main(){

  //Shallow Copy Example
  Box b1(10);

  Box b2=b1; //// Copy constructor called

  b1.Volume();

  b2.Volume();

  //Deep Copy Example
  Circle c1(5);
  Circle c2=c1;   // Copy constructor called
  Circle c3(10); 

  c1.Area();
  c2.Area();
  c3.Area();
  
  c3=c1; //c2.operator=(c1);  // Copy assignment operator called
  c3.Area();

  return 0;
}