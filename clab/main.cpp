#include<iostream>
#include<cstring>
using namespace std;
int main(){

    char name[]="rohit";

    // strlen(name) 
    cout<<strlen(name)<<endl; // 5

    char dest[20];

    // strcpy(dest,src); //src se dest me pura data copy kr deta hai jo risky hai,agar dest k pass kam memory hai to buffer over flow hoga, program ka bevaiour undefined ho jayega
    strcpy(dest,name);

    cout<<dest<<endl;


    char destlimitcharcopy[3];

    // strncpy(dest,src,number_of_byte) //limited characters copy karna
    // strncpy() agar n characters copy karta hai,
    // to zaroori nahi ki '\0' add kare.
    // Isliye manually '\0' add kar sakte hain.
    strncpy(destlimitcharcopy,name,2);
    destlimitcharcopy[2] = '\0'; //yeh hamesha null-terminate nahi karta
    cout<<destlimitcharcopy<<endl;


    int value=strcmp("ABC","abc"); //// poori strings compare
    // Yeh str1 and str2 ko compare krta hai, Wo bhi CASE SENSTIVE
    // agar str1==str2 ==> 0
    // agar str1>str2  ==> +ve
    // agar str1<str2  ==> -ve
    // exact +1 ya -1 return karna guaranteed nahi karta
    cout<<"Value : "<<value<<endl;

    // strncmp(str1,str2,size)  // first n characters compare

    // strcasecmp(str1,str2) // case-insensitive comparison 
    // Non-standard / POSIX function


    char* result=strchr(name,'h'); //Character search karna
    // agar wo character(h) mila to uska pointer return hoga
    if(result!=nullptr){
        cout<<"Character found"<<endl;
        cout<<result<<endl;
    }else{
        cout<<"Character NOT found"<<endl;
    }


    //char* result= strstr(sentence,"rohit") → ek poori string/substring search karta hai





    return 0;
}