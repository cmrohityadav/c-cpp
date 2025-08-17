#include<iostream>
#include<WinSock2.h>
#include<WS2tcpip.h>
#include<tchar.h>
#include<thread>
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

// #pragma comment(lib,"win2_32.lib")
#pragma comment(lib,"ws2_32.lib")
bool Initialize(){
    WSADATA data;

    return WSAStartup(MAKEWORD(2,2),&data)==0;

}

void InteractWithClient(SOCKET clientSocket){
    //send or recv client
    
    cout<<"Client connected"<<endl;

    char buffer[4096];
    while(1){
        int bytesRecv=recv(clientSocket,buffer,sizeof(buffer),0);
        if(bytesRecv<=0){
            cout<<"client disconnected"<<endl;
            break;
        }
        string message(buffer,bytesRecv);
        cout<<"message from client : "<<message<<endl;

    }

    closesocket(clientSocket);
}
int main(){
    if(!Initialize()){
        cout<<"winsock initialization failed"<<endl;
        return 1;
    }
    
    cout<<"Server program"<<endl;

    SOCKET listenSocket=socket(AF_INET,SOCK_STREAM,0);

    if(listenSocket==INVALID_SOCKET){
        cout<<"socket creation failed"<<endl;
        return 1;
    }

    //create address structure
    sockaddr_in serveraddr;

    serveraddr.sin_family=AF_INET;
    int PORT=3000;
    serveraddr.sin_port=htons(PORT);

    //convert the ip address (0.0.0.0) put it inside the sin_family in binary form
   if(inet_pton(AF_INET,"0.0.0.0",&serveraddr.sin_addr)!=1) {
    cout<<"setting adddress structure failed"<<endl;
    closesocket(listenSocket);
    WSACleanup();
    return 1;
   }

   //bind
   if(bind(listenSocket,(struct sockaddr*)&serveraddr,sizeof(serveraddr))==SOCKET_ERROR){
    cout<<"bind failed"<<endl;
    closesocket(listenSocket);
    WSACleanup();
    return 1;
   }


//    listen
if(listen(listenSocket,500)==SOCKET_ERROR){
    cout<<"listing failed"<<endl;
    closesocket(listenSocket);
    WSACleanup();
    return 1;
}

cout<<"Server has started listening on port: "<<PORT<<endl;

while(1){
    //accept
    SOCKET clientSocket=accept(listenSocket,nullptr,nullptr);
    if(clientSocket==INVALID_SOCKET){
        cout<<"Invalid client socket"<<endl;
    }

    thread t1(InteractWithClient,clientSocket);
    t1.join();
}

closesocket(listenSocket);
WSACleanup();
return 0;
}