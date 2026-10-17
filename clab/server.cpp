#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argCount, char *argValue[])
{

    if (argCount != 2)
    {
        std::cout << "Invalid command\nEnter Proper Port\n\n"
                  << std::endl;
        exit(0);
    }

    int port = std::atoi(argValue[1]);
    int serverSocketFd, clientSocketFd, ret;
    char buffer[1024];
    pid_t childpid;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientAddrSize;
    clientAddrSize = sizeof(clientAddr);

    serverSocketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocketFd < 0)
    {
        std::cout << "Error while creating socket!!" << std::endl;
        exit(1);
    }

    std::cout << "Created successfully socket" << std::endl;

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    ret = bind(serverSocketFd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    if (ret < 0)
    {
        std::cout << "Error while binding socket" << std::endl;
        exit(1);
    }

    std::cout << "Created successfully socket binding to port : " << port << std::endl;

    if (listen(serverSocketFd, 10) == 0)
    {
        std::cout << "Serve start listening at port : " << port << std::endl;
    }
    else
    {
        std::cout << "Error while listening socket" << std::endl;
        exit(1);
    }

    while (1)
    {
        clientSocketFd = accept(serverSocketFd, (struct sockaddr *)&clientAddr, &clientAddrSize);
       
        if (clientSocketFd < 0)
        {
            std::cout << "A client wanna to connect but disconnected due to unable get proper socket of client" << std::endl;
            continue;
        }

        char clientIP[INET_ADDRSTRLEN];

        inet_ntop(AF_INET, &clientAddr.sin_addr, clientIP, sizeof(clientIP));

        std::cout << "Connection accepted successfully\n";
        std::cout << "Client IP: " << clientIP << '\n';
        std::cout << "Client Port: "<< ntohs(clientAddr.sin_port) << '\n';

        if((childpid=fork())==0){
            
            close(serverSocketFd);
            while(1){
                recv(clientSocketFd,buffer,1024,0);
                if(strcmp(buffer,":exit")==0){
                    std::cout<<"Client Disconnected"<<std::endl;
                    std::cout << "Client IP: " << clientIP << '\n';
                    std::cout << "Client Port: "<< ntohs(clientAddr.sin_port) << '\n';
                    break;

                }else{
                    std::cout<<"Client: "<<buffer<<std::endl;
                    send(clientSocketFd,buffer,strlen(buffer),0);
                    memset(buffer,0,sizeof(buffer));
                }
            }

        }
    }

    close(serverSocketFd);
    return 0;
}