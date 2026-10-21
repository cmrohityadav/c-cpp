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

Signup_res process_signup(const Signup_req &req)
{
    Signup_res res;
    res.header.transcode = SIGNUP_RES;
    res.header.length = sizeof(Signup_res) - sizeof(Header);

    std::cout << "Processing Signup for:\n";
    std::cout << " - Name: " << req.name << "\n";
    std::cout << " - Username: " << req.username << "\n";

    std::strncpy(res.name,req.name,sizeof(res.name)-1);
    res.name[sizeof(res.name)-1]='\0';

    std::strncpy(res.username,req.username,sizeof(res.username)-1);
    res.username[sizeof(res.username)-1]='\0';

    // hardcoding
    if(std::strcmp(req.name,"rohit")==0){
        res.login_status = LOGIN_STATUS::SUCCESS;
        std::strncpy(res.msg, "Signup Successful! You can login now.", sizeof(res.msg) - 1);
    }else{
        res.login_status = LOGIN_STATUS::USER_NOT_FOUND;
        std::strncpy(res.msg, "Signup Fail! User Does not exits", sizeof(res.msg) - 1);
    }
       
    
   

    res.msg[sizeof(res.msg) - 1] = '\0'; // Safe null-termination
    return res;
}

void handle_client(int client_socket_fd)
{
    printf("Client handler thread started for socket: %d\n", client_socket_fd);

    while (true)
    {
        Header header;

        //  Header receive karo
        if (!recvAll(client_socket_fd,&header, sizeof(Header)))
        {
            printf("Client disconnected or error reading header on socket: %d\n", client_socket_fd);
            break;
        }

        // Login Request Check
        if (header.transcode == LOGIN_REQ)
        {
            Login_req req;
            req.header = header;

            size_t payload_size = sizeof(Login_req) - sizeof(Header);
            if (!recvAll(client_socket_fd, &req.username, payload_size))
            {
                break;
            }

            // Login process call (jo pehle banaya tha)
            // Login_res res = process_login(req);
            // sendAll(client_socket_fd, &res, sizeof(Login_res));
            // if (res.login_status == LOGIN_STATUS::FAIL) break;
        }
        // Signup Request Check
        else if (header.transcode == SIGNUP_REQ)
        {
            
            if (header.length != (sizeof(Signup_req) - sizeof(Header)))
            {
                std::cout << "Error: Payload length mismatch!\n";
                break;
            }

            Signup_req req;
            req.header = header;

            
            if (!recvAll(client_socket_fd, &req.name, header.length))
            {
                printf("Error receiving signup payload.\n");
                break;
            }

            // Signup process call karo
            Signup_res res = process_signup(req);

            // Response send karo
            if (!sendAll(client_socket_fd, &res, sizeof(Signup_res)))
            {
                printf("Failed to send signup response.\n");
                break;
            }
        }
        else
        {
            std::cout << "Unknown packet type received.\n";
            break;
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