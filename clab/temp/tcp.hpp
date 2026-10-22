
#pragma once

#include <cstddef>
#include <sys/types.h>

class TCPConnection
{
private:
    int socket_fd;

public:
    explicit TCPConnection(int fd);
    ~TCPConnection();

    TCPConnection(const TCPConnection&) = delete;
    TCPConnection& operator=(const TCPConnection&) = delete;

    bool sendAll(const void* data, size_t size);
    bool recvAll(void* data, size_t size);

    int getSocket() const;
    void closeConnection();
};

class TCPServer
{
private:
    int server_fd;

public:
    TCPServer();
    ~TCPServer();

    bool start(int port);
    int acceptClient();
};
