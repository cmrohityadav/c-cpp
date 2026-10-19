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
#include <stdatomic.h>

#define MAX_CLIENTS 100
#define BUFFER_SIZE 2048
#define NAME_LEN 32
static _Atomic unsigned int client_count=0;
static int uid=10;
void print_ip_addr(struct sockaddr_in addr){
    char ip[INET_ADDRSTRLEN];

    inet_ntop(AF_INET,&addr.sin_addr,ip,sizeof(ip));
    
    printf("%s\n",ip);
}

typedef struct{
    struct sockaddr_in address;
    int socket_fd;
    int uid;
    char name[NAME_LEN]
} client_t;

client_t* clients[MAX_CLIENTS];

pthread_mutex_t clients_mutex=PTHREAD_MUTEX_INITIALIZER;

void str_overwrite_stdout(){
    printf("\r%s","> ");
    fflush(stdout);
}

void str_trim_lf(char* arr,int length){
 for(int i=0;i<length;i++){
    if(arr[i]=="\n"){
        arr[i]="\0";
        break;
    }   
 }
    
}

void queue_add(client_t* cl){
    pthread_mutex_lock(&clients_mutex);
        for(int i=0;i<MAX_CLIENTS;i++){
            if(!clients[i]){
                clients[i]=cl;
                break;
            }
        }

    pthread_mutex_unlock(&clients_mutex);
}

void queue_remove(int uid){
    pthread_mutex_lock(&clients_mutex);

    for(int i=0;i<MAX_CLIENTS;i++){
     if(clients[i]){
        if(clients[i]->uid==uid){
          clients[i]==NULL;
          break;  
        }
     }   
    }

    pthread_mutex_unlock(&clients_mutex);
}

void send_message(char* s,int uid){
    pthread_mutex_lock(&clients_mutex);

    for(int i=0;i<MAX_CLIENTS;i++){
        if(clients[i]){
            if(clients[i]->uid!=uid){
                if(write(clients[i]->socket_fd,s,strlen(s))<0){
                    printf("Error: write to descriptor failed\n");
                    break;
                }

            }
        }
    }


    pthread_mutex_unlock(&clients_mutex);

}

int main(int argCount,char* argValue[]){

    if(argCount!=2){
        printf("Usage: %s <port>\n",argValue[0]);
        return EXIT_FAILURE;
    }

    const char* ip="127.0.0.1";
    int port=atoi(argValue[1]);

    int option=1;
    int server_socket_fd=0,connection_fd=0;

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

    while(1){
        socklen_t client_addr_len=sizeof(clientAddr);

        connection_fd=accept(server_socket_fd,(struct sockaddr*)&clientAddr,&client_addr_len);
        if(connection_fd<0){
            printf("Error: while accepting client...\n");
            return EXIT_FAILURE;
        }

        if(connection_fd>=0){
            printf("Client successfully connected: ");
            print_ip_addr(clientAddr);
        }
        //check for MAx client
        if((client_count+1)==MAX_CLIENTS){
           printf("Maximum clients connected, connection Reject\n");
           
           print_ip_addr(clientAddr);
           close(connection_fd);
           continue;
        }

    }










    return EXIT_SUCCESS;
}



