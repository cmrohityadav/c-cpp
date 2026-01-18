#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <signal.h>
// ---------------- STRUCTS ----------------

#pragma pack(push, 1)
struct Header {
    int platformNumber;
    int action;   // 1=Train, 2=Announcement, 3=Advertisement
    int size;     // payload size
};
#pragma pack(pop)

struct TrainInfo {
    int trainNumber;
    char trainName[256];
    char arriveDeparture;
    char time[16];
};

struct Announcement {
    char announceMessage[256];
};

struct Advertisement {
    char company[100];
    char product[100];
    int discountPercentage;
};

// ---------------- GLOBAL CLIENT LIST ----------------

std::vector<int> clients;
std::mutex clientMutex;

// ---------------- SEND ALL ----------------

bool sendAll(int sock, void* buffer, int size) {
    int totalSendBytes = 0;
    char* buf = (char*)buffer;

    while (totalSendBytes < size) {
        int sendBytes = send(sock, buf + totalSendBytes, size - totalSendBytes, MSG_NOSIGNAL);
        if (sendBytes  <= 0) return false;

        totalSendBytes += sendBytes;
    }
    return true;
}

// ---------------- BROADCAST ----------------

void broadcast(void* header, int hSize, void* payload, int pSize) {
    std::lock_guard<std::mutex> lock(clientMutex);

    for (auto it = clients.begin(); it != clients.end();) {
        if (!sendAll(*it, header, hSize) || !sendAll(*it, payload, pSize)) {

            std::cout << "Client disconnected\n";
            close(*it);
            it = clients.erase(it);

        } else {
            ++it;
        }
    }
}

// ---------------- ACCEPT CLIENTS THREAD ----------------

void acceptClients(int serverSock) {
    while (true) {
        int clientSock = accept(serverSock, nullptr, nullptr);
        if (clientSock >= 0) {
            std::lock_guard<std::mutex> lock(clientMutex);
            clients.push_back(clientSock);
        }
    }
}

// ---------------- MAIN ----------------

int main() {
    signal(SIGPIPE, SIG_IGN);
    int serverSock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(serverSock, (sockaddr*)&server, sizeof(server));
    listen(serverSock, 10);

    std::cout << "Multi-client server started on port 8080...\n";

    
    std::thread acceptThread(acceptClients, serverSock);
    acceptThread.detach();

    // Console loop
    while (true) {
        Header header{};
        int choice;

        std::cout << "\nChoose update type:\n";
        std::cout << "1. Train Info\n";
        std::cout << "2. Announcement\n";
        std::cout << "3. Advertisement\n";
        std::cout << "Choice: ";
        std::cin >> choice;

        std::cout << "Platform number: ";
        std::cin >> header.platformNumber;

        header.action = choice;

        if (choice == 1) {
            TrainInfo train{};
            header.size = sizeof(TrainInfo);

            std::cout << "Train Number: ";
            std::cin >> train.trainNumber;
            std::cin.ignore();

            std::cout << "Train Name: ";
            std::cin.getline(train.trainName, 256);

            std::cout << "Arrival(A) / Departure(D): ";
            std::cin >> train.arriveDeparture;

            std::cout << "Time (HH:MM): ";
            std::cin >> train.time;

            broadcast(&header, sizeof(Header),&train, sizeof(TrainInfo));
        }
        else if (choice == 2) {
            Announcement a{};
            header.size = sizeof(Announcement);

            std::cin.ignore();
            std::cout << "Announcement message: ";
            std::cin.getline(a.announceMessage, 256);

            broadcast(&header, sizeof(Header),&a, sizeof(Announcement));
        }
        else if (choice == 3) {
            Advertisement ad{};
            header.size = sizeof(Advertisement);

            std::cin.ignore();
            std::cout << "Company: ";
            std::cin.getline(ad.company, 100);

            std::cout << "Product: ";
            std::cin.getline(ad.product, 100);

            std::cout << "Discount %: ";
            std::cin >> ad.discountPercentage;

            broadcast(&header, sizeof(Header),&ad, sizeof(Advertisement));
        }
        else {
            std::cout << "Invalid choice\n";
        }
    }

    close(serverSock);
    return 0;
}
