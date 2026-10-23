#pragma once
#include <sys/socket.h>
#include <unistd.h>
#include <cstddef>


inline bool sendAll(int sock, const void* data, size_t total_bytes) {
    const char* ptr = static_cast<const char*>(data);
    size_t bytes_sent = 0;

    while (bytes_sent < total_bytes) {
        ssize_t sent = send(sock, ptr + bytes_sent, total_bytes - bytes_sent, 0);
        if (sent <= 0) {
            
            return false; 
        }
        bytes_sent += sent;
    }
    return true;
}

inline bool recvAll(int sock, void* data, size_t total_bytes) {
    char* ptr = static_cast<char*>(data);
    size_t bytes_received = 0;

    while (bytes_received < total_bytes) {
        ssize_t received = recv(sock, ptr + bytes_received, total_bytes - bytes_received, 0);
        if (received <= 0) {
           
            return false; 
        }
        bytes_received += received;
    }
    return true;
}