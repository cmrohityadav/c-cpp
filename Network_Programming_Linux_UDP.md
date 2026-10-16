# content

[Basic UDP client](#basic-udp-client)
- [Basic UDP server](#basic-udp-server)
[]()
[]()
[]()

## Basic UDP client
```cpp
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argCount, char* argValue[])
{

    if (argCount!=2)
    {
        std::cout<<"Invalid command\nEnter Proper Port\n\n"<<std::endl;
        exit(0);
    }

    int port=std::atoi(argValue[1]);
    int clientFd;
    char buffer[1024];
    struct sockaddr_in serverAddr;
    socklen_t serverAddrSize=sizeof(serverAddr);

    clientFd=socket(AF_INET,SOCK_DGRAM,0);

    memset(&serverAddr,0,sizeof(serverAddr));
    serverAddr.sin_family=AF_INET;
    serverAddr.sin_port=htons(port);
    serverAddr.sin_addr.s_addr=inet_addr("127.0.0.1");

    strcpy(buffer,"Hello guys I am UDP client\n");
    
    // Its UDP, so no connect() needed
    sendto(clientFd,buffer,1024,0,(struct sockaddr*)&serverAddr,serverAddrSize);

    std::cout<<"Data sended"<<std::endl;

    return 0;
}

```
## Basic UDP server
```cpp
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argCount, char* argValue[])
{

    if (argCount!=2)
    {
        std::cout<<"Invalid command\nEnter Proper Port\n\n"<<std::endl;
        exit(0);
    }

    int port=std::atoi(argValue[1]);
    int serverFd, clientFd;
    char buffer[1024];
    struct sockaddr_in serverAddr,clientAddr;
    socklen_t clientAddrSize;
    clientAddrSize=sizeof(clientAddr);

    serverFd=socket(AF_INET,SOCK_DGRAM,0);

    memset(&serverAddr,0,sizeof(serverAddr));
    serverAddr.sin_family=AF_INET;
    serverAddr.sin_port=htons(port);
    serverAddr.sin_addr.s_addr=inet_addr("127.0.0.1");

    bind(serverFd,(struct sockaddr*)&serverAddr,sizeof(serverAddr));

    //UDP is connectionless, so there is no listen() or accept()

    recvfrom(serverFd,buffer,1024,0,(struct sockaddr*)&clientAddr,&clientAddrSize);

    std::cout<<"Data Recieved : "<<buffer<<std::endl;

    return 0;
    // nc -u 127.0.0.1 8080
}
```