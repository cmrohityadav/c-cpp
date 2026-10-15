#include<iostream>
#include<cstring>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>

# define PORT 8080

int main(){

    int serverfd, clientfd;;
    struct sockaddr_in serverAddr, clientAddr;
    memset(&serverAddr,0,sizeof(serverAddr));

    socklen_t client_addr_size;
    char buffer[1024];
    strcpy(buffer,"hello client rohit");


    serverfd=socket(AF_INET,SOCK_STREAM,0);

    serverAddr.sin_family=AF_INET;
    serverAddr.sin_port=htons(PORT);
    serverAddr.sin_addr.s_addr=inet_addr("127.0.0.1");

    bind(serverfd,(struct sockaddr*)&serverAddr,sizeof(serverAddr));

    listen(serverfd,5);

    client_addr_size=sizeof(clientAddr);
    clientfd=accept(serverfd,(struct sockaddr*)&clientAddr,&client_addr_size);

    send(clientfd,buffer,strlen(buffer),0);
    
    return 0;
}