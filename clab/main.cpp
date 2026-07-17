#include <iostream>
#include<vector>
int main()
{
        auto add =[](auto x,auto y){ return x+ y;};
        std::cout<<add(10,20)<<std::endl;

        std::vector<int>v={0,1,2,3,4,5};

        for( int  value:v){

            std::cout<<value<<" ";
        }
        std::cout<<" \n";
        for( int  value:v){
            
            value+=10;
        }

        for( int  value:v){

            std::cout<<value<<" ";
        }
        std::cout<<" \n";
        std::cout<<" \n After ref \n";
        for( int& value:v){
            
            value+=10;
        }
        for( int  value:v){

            std::cout<<value<<" ";
        }
        std::cout<<" \n";

}