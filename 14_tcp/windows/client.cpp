#include<iostream>
#include<WinSock2.h>
#include<WS2tcpip.h>
using namespace std;
/*
    // initialize winsock

    //create socket

    //connect to the server

    //send/recv

    //close the socket
*/

#pragma comment(lib,"win2_32.lib")
bool Initialize(){
    WSADATA data;

    return WSAStartup(MAKEWORD(2,2),&data)==0;
}
int main()
{
    if(!Initialize()){
        cout<<"winsock initialization failed"<<endl;
        return 1; 
    }

    cout<<"Client program started"<<endl;

    //create socket
    SOCKET clientSocketDiscriptor;

    clientSocketDiscriptor=socket(AF_INET,SOCK_STREAM,0);

    if(clientSocketDiscriptor == INVALID_SOCKET) {
        cout << "Invalid Socket creation failed" << endl;
        WSACleanup();
        return 1;
    }


    // setup server address
    const char *serverIp = "127.0.0.1";
    int PORT = 3000;   

    sockaddr_in serveraddr;

    serveraddr.sin_family=AF_INET;
    serveraddr.sin_port=htons(PORT);

    if(inet_pton(AF_INET, serverIp, &serveraddr.sin_addr) <= 0) {
        cout << "Invalid IP address" << endl;
        closesocket(clientSocketDiscriptor);
        WSACleanup();
        return 1;
    }

    // connect to server
    if(connect(clientSocketDiscriptor, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) == SOCKET_ERROR) {
        cout << "Not able to connect to server" << endl;
        closesocket(clientSocketDiscriptor);
        WSACleanup();
        return 1;
    }

    cout << "Connected to server at " << serverIp << ":" << PORT << endl;
    
    //send/recv

    const char * message="hello server I am client";
    int byteSent;
    byteSent=send(clientSocketDiscriptor,message,strlen(message),0);

    if(byteSent == SOCKET_ERROR) {
    cout << "send failed" << endl;
    } else {
        cout << "Sent " << byteSent << " bytes to server" << endl;
    }

    WSACleanup();
    return 0;
}
