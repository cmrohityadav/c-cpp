
#include "tcp.hpp"

#include <cerrno>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

TCPConnection::TCPConnection(int fd)
    : socket_fd(fd)
{
}

TCPConnection::~TCPConnection()
{
    closeConnection();
}

bool TCPConnection::sendAll(
    const void* data, size_t size)
{
    const char* ptr =
        static_cast<const char*>(data);

    size_t sent = 0;

    while (sent < size)
    {
        ssize_t n = send(
            socket_fd,
            ptr + sent,
            size - sent,
            MSG_NOSIGNAL
        );

        if (n < 0 && errno == EINTR)
            continue;

        if (n <= 0)
            return false;

        sent += static_cast<size_t>(n);
    }

    return true;
}

bool TCPConnection::recvAll(
    void* data, size_t size)
{
    char* ptr = static_cast<char*>(data);

    size_t received = 0;

    while (received < size)
    {
        ssize_t n = recv(
            socket_fd,
            ptr + received,
            size - received,
            0
        );

        if (n < 0 && errno == EINTR)
            continue;

        if (n <= 0)
            return false;

        received += static_cast<size_t>(n);
    }

    return true;
}

int TCPConnection::getSocket() const
{
    return socket_fd;
}

void TCPConnection::closeConnection()
{
    if (socket_fd != -1)
    {
        close(socket_fd);
        socket_fd = -1;
    }
}


// -------- TCP SERVER --------

TCPServer::TCPServer()
    : server_fd(-1)
{
}

TCPServer::~TCPServer()
{
    if (server_fd != -1)
        close(server_fd);
}

bool TCPServer::start(int port)
{
    server_fd = socket(
        AF_INET,
        SOCK_STREAM,
        0
    );

    if (server_fd < 0)
        return false;

    int opt = 1;

    setsockopt(
        server_fd,
        SOL_SOCKET,
        SO_REUSEADDR,
        &opt,
        sizeof(opt)
    );

    sockaddr_in addr{};

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    // Same as your existing project:
    // localhost only
    addr.sin_addr.s_addr =
        htonl(INADDR_LOOPBACK);

    if (bind(
        server_fd,
        reinterpret_cast<sockaddr*>(&addr),
        sizeof(addr)
    ) < 0)
    {
        close(server_fd);
        server_fd = -1;
        return false;
    }

    if (listen(server_fd, 10) < 0)
    {
        close(server_fd);
        server_fd = -1;
        return false;
    }

    return true;
}

int TCPServer::acceptClient()
{
    while (true)
    {
        int fd = accept(server_fd, nullptr, nullptr);

        if (fd >= 0)
            return fd;

        if (errno != EINTR)
            return -1;
    }
}
