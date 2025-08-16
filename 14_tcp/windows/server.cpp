#include<iostream>
#include<WinSock2.h>
using namespace std;

/*
    //initialize winsock lib

    //create the socket

    //get ip and port

    // bind the ip/port with the socket


    //listen on the socket


    //accept 

    //recv andd send

    //close socket 

    //cleanup the winsock


*/

#pragma comment(lib,"win2_32.lib")
bool Initialize(){
    WSADATA data;

    return WSAStartup(MAKEWORD(2,2),&data)==0;

}
int main(){
    if(!Initialize()){
        cout<<"winsock initialization failed"<<endl;

    }
    
    cout<<"Server program"<<endl;

    

    WSACleanup();
    return 0;
}