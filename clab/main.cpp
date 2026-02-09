
#include<iostream>
#include<memory>
int main(){

  std::shared_ptr<int>ptr1=std::make_shared<int>(10);

  {
    std::cout<<ptr1.use_count()<<std::endl;
    std::shared_ptr<int>ptr2=ptr1;
    std::cout<<ptr1.use_count()<<std::endl;
    std::cout<<ptr2.use_count()<<std::endl;
    {
      std::shared_ptr<int>ptr3=ptr2;
      std::cout<<ptr3.use_count()<<std::endl;
      std::cout<<ptr1.use_count()<<std::endl;


    }


  
  }
  return 0;
}