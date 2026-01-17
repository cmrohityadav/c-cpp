#include<iostream>
#include<sys/socket.h> //socket(AF_INET,SOCK_STREAM,0);

#include <arpa/inet.h> //struct sockaddr_in clientAdd;

#include <unistd.h>  //close(clientSock);
int main(){

    int clientSock=socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in clientAdd;
    clientAdd.sin_family=AF_INET;
    clientAdd.sin_port=htons(4000);

    inet_pton(AF_INET,"127.0.0.1",&clientAdd.sin_addr);

    int clientConnect=connect(clientSock,(struct sockaddr*)&clientAdd,sizeof(clientAdd));

    if(clientConnect<0){
        std::cout<<"connection failed"<<std::endl;
    }

    char buff[256]="hello from client";
    ssize_t sendByte=send(clientSock,(const char*)&buff,sizeof(buff),0);
    if(sendByte<0){
        std::cout<<"No data send fail the sending"<<std::endl;
    }

    close(clientSock);



    return 1;

}