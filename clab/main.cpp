#include <iostream>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/epoll.h>

#define PORT 8080
#define MAX_EVENTS 10
#define BUFFER_SIZE 1024

// Helper function to set a socket to non-blocking mode
void make_non_blocking(int sockfd) {
    int flags = fcntl(sockfd, F_GETFL, 0); //Socket ke current file status flags nikalta hai
    fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);
    /*
    Usme O_NONBLOCK flag jod deta hai. 
    Iska matlab ab agar recv() ya send() par data nahi mila, 
    toh yeh thread ko rokega nahi, seedha -1 aur EAGAIN return karke aage badh jayega
    */
}

int main() {
    // 1. Create Server Socket
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    make_non_blocking(server_fd); // Server socket bhi non-blocking hoga

    struct sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, SOMAXCONN);

    // 2. Create epoll instance
    /*
    Yeh Linux kernel ke andar ek Kernel Event Table banata hai aur uska handle (epoll_fd) return karta hai. 
    Is table me woh saare sockets stored hote hain jinpar server nazar rakh raha hai
    */
    int epoll_fd = epoll_create1(0);

    if (epoll_fd < 0) {
        perror("epoll_create1 failed");
        return 1;
    }

    // 3. Register server socket to epoll watch list
    struct epoll_event ev{};
    ev.events = EPOLLIN; // Watch for incoming read events (connections)
    ev.data.fd = server_fd;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &ev) < 0) {
        perror("epoll_ctl server_fd failed");
        return 1;
        /*
        epoll_ctl ka matlab hai "Control the epoll watch list"
        Yahan hum kernel ko bol rahe hain: 
        "Bhai server_fd ko apni watch list me add (EPOLL_CTL_ADD) kar le, 
        aur jab bhi is par koi naya connection aaye (EPOLLIN), mujhe notify karna."

        */
    }

    std::cout << "[SERVER] High-Performance epoll Server started on port " << PORT << "...\n";

    struct epoll_event events[MAX_EVENTS];

    // 4. The Main Event Loop
    while (true) {
        // Wait for events to happen (blocks here until something occurs on any socket)
        // Yeh server ka heartbeat/engine hai
        //Jab tak koi client kuch nahi bhejta, yeh thread yahin chup-chap soya (blocked) rehta hai (CPU 0% consumption!).
        //Jaise hi kisi bhi socket par data aata hai
        // OS is thread ko jagata hai aur events array me un sabhi sockets ki list bhar deta hai jo active hain. 
        //nfds batata hai ki kitne sockets par action hua hai.

        int nfds = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
        if (nfds < 0) {
            perror("epoll_wait failed");
            break;
        }

        for (int i = 0; i < nfds; ++i) {
            int current_fd = events[i].data.fd;

            // CASE A: New connection coming in on the server socket
            if (current_fd == server_fd) {
                struct sockaddr_in client_addr{};
                socklen_t client_len = sizeof(client_addr);
                int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
                
                if (client_fd < 0) continue;

                make_non_blocking(client_fd); // Make client socket non-blocking

                // Add new client to epoll watch list
                ev.events = EPOLLIN | EPOLLET; // Read event + Edge-Triggered mode
                ev.data.fd = client_fd;
                epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &ev);

                std::cout << "[SERVER] New client connected! FD: " << client_fd << "\n";
            } 
            // CASE B: Data received from an existing client
            else {
                char buffer[BUFFER_SIZE];
                memset(buffer, 0, BUFFER_SIZE);
                ssize_t bytes_read = recv(current_fd, buffer, BUFFER_SIZE - 1, 0);

                if (bytes_read <= 0) {
                    // Client disconnected or error occurred
                    if (bytes_read == 0) {
                        std::cout << "[SERVER] Client disconnected gracefully. FD: " << current_fd << "\n";
                    } else {
                        perror("recv error");
                    }
                    // epoll automatically removes closed fds when closed, but good to clean up
                    close(current_fd);
                } else {
                    std::cout << "[SERVER] Received " << bytes_read << " bytes from FD " << current_fd << ": " << buffer;

                    // Echo back the data (Echo Protocol)
                    send(current_fd, buffer, bytes_read, 0);
                }
            }
        }
    }

    close(server_fd);
    close(epoll_fd);
    return 0;
}