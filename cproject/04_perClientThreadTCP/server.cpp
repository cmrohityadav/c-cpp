#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <network_utils.hpp>
#include <common_hash.hpp>
#include <common_struct.hpp>
#include<process_request.hpp>



void handle_client(int client_socket_fd)
{
    printf("Client handler thread started for socket: %d\n", client_socket_fd);

    
    char request_buffer[MAXMSGSIZE];
    char response_buffer[MAXMSGSIZE];
    const int packetSize = MAXMSGSIZE;

    while (true)
    {   
        if (!recvAll(client_socket_fd, request_buffer, sizeof(Header))) {
            printf("Client disconnected or error reading header.\n");
            break; 
        }

        Header header = *(Header*)request_buffer;
        int payload_size = header.length;

        if (sizeof(Header) + payload_size > packetSize) {

            printf("Error: Packet size (%lu) exceeds buffer limit (5000)!\n", sizeof(Header) + payload_size);
            break;
        }

        if (!recvAll(client_socket_fd, request_buffer + sizeof(Header), payload_size)) {
            printf("Error: while receiving payload\n");
            break; 
        }

        int response_size=processRequest(request_buffer,response_buffer);
        if (response_size > 0) {
            if (!sendAll(client_socket_fd, response_buffer, response_size)) {
                printf("Failed to send response.\n");
                break;
            }
        }
        

    }

    close(client_socket_fd);
    printf("Thread exiting and socket closed for: %d\n", client_socket_fd);
}
int main(int arg_count, char *agr_value[])
{

    if (arg_count != 2)
    {
        printf("%s <port>\n", agr_value[0]);
        return EXIT_FAILURE;
    }

    int port = std::atoi(agr_value[1]);

    int server_fd;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0)
    {
        printf("Error: while creating socket\n");
        return EXIT_FAILURE;
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int bindValue = bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (bindValue < 0)
    {
        printf("Error: Bind failed\n");
        close(server_fd);
        return EXIT_FAILURE;
    }

    if (listen(server_fd, 5) < 0)
    {
        printf("Error: Listen failed\n");
        close(server_fd);
        return EXIT_FAILURE;
    }

    printf("Server is listening on port %d...\n", port);

    while (1)
    {
        sockaddr_in client_addr{};
        socklen_t client_addr_len = sizeof(client_addr);

        int client_socket = accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_socket < 0)
        {
            printf("Error: Accept failed\n");
            close(server_fd);
            return EXIT_FAILURE;
        }

        printf("Client connected successfully!\n");

        std::thread threadObject(handle_client, client_socket);
        threadObject.detach();
    }

    return EXIT_SUCCESS;
}