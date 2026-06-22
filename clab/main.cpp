#include <iostream>
#include<vector>
int main()
{
    std::vector<int>ltp={1,2,3,4,5};
    for(int& x:ltp){
          x+=10;
    }

    for(int x:ltp){
         std::cout<<x<<std::endl;
    }
    return 0;
}