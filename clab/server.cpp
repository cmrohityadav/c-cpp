#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include<time.h>
#define BACKLOG 10


int main(int argCount, char *argValue[])
{

    if (argCount != 2)
    {
        std::cout << "Invalid command\nEnter Proper Port\n\n"
                  << std::endl;
        exit(0);
    }

    int port = std::atoi(argValue[1]);
    int serverSocketFd, ret;
    struct sockaddr_in serverAddr;
    int client_count=0;

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
        int clientSocketFd = accept(serverSocketFd,NULL,NULL);
       
        if (clientSocketFd < 0)
        {
            std::cout << "A client wanna to connect but disconnected due to unable get proper socket of client" << std::endl;
            continue;
        }

        client_count++;
        time_t current_time;
        time(&current_time);

        std::cout<<"Client: "<<client_count<<" Request for time at "<<ctime(&current_time)<<std::endl;
        send(clientSocketFd,ctime(&current_time),30,0);
       
    }

    return 0;
}