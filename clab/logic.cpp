
#include <iostream>
#include <thread>
#include <cstdlib>
#include <cstring>

#include "tcp.hpp"
#include "common_struct.hpp"
#include "common_hash.hpp"

Signup_res process_signup(const Signup_req& req)
{
    Signup_res res{};

    res.header.transcode = SIGNUP_RES;
    res.header.length =
        sizeof(Signup_res) - sizeof(Header);

    std::strncpy(res.name, req.name, sizeof(res.name) - 1);
    std::strncpy(res.username, req.username,
                 sizeof(res.username) - 1);

    if (std::strcmp(req.name, "rohit") == 0)
    {
        res.login_status = LOGIN_STATUS::SUCCESS;

        std::strncpy(
            res.msg,
            "Signup Successful",
            sizeof(res.msg) - 1
        );
    }
    else
    {
        res.login_status = LOGIN_STATUS::USER_NOT_FOUND;

        std::strncpy(
            res.msg,
            "Signup failed",
            sizeof(res.msg) - 1
        );
    }

    return res;
}

void handle_client(int fd)
{
    TCPConnection conn(fd);

    while (true)
    {
        Header header{};

        // 1. Receive header
        if (!conn.recvAll(&header, sizeof(header)))
            break;

        // 2. Validate known message and payload size
        if (header.transcode == SIGNUP_REQ)
        {
            constexpr size_t expected =
                sizeof(Signup_req) - sizeof(Header);

            if (header.length != expected)
                break;

            Signup_req req{};

            req.header = header;

            // 3. Receive remaining request payload
            char* payload =
                reinterpret_cast<char*>(&req)
                + sizeof(Header);

            if (!conn.recvAll(payload, expected))
                break;

            // 4. Business logic
            Signup_res res = process_signup(req);

            // 5. Send response
            if (!conn.sendAll(&res, sizeof(res)))
                break;
        }
        else if (header.transcode == LOGIN_REQ)
        {
            constexpr size_t expected =
                sizeof(Login_req) - sizeof(Header);

            if (header.length != expected)
                break;

            Login_req req{};
            req.header = header;

            char* payload =
                reinterpret_cast<char*>(&req)
                + sizeof(Header);

            if (!conn.recvAll(payload, expected))
                break;

            // Add process_login(req) here.
            // Send Login_res using conn.sendAll().
        }
        else
        {
            std::cerr << "Unknown transcode\n";
            break;
        }
    }

    // TCPConnection destructor closes fd automatically.
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0]
                  << " <port>\n";
        return EXIT_FAILURE;
    }

    int port = std::atoi(argv[1]);

    TCPServer server;

    if (!server.start(port))
    {
        std::cerr << "Server start failed\n";
        return EXIT_FAILURE;
    }

    std::cout << "Server started on port "
              << port << '\n';

    while (true)
    {
        int fd = server.acceptClient();

        if (fd < 0)
        {
            std::cerr << "Accept failed\n";
            continue;
        }

        std::thread(
            handle_client,
            fd
        ).detach();
    }
}
