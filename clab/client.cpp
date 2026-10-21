#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <network_utils.hpp>
#include <common_hash.hpp>
#include <common_struct.hpp>

int main(int arg_count, char *agr_value[])
{
    if (arg_count != 3)
    {
        printf("Usage: %s <server_ip> <port>\n", agr_value[0]);
        return EXIT_FAILURE;
    }

    const char *server_ip = agr_value[1];
    int port = std::atoi(agr_value[2]);

    // 1. Socket Create karo
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        printf("Error: Socket creation failed\n");
        return EXIT_FAILURE;
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, server_ip, &server_addr.sin_addr);

    // 2. Server se Connect karo
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("Error: Connection to server failed\n");
        close(sock);
        return EXIT_FAILURE;
    }

    printf("Connected to server successfully!\n");

    // 3. Signup Request Packet Banao
    Signup_req req;
    req.header.transcode = SIGNUP_REQ;
    // Server ke code ke mutabiq length payload ka size honi chahiye
    req.header.length = sizeof(Signup_req) - sizeof(Header);

    printf("Enter Name: ");
    // scanf(" %[^\n]", req.name); // Space ke pehle ' ' lagane se pichhla buffer clear ho jata hai
    scanf("%s", req.name);
    req.name[sizeof(req.name) - 1] = '\0';

    // 2. Username input
    printf("Enter Username: ");
    scanf("%s", req.username);
    req.username[sizeof(req.username) - 1] = '\0';

    // 3. Password input
    printf("Enter Password: ");
    scanf("%s", req.password);
    req.password[sizeof(req.password) - 1] = '\0';

    // 4. Poora Signup_req struct server ko bhejo (`sendAll` use karke)
    if (!sendAll(sock, &req, sizeof(Signup_req)))
    {
        printf("Error: Failed to send signup request\n");
        close(sock);
        return EXIT_FAILURE;
    }
    printf("Signup request sent. Waiting for response...\n");

    // 5. Server se Response ka Header pehle read karo
    Header res_header;
    if (!recvAll(sock, &res_header, sizeof(Header)))
    {
        printf("Error: Failed to receive response header\n");
        close(sock);
        return EXIT_FAILURE;
    }

    // 6. Check karo ki response Signup ka hi hai ya nahi
    if (res_header.transcode == SIGNUP_RES)
    {
        Signup_res res;
        res.header = res_header;

        if (!recvAll(sock, &res.name, res.header.length))
        {
            printf("Error: Failed to receive signup response payload\n");
            close(sock);
            return EXIT_FAILURE;
        }

        // Server ka message print karo
        std::cout << "\n--- Server Response ---\n";
        std::cout << "Name: " << res.name << "\n";
        std::cout << "Username: " << res.username << "\n";
        std::cout << "Message: " << res.msg << "\n";

        if (res.login_status == LOGIN_STATUS::SUCCESS)
        {
            std::cout << "Status: SUCCESS\n";
        }
        else
        {
            std::cout << "Status: FAIL\n";
        }
    }
    else
    {
        std::cout << "Error: Unknown response type received from server.\n";
    }

    // 7. Connection close karo
    close(sock);
    return EXIT_SUCCESS;
}