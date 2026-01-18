#include<iostream>
#include<sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


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
    char arriveDeparture; // 'A' or 'D'
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


//----------TCP Recieve thecall Data from server----------------
bool recieveAllData(int sock,void* buffer,int totalSize){
    int totalRecievedBtye=0;

    char* buf=(char*)buffer;

    while(totalRecievedBtye<totalSize){
        int recievedByte=recv(sock, buf+totalRecievedBtye, totalSize-totalRecievedBtye,0);
        if(recievedByte<=0){
            return false;
        }

        totalRecievedBtye=totalRecievedBtye+recievedByte;
    }
    return true;
}

// ---------------- DISPLAY ----------------

void displayTrain(const Header& h, const TrainInfo& t) {
    std::cout << "\n--- PLATFORM " << h.platformNumber << " ---\n";
    std::cout << "Train No : " << t.trainNumber << "\n";
    std::cout << "Name     : " << t.trainName << "\n";
    std::cout << "Type     : "
              << (t.arriveDeparture == 'A' ? "Arrival" : "Departure") << "\n";
    std::cout << "Time     : " << t.time << "\n";
}

void displayAnnouncement(const Announcement& a) {
    std::cout << "\n[ANNOUNCEMENT]\n";
    std::cout << a.announceMessage << "\n";
}

void displayAdvertisement(const Advertisement& ad) {
    std::cout << "\n[ADVERTISEMENT]\n";
    std::cout << ad.company << " - " << ad.product
              << " (" << ad.discountPercentage << "% OFF)\n";
}


// ---------------- CONNECT SERVER ----------------

int connectServer() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_port = htons(8080); //#include <netinet/in.h>
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); //#include <arpa/inet.h>

    if (connect(sock, (sockaddr*)&server, sizeof(server)) < 0) {
        perror("connect failed");
        return -1;
    }
    return sock;
}

static int GlobalPlaftformNumber=0;
int main(){
    std::cout<<"Welcome to Mumbai Local| Smart Railways Indicator System"<<std::endl;


    int sock=connectServer();
    if (sock<0){
        std::cout<<"Unable to connect to server Please Restart client application"<<std::endl;

    }

    std::cout<<"Enter Platform Number: "<<std::endl;
    std::cin>>GlobalPlaftformNumber;

    while(true){
        Header header{};

        if(!recieveAllData(sock,&header,sizeof(Header))){
            std::cout << "Server disconnected\n";
            break;
        }

        if(header.platformNumber!=GlobalPlaftformNumber){
            char* skip=new char[header.size]; 
            recieveAllData(sock,skip,header.size);
            delete[] skip;
            continue;
        }
        

        //based on action we do activites on console of client
        switch(header.action){
            case 1:
            // Train updates
            TrainInfo train;
            if (!recieveAllData(sock, &train, header.size)) break;
            displayTrain(header, train);

            break;
            case 2:
                Announcement anncouncement;
                if(!recieveAllData(sock, &anncouncement, header.size)) break;
                displayAnnouncement(anncouncement);

            break;
            case 3:

            Advertisement ad;
            if(!recieveAllData(sock, &ad, header.size)) break;
            displayAdvertisement(ad);

            break;
            default:
            std::cout << "Unknown data received\n";
            break;

        }

    }

    close(sock); //#include <unistd.h>
    return 0;
}