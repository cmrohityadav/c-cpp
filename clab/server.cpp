#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include <arpa/inet.h>
#include <unistd.h> 
#include <cstring>
int main(){
    
    int server_sock=socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in serverAdd,clientAdd;
    serverAdd.sin_family=AF_INET;
    serverAdd.sin_port=htons(4000);
    
    inet_pton(AF_INET,"127.0.0.1",&serverAdd.sin_addr);

    int sockBinding=bind(server_sock,(struct sockaddr*)&serverAdd,sizeof(serverAdd));
    if (sockBinding<0){
        std::cerr<<"Binding failed"<<std::endl;
    }

    int iListen=listen(server_sock,5);
    if(iListen==0){
        std::cout<<"Server is listening on Port "<<serverAdd.sin_port<<std::endl;
    }else{
        std::cout<<"Server failed to Up"<<std::endl;
    }

    socklen_t sizeClientAdd=sizeof(clientAdd);

    while(true){
        int clientSockfd=accept(server_sock,(struct sockaddr*)&clientAdd,&sizeClientAdd);

        char buff[256]={0};
        ssize_t recvbytes=recv(clientSockfd,(char*)&buff,sizeof(buff)-1,0);
        if(recvbytes==0){
            std::cout<<"connection closed by peers "<<std::endl;
        }else if(recvbytes<0){
            std::cout<<"erro occurred"<<std::endl;
        }

        if(recvbytes>0){
            std::cout<<"recv mes: "<<buff<<std::endl;
        }

        const char msg[]="This message froms server";
       ssize_t sendbytes= send(clientSockfd,(const char*)&msg,strlen(msg),0);
       if(sendbytes>0){
        std::cout<<"message sended succesfully"<<std::endl;
       }

       close(clientSockfd);

    }

    close(server_sock);
    return 1;
    

}