#include<iostream>
#include<sys/socket.h> //socket(AF_INET,SOCK_STREAM,0);

#include <arpa/inet.h> //struct sockaddr_in clientAdd;

#include <unistd.h>  //close(clientSock);
#include <cstring>
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

    while (true) {
        std::cout << "Enter message (type 'exit' to quit): ";

        char buff[256];
        std::cin.getline(buff, sizeof(buff));

        // Handle Ctrl+D (EOF)
        if (std::cin.eof()) {
            break;
        }

        // Exit command
        if (strcmp(buff, "exit") == 0) {
            break;
        }

        ssize_t sent = send(clientSock, buff, strlen(buff), 0);
        if (sent < 0) {
            perror("send");
            break;
        }
    }

    close(clientSock);



    return 1;

}