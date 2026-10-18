#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

#include<errno.h>
#include<pthread.h>
#include<signal.h>

#define MAX_CLIENTS 100
#define BUFFER_SIZE 2048

int main(int argCount,char* argValue[]){

    if(argCount!=2){
        printf("Usage: %s <port>\n",argValue[1]);
        return EXIT_FAILURE;
    }

    char* ip="127.0.0.1";
    int port=atoi(argValue[1]);

    int option=1;
    int server_socket_fd=0,confd=0;

    struct sockaddr_in serverAddr;
    struct sockaddr_in clientAddr;

    //socket settings
    server_socket_fd=socket(AF_INET,SOCK_STREAM,0);

    serverAddr.sin_family=AF_INET;
    serverAddr.sin_addr.s_addr=inet_addr(ip);
    serverAddr.sin_port=htons(port);

    // Signals
    signal(SIGPIPE,SIG_IGN);

    // socket configuration
    int set_socket_opt=setsockopt(server_socket_fd,SOL_SOCKET,(SO_REUSEPORT | SO_REUSEADDR),(char*)&option,sizeof(option));
    if(set_socket_opt<0){
       printf("ERROR: while setting up setsockopt()\n"); 
       return EXIT_FAILURE;
    }

    //binding
    int bind_socket=bind(server_socket_fd,(struct sockaddr*)&serverAddr,sizeof(serverAddr));
    if(bind_socket<0){
        printf("Error: while binding\n");
        return EXIT_FAILURE;
    }

    //listen
    int listen_socket=listen(server_socket_fd,10);
    if(listen_socket<0){
       printf("Error: while listing...\n");
       return EXIT_FAILURE;
    }

    printf("=== WELLCOME TO GAPSAP===\n");

    










    return EXIT_SUCCESS;
}



