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
#include<unordered_map>
#include<fstream>
#include<mutex>
#include<vector>
#include<csignal>

std::unordered_map<std::string,ClientDetail>g_map_clients_detail;
int32_t g_userid=1;

using  UserMap=std::unordered_map<std::string,std::string>;
UserMap g_map_user_password;
std::mutex mtx_user_detail;


void handle_client(int client_socket_fd)
{
    printf("Client handler thread started for socket: %d\n", client_socket_fd);

    
    char request_buffer[MAXMSGSIZE];
    char response_buffer[MAXMSGSIZE];
    char usernameforsocket[USERNAME]={0};
    const int packetSize = MAXMSGSIZE;

    while (true)
    {   
        memset(request_buffer,0,MAXMSGSIZE);
        memset(response_buffer,0,MAXMSGSIZE);
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

        if(header.transcode==LOGIN_REQ && (((Login_res*)response_buffer)->login_status==LOGIN_STATUS::SUCCESS)){
        
            std::unique_lock<std::mutex>lck(mtx_user_detail);
            ClientDetail objClientDetail={0};
            objClientDetail.clientfd=client_socket_fd;
            objClientDetail.isLoggedIn=true;
            strncpy(objClientDetail.username,((Login_req*)request_buffer)->username,sizeof(objClientDetail.username)-1);
            g_map_clients_detail[objClientDetail.username]=objClientDetail;
            strncpy(usernameforsocket,objClientDetail.username,sizeof(usernameforsocket)-1);
        }

        if (response_size > 0) {
            if (!sendAll(client_socket_fd, response_buffer, response_size)) {
                printf("Failed to send response.\n");
                break;
            }
        }

        
        

    }

    close(client_socket_fd);
    {
        std::lock_guard<std::mutex>lck(mtx_user_detail);
        
        auto itr=g_map_clients_detail.find(usernameforsocket);
        if(itr!=g_map_clients_detail.end()){
            ClientDetail& cd=itr->second;
            cd.isLoggedIn=false;
        }
    }

    printf("Thread exiting and socket closed for: %d\n", client_socket_fd);
}

bool loadUsersFile(std::string& userfile,UserMap& usermap){
      
    std::ifstream file(userfile);
    
    if(!file.is_open()){
        printf("%s","could not open file for reading\n");
        return false;
    }

    std::string line;

    //reading heading here username,password
    if(!getline(file,line)){
        return true;// file is empty
    }

    //reading content 
    while(getline(file,line)){
        size_t comma=line.find(',');
        
        if(comma==std::string::npos){
            continue;
        }

        std::string username=line.substr(0,comma);
        std::string password=line.substr(comma+1);

        {
            std::lock_guard<std::mutex>lck(mtx_user_detail);
            usermap[username]=password;
            ClientDetail clientdetail={0};
            strncpy(clientdetail.username,username.c_str(),sizeof(clientdetail.username)-1);
            g_map_clients_detail[username]=clientdetail;
        }

    }


    if(file.bad()){
        printf("%s","Erro while reading file\n");
        return false;
    }

    return true;

}

bool append_in_user_file(std::string username,std::string password){

    std::unique_lock<std::mutex> lck(mtx_user_detail);

    std::string userfilename=USERPASSFILENAME;
    std::ofstream outfile(userfilename,std::ios::app);


    if(!outfile.is_open()){
        printf("Error: while opening file\n");
        return false;
    }

    outfile<<username<<','<<password<<'\n';

    if (!outfile) {
        std::fprintf(stderr, "Failed to write user record\n");
        return false;
    }

    outfile.flush();

    if(!outfile){
        printf("Error: while writing in file\n");
        return false;
    }

    outfile.close();

    if(outfile.fail()){
        printf("Error: while closing  file\n");
        return false;
    }

    return true;

}

void save_in_file_from_map(std::string filename){
    
    UserMap snapshotUserPass;

    {
        
        std::lock_guard<std::mutex>lck(mtx_user_detail);
        snapshotUserPass=g_map_user_password;
    }

    std::ofstream file(filename);

    if(!file.is_open()){
        printf("%s", "Could not open file for writing\n");
        return;
    }
    file<<"username,password\n";

    
    auto itr=snapshotUserPass.begin();
    while(itr!=snapshotUserPass.end()){
        file<<itr->first<<','<<itr->second<<'\n';
        itr++;
    }

    file.flush();

    if(!file){
        printf("%s","Error while writing to file");
        return;
    }

    file.close();

    if(file.fail()){
        printf("%s","Error while clsosing");
        return;
    }

    return;

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

    signal(SIGPIPE,SIG_IGN);

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

    int opt = 1;

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR,&opt, sizeof(opt)) == -1) {
            perror("setsockopt SO_REUSEADDR");
            close(server_fd);
            return 1;
    }

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

    std::string filename= USERPASSFILENAME;

    bool isFileLoaded=loadUsersFile(filename,g_map_user_password);
    if(isFileLoaded){
        printf("%s", "file loaded succesfully\n");
    }else{
        printf("%s", "file not loaded  succesfully\n");
    }


    std::vector<std::thread> workers;   
    while (true)
    {
        sockaddr_in client_addr{};
        socklen_t client_addr_len = sizeof(client_addr);

        int client_socket = accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_socket < 0)
        {
            printf("Error: Accept failed\n");
            close(server_fd);
            break;
        }

        printf("Client connected successfully!\n");
        workers.emplace_back(handle_client,client_socket);
    }

    printf("%s","Shutdown requested...\n");

    close(server_fd);

    for(std::thread& worker:workers){
        if(worker.joinable()){
            worker.join();
        }
    }

    
    save_in_file_from_map(filename);
    
    std::cout << "Server shutdown complete.\n";
    return EXIT_SUCCESS;
}