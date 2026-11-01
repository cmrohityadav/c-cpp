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

char g_username[USERNAME];

void clear_input(){
    int c;
    while((c=getchar()) != '\n' && c!=EOF){

    }
}

bool recv_response(int sock,uint32_t expected_transcode,void* p_res,size_t res_size ){

    Header* resp_header=(Header*)p_res;
    
    if(!recvAll(sock,resp_header,sizeof(Header))){
        printf("Error: Failed to recieve response header\n");
        return false;
    }

    if(resp_header->transcode!=expected_transcode){
        printf("Error: Unknown response type recieve from server\n");
        return false;
    }

    if(resp_header->length != res_size- sizeof(Header)){
        printf("Error: Invalid response length %u\n", resp_header->length);
        return false;
    }

    if(!recvAll(sock,(char*)p_res+sizeof(Header),resp_header->length)){
        printf("Error: Failed to receive response payload\n");
        return false;
    }

    return true;
}

// return: true agar signup successful hua
bool do_signup(int sock, bool &connection_ok)
{
    Signup_req req{};
    req.header.transcode = SIGNUP_REQ;
    req.header.length = sizeof(Signup_req) - sizeof(Header);

    printf("Enter Name: ");
    scanf("%19s", req.name);
    clear_input();

    printf("Enter Username: ");
    scanf("%19s", req.username);
    clear_input();

    printf("Enter Password: ");
    scanf("%39s", req.password);
    clear_input();

    if (!sendAll(sock, &req, sizeof(Signup_req)))
    {
        printf("Error: Failed to send signup request\n");
        connection_ok = false;
        return false;
    }

    Signup_res res{};
    if (!recv_response(sock, SIGNUP_RES, &res, sizeof(Signup_res)))
    {
        connection_ok = false;
        return false;
    }
    res.msg[sizeof(res.msg) - 1] = '\0';

    std::cout << "\n--- Server Response ---\n";
    std::cout << "Message: " << res.msg << "\n";
    std::cout << "Status: " << (res.login_status == LOGIN_STATUS::SUCCESS ? "SUCCESS" : "FAIL") << "\n\n";

    return res.login_status == LOGIN_STATUS::SUCCESS;
}

// return: true agar login successful hua
bool do_login(int sock, bool &connection_ok)
{
    Login_req req{};
    req.header.transcode = LOGIN_REQ;
    req.header.length = sizeof(Login_req) - sizeof(Header);

    printf("Enter Username: ");
    scanf("%19s", req.username);
    strncpy(g_username,req.username,sizeof(g_username)-1);
    clear_input();

    printf("Enter Password: ");
    scanf("%39s", req.password);
    clear_input();

    if (!sendAll(sock, &req, sizeof(Login_req)))
    {
        printf("Error: Failed to send login request\n");
        connection_ok = false;
        return false;
    }

    Login_res res{};
    if (!recv_response(sock, LOGIN_RES, &res, sizeof(Login_res)))
    {
        connection_ok = false;
        return false;
    }
    res.msg[sizeof(res.msg) - 1] = '\0';

    std::cout << "\n--- Server Response ---\n";
    std::cout << "Message: " << res.msg << "\n";
    std::cout << "Status: " << (res.login_status == LOGIN_STATUS::SUCCESS ? "SUCCESS" : "FAIL") << "\n\n";

    return res.login_status == LOGIN_STATUS::SUCCESS;
}

bool do_add_token(int sock,bool& connection_ok){
    AddTokenRequest addTokenReq={0};
    AddTokenResponse addTokenRes={0};
    addTokenReq.header.transcode=ADDTOKEN_REQ;
    addTokenReq.header.length=sizeof(addTokenReq)-sizeof(Header);

    
    strncpy(addTokenReq.username,g_username,USERNAME-1);

    printf("Enter token Number: ");
    scanf("%d",&addTokenReq.token);
    clear_input();

    printf("Enter Scrip Name: ");
    scanf("%14s",addTokenReq.scrip);
    clear_input();

    printf("Enter Any remark: ");
    scanf("%49s",addTokenReq.remark);
    clear_input();

    if(!sendAll(sock,&addTokenReq,sizeof(addTokenReq))){
        printf("Error: Failed to send addtoken request\n");
        connection_ok = false;
        return false;
        
    }

    if(!recv_response(sock,ADDTOKEN_RES,&addTokenRes,sizeof(addTokenRes))){
        printf("Error: Failed to send addtoken request\n");
        connection_ok = false;
        return false;
    }


    addTokenRes.msg[MESSAGE-1]='\0';

    std::cout << "\n--- Server Response ---\n";
    std::cout << "Message: " << addTokenRes.msg << "\n";
    if(addTokenRes.isAddedflag){
        std::cout << "Status: " << "Token Added" << "\n";
        return true;
    }else{
        std::cout << "Status: " << "Token NOT  Added" << "\n";
        return false;
    }

}

void authenticated_menu(int sock, bool &connection_ok)
{
    while (connection_ok)
    {
        int choice = 0;

        printf("\n========== WELCOME TO  PORTFOLIO MANAGER ==========\n");
        printf("1. Check Holdings\n");
        printf("2. Modify Holding\n");
        printf("3. Add Token\n");
        printf("4. Logout\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1)
        {
            if (feof(stdin))
                break;

            clear_input();
            printf("Invalid input!\n");
            continue;
        }

        clear_input();

        switch (choice)
        {
            case 1:
                // do_check_holdings(sock, connection_ok);
                break;

            case 2:
                // do_modify_holding(sock, connection_ok);
                break;

            case 3:
                do_add_token(sock, connection_ok);
                break;

            case 4:
                // do_logout(sock, connection_ok);
                return;

            default:
                printf("Invalid choice!\n");
                break;
        }
    }
}
int main(int arg_count, char *agr_value[])
{
    if (arg_count != 3)
    {
        printf("Usage: %s <server_ip> <port>\n", agr_value[0]);
        return EXIT_FAILURE;
    }

    const char *server_ip = agr_value[1];
    int port = std::atoi(agr_value[2]);

    
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

    
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("Error: Connection to server failed\n");
        close(sock);
        return EXIT_FAILURE;
    }

    printf("Connected to server successfully!\n");

    bool signed_up = false;
    bool connection_ok = true;

    while (connection_ok)
    {
        int choice = 0;
        if (!signed_up)
        {
            printf("1. Signup\n2. Login\n3. Exit\nEnter choice: ");
            if (scanf("%d", &choice) != 1) {
                if (feof(stdin)) break;
                clear_input();
                printf("Invalid choice\n\n");
                continue;
            }
            clear_input();

            if (choice == 1) {
                signed_up = do_signup(sock, connection_ok);
            } else if (choice == 2) {
                if (do_login(sock, connection_ok)) {
                    printf("Welcome! Logged in successfully.\n");
                    authenticated_menu(sock,connection_ok);
                }
            } else if (choice == 3) {
                break;
            } else {
                printf("Invalid choice\n\n");
            }
        }
        else
        {
            printf("1. Login\n2. Exit\nEnter choice: ");
            if (scanf("%d", &choice) != 1) {
                if (feof(stdin)) break;
                clear_input();
                printf("Invalid choice\n\n");
                continue;
            }
            clear_input();

            if (choice == 1) {
                if (do_login(sock, connection_ok)) {
                    printf("Welcome! Logged in successfully.\n");
                    break;
                }
            } else if (choice == 2) {
                break;
            } else {
                printf("Invalid choice\n\n");
            }
        }
    }

    
    close(sock);
    printf("Bye!\n");
    return EXIT_SUCCESS;
}