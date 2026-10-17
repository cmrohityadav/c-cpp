#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<unistd.h>
int main(int argCount, char* argValue[])
{

    if (argCount!=2)
    {
        std::cout<<"Invalid command\nEnter Proper Port\n\n"<<std::endl;
        exit(0);
    }

    int port=std::atoi(argValue[1]);
    int clientSocketfd,ret;
    struct sockaddr_in serverAddr;
    char buffer[1024];

    clientSocketfd=socket(AF_INET,SOCK_STREAM,0);

    if (clientSocketfd<0){
        std::cout<<"Error in while creating socket"<<std::endl;
        exit(1);
    }

    std::cout<<"socket created succesfully"<<std::endl;

    memset(&serverAddr,0,sizeof(serverAddr));
    serverAddr.sin_family=AF_INET;
    serverAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    serverAddr.sin_port=htons(port);

    ret=connect(clientSocketfd,(struct sockaddr*)&serverAddr,sizeof(serverAddr));
    if(ret<0){
        std::cout<<"Error while connecting to server"<<std::endl;
        exit(1);
    }

    std::cout<<"Connected to server"<<std::endl;

    while(1){
        std::cout<<"Client: ";
        std::cin>>buffer;
        
        send(clientSocketfd,buffer,strlen(buffer),0);

        if(strcmp(buffer,":exit")==0){
            close(clientSocketfd);
            std::cout<<"Disconnected from server"<<std::endl;
            exit(1);
        }
        
        if(recv(clientSocketfd,buffer,1024,0)<0){
            std::cout<<"Error while receiving data from server"<<std::endl;
            
        }else{
            std::cout<<"Server: "<<buffer<<std::endl;
        }
        
    }


    return 0;
}