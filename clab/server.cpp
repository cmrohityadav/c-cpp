#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include <arpa/inet.h>
#include <unistd.h> 
#include <cstring>
#include<thread>
void handleClient(int clientSockfd) {
    char buff[256];

    while (true) {
        memset(buff, 0, sizeof(buff));

        ssize_t recvbytes = recv(clientSockfd, (char *)&buff, sizeof(buff) - 1, 0);

        if (recvbytes == 0) {
            std::cout << "Client disconnected\n";
            break;
        }
        if (recvbytes < 0) {
            perror("recv");
            break;
        }

        std::cout << "Client: " << buff << std::endl;

        const char msg[] = "Message from server";
        send(clientSockfd, (const char *)&msg, strlen(msg), 0);
    }

    close(clientSockfd);
}

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

        std::thread thrd(handleClient,clientSockfd);
        thrd.detach();
       
    }
    

    close(server_sock);
    return 1;
    

}