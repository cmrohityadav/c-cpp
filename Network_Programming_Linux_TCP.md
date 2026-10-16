# Network Programming (Socket Programming)
- Build a program that recieves and transmits data between two or more computers by means of a network
# content
- [basic socket](#socket-socket-descriptor)
- [Basic TCP Client ](#basic-tcp-client)
- [Basic TCP server](#basic-tcp-server)
- [epoll](#epoll)
## Socket (socket descriptor)
- Socket ek endpoint hota hai jiske through do programs network ke upar baat karte hain
- Pipe → same machine ke processes ke liye
- File → disk ke liye
- Socket → network ke liye
```bash
# Real-life analogy
Mera ghar = Program / Process
Phone = Socket
Phone number = IP + Port
Call karna = connect()
Call receive karna = accept()
Baat karna = send() / recv()
```
- Linux me socket ek file jaisa hota hai
- Isliye socket ko file descriptor (FD) bola jata hai
```txt
#include<sys/socket.h> 

It provides:
- Functions: socket(), bind(), listen(), accept(), connect(), send(), recv(), setsockopt()
- Constants: AF_INET, SOCK_STREAM, SOCK_DGRAM, SOL_SOCKET
- Data types: struct sockaddr jaise socket address types.

Purpose: C++ program ko OS ke socket API ke through network communication karne dena

```
```cpp
#include<sys/socket.h>

int sockfd=socket(int domain,int type,int protocol)

//Example
int sockfd = socket(AF_INET, SOCK_STREAM, 0);
//
socket(AF_INET, SOCK_DGRAM, 0);
```
- AF_INET: Address Family – Internet
- SOCK_STREAM → Socket Stream(TCP/Transmission Control Protocol)
- SOCK_DGRAM → Socket Datagram(UDP/User Datagram Protocol)

- `int sockfd = socket(int domain, int type, int protocol);`
- domain (Address Family)
- Batata hai kis type ka network use hoga.
| Constant   | Meaning                     |
| ---------- | --------------------------- |
| `AF_INET`  | IPv4 Internet protocol      |
| `AF_INET6` | IPv6 Internet protocol      |
| `AF_UNIX`  | Local (Unix domain) sockets |

- type (Socket Type)
| Type          | Meaning | Use                        |
| ------------- | ------- | -------------------------- |
| `SOCK_STREAM` | TCP     | Reliable, connection-based |
| `SOCK_DGRAM`  | UDP     | Fast, connectionless       |

- protocol
| Protocol      | Meaning          |
| ------------- | ---------------- |
| `0`           | Default protocol |
| `IPPROTO_TCP` | TCP              |
| `IPPROTO_UDP` | UDP              |



- Kernel ne socket object banaya
- Program ko uska handle (FD) de diya
- Linux ka rule: Everything is a file(File,Pipe,Socket)
- File ka matlab hota hai: `data ka stream jisko read/write kiya ja sake`
- Data stream = `bytes ka continuous flow`, jisme data ek ke baad ek aata ya jaata hai

## Bind
- Is socket ko bata do ki tu kis address (IP + port) par baitha hai
- Agar socket bas ek stream hai, to bind() kya kar raha hai?
- bind() stream ko network ke map pe register karta hai
- Is data stream ke receiving end ko
is `IP + port` par laga do
- IP batata hai “kaunsi machine”
- IP = machine ka address //192.168.1.10
- Port batata hai “us machine ke andar kaunsa program”
- Port program kaise ho jaata hai?
- Port khud program nahi hota
- Port number ko OS (kernel) program ke socket se jod deta hai
- Port = kernel ke andar ek number
jo incoming data ko correct program ke socket tak pahunchata hai
- bind(s, IP, 8080);
- Program kernel ko bolta hai:
- Port 8080 mujhe de do
- **NOTES**
```txt
#include <sys/types.h>

Definition: Linux/POSIX ka system header file hai, jo system-level programming mein use hone wale data types ki definitions provide karta hai.
It provides:
- pid_t — Process ID store karne ke liye.
- size_t — Object ya memory size represent karne ke liye.
- ssize_t — Signed size type, jo byte count ya -1 error represent kar sakta hai.
- off_t — File offsets represent karne ke liye

Purpose: System calls aur OS-related APIs mein use hone wale standard system data types available karana

```
```bash
int s=socket(int domain,int type,int protocol)

```

```bash
#include <sys/types.h>
#include <sys/socket.h>

int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

// example
struct sockaddr_in server; //IPv4-specific structure

bind(sockfd, (struct sockaddr *)&server, sizeof(server));
```
#### General-purpose structure
```cpp
struct sockaddr {
    sa_family_t sa_family;
    char sa_data[14];
};
```
#### struct sockaddr_in
```cpp
#include <netinet/in.h>
struct sockaddr_in server;
```
- **NOTES**
```txt
#include <netinet/in.h>

Linux/POSIX networking header hai, jo IPv4/IPv6 internet address structures aur internet protocol-related constants provide karta hai

It provides:
- struct sockaddr_in — IPv4 address aur port store karne ke liye.
- struct sockaddr_in6 — IPv6 address aur port store karne ke liye.
- htons() / htonl() — Host byte order ko network byte order mein convert karne ke liye.
- INADDR_ANY — Server ko available local IPv4 interfaces par bind karne ke liye.
- IP
PROTO_TCP / IPPROTO_UDP — TCP aur UDP protocol constants


Purpose: Socket ko IP address aur port ke saath configure karne ke liye required structures aur constants provide karna

```

#### Internal struct sockadd_in
```cpp
struct sockaddr_in {
    short sin_family;       // Address family (IPv4)
    unsigned short sin_port; // Port number
    struct in_addr sin_addr; // IP address
};
```
- sin = socket internet
- `server.sin_family = AF_INET;`
- AF_INET = IPv4
- AF_INET6= IPv6


#### server.sin_addr.s_addr
- server.sin_addr.s_addr = INADDR_ANY; //0.0.0.0
- Server kisi bhi IP address se connection accept karega
- All network interfaces (WiFi, Ethernet, localhost)
```cpp
#include <arpa/inet.h>

inet_pton(AF_INET, "192.168.208.209", &server.sin_addr);
```
```txt
#include <arpa/inet.h>

Linux/POSIX networking header hai, jo IP addresses ko human-readable text format aur network binary format ke beech convert karne ke functions provide karta hai

inet_pton() — IPv4/IPv6 text address ko binary format mein convert karta hai.



inet_ntop() — Binary IP address ko readable text format mein convert karta hai.



inet_addr() — IPv4 text address ko binary representation mein convert karta hai (legacy function).

Purpose: IP addresses ko program mein parse aur display karna


inet_pton() = Internet Presentation to Network

inet_ntop() = Internet Network to Presentation

p = Presentation (readable IP string, e.g. "192.168.1.10")

n = Network (binary network format)

inet_pton() → Readable IP → Binary format
inet_ntop() → Binary format → Readable IP string



```
- Internet Presentation TO Numeric
```cpp
struct in_addr {
    uint32_t s_addr;
};
```
#### server.sin_port
- server.sin_port = htons(8080);
- htons: Host TO Network Short
- Port number ko host byte order se
network byte order (Big Endian) me convert karta hai
- Network protocols Big Endian follow karte hain


## Listen
```cpp
#include<sys/socket.h>
int listen(int sockfd,int backlog)

```
- backlog =kitne pending connections queue me allowed hain
- Queue size for connections waiting to be accepted
- Server accept() call kar ke request ko queue se nikalta hai

## accept()
```cpp
#include <sys/socket.h>
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

//Example
struct sockaddr_in client;
socklen_t client_len = sizeof(client);

int clientfd = accept(sockfd, (struct sockaddr *)&client, &client_len);
```
-  accept() BLOCKS until a client connects


### Header
```cpp
#include <sys/socket.h>   // socket(), bind(), listen(), accept()
#include <netinet/in.h>   // sockaddr_in, INADDR_ANY
#include <arpa/inet.h>    // htons(), htonl(), inet_addr()
#include <unistd.h>       // close()
#include <cstring>        // memset()
```

## send()
- send() transmits raw bytes from a user-space memory buffer to a connected socket.
- The operating system does not understand data types, structures, or objects — it only sends bytes
```cpp
ssize_t send(int sockfd, const void* buffer, size_t length, int flags);

//
send(fd, (const char*)&packet, sizeof(packet), 0);

```
- Casting to char* means:
“Send exactly these N bytes starting from this memory address.”

| Return value | Meaning                           |
| ------------ | --------------------------------- |
| `> 0`        | Number of bytes successfully sent |
| `0`          | Connection closed by peer         |
| `-1`         | Error occurred                    |

```cpp
ssize_t send(
    int sockfd,        // pipe / socket FD
    const void *buf,   // data kahan se bhejna hai
    size_t len,        // kitna data bhejna hai
    int flags
);
```

## recv()
- recv() receives raw bytes from a connected socket into a user-space memory buffer.
- The operating system does not interpret the data — it only delivers bytes exactly as sent

```cpp
ssize_t recv(int sockfd, void* buffer, size_t length, int flags);

// Example: Receiving a struct
struct OrderPacket pkt;
ssize_t n = recv(fd, (char*)&pkt, sizeof(pkt), 0);
```
| Return value | Meaning                                    |
| ------------ | ------------------------------------------ |
| `> 0`        | Number of bytes successfully received      |
| `0`          | Connection closed by peer (graceful close) |
| `-1`         | Error occurred                             |

- recv() BLOCKS until data arrives

```cpp
ssize_t recv(
    int sockfd,        // pipe
    void *buf,         // data kahan rakhna hai
    size_t len,        // maximum kitna lena hai
    int flags
);

```
- recv ka 3rd parameter = kitne BYTES chahiye
buffer ka size nahi, DATA ka size
# Client

## Create a socket
```cpp
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

int sockfd = socket(AF_INET, SOCK_STREAM, 0); // TCP
if (sockfd < 0) {
    perror("socket failed");
    return 1;
}


```
## Specify server address
```cpp
struct sockaddr_in server;
server.sin_family = AF_INET;
server.sin_port = htons(8080); // server port

// Convert IP string to numeric format
inet_pton(AF_INET, "192.168.1.100", &server.sin_addr);
```
## Connect to the server
```cpp
int ret = connect(sockfd, (struct sockaddr*)&server, sizeof(server));
if (ret < 0) {
    perror("connect failed");
    close(sockfd);
    return 1;
}

```
- Client blocks until server accepts connection (unless non-blocking)

## Send data to server
```cpp
struct OrderPacket pkt;
pkt.id = 101;
pkt.price = 5000;

ssize_t n = send(sockfd, (char*)&pkt, sizeof(pkt), 0);
if (n <= 0) {
    perror("send failed");
}

```
- BLOCKS until data sent
## Receive data from server
```cpp
struct ResponsePacket resp;
ssize_t n = recv(sockfd, (char*)&resp, sizeof(resp), 0);
if (n == 0) {
    // server closed connection
} else if (n < 0) {
    perror("recv failed");
}

```
- BLOCKS until data received
## Full Client Header List
```cpp
#include <sys/socket.h>   // socket(), connect(), send(), recv()
#include <netinet/in.h>   // sockaddr_in
#include <arpa/inet.h>    // htons(), htonl(), inet_pton()
#include <unistd.h>       // close()
#include <cstring>        // memset(), memcpy()
#include <cerrno>         // errno
#include <cstdio>         // perror()

```


## EPOLL
- Bell system ko kaam karta hua dekho



## STORY
- bind() ke waqt kernel apni table me entry karta hai:
“Port X → is socket → is program”
- Port number kernel ke liye ek key hai,
jisse wo incoming data ko correct socket (aur uske program) tak pahunchata hai.

```bash
P1
int s1 = socket(AF_INET, SOCK_STREAM, 0);

P2
int s2 = socket(AF_INET, SOCK_STREAM, 0);
# Kernel ke andar aise hota hai
Process P1 (PID 1001)
FD Table:
  3  ───▶  Socket Object A

Process P2 (PID 2002)
FD Table:
  3  ───▶  Socket Object B



bind(s1, 192.168.1.10, 8080);
Kernel kya karta hai:
P1 ki FD table dekhta hai

FD 3 → Socket Object A

Socket Object A ke andar likhta hai:
local_ip   = 192.168.1.10
local_port = 8080


Kernel ek global port table me entry karta hai:

Port 8080 ───▶ Socket Object A

NOTE : P2 ka FD 3 yahan bilkul involved nahi

listen(s1, 5);
Socket Object A ka state: LISTEN



Client connect() karta hai
Kernel kya karta hai:

Client ke socket object B ko:

Random source port deta hai (e.g. 53012)

TCP SYN packet bhejta hai:
SRC: 192.168.1.20 : 53012
DST: 192.168.1.10 : 8080

Server ko packet milta hai
Packet server machine ke kernel me aata hai:
Kernel dekhta hai:
Destination Port = 8080

Global port table:
8080 ───▶ Socket Object A (LISTEN)
Kernel bolta hai:
“Ye server ke liye hai”


accept() ka magic (sabse important)
int cfd = accept(s1);
Kernel kya karta hai:

Naya Socket Object C banata hai

Is socket ke andar likhta hai:
local_ip   = 192.168.1.10
local_port = 8080
peer_ip    = 192.168.1.20
peer_port  = 53012



P1 ki FD table me naya entry:
FD 4 ───▶ Socket Object C
LISTEN socket A aur CONNECTED socket C alag hote hain


Process PID 3001
FD Table:
  3 → struct file → socket A (LISTEN)
  4 → struct file → socket B (ESTABLISHED)

//
FD 3 → socket object
        └─ struct sock
             local_ip   = 192.168.1.10
             local_port = 8080
             peer_ip    = 0
             peer_port  = 0
             state      = LISTEN


ONE PROCESS (PID 1000)

FD TABLE:
  3 → listen socket
  4 → client socket #1
  5 → client socket #2
  6 → client socket #3
  ...



FD table ek hi hai
👉 Har accept() = naya FD + naya socket object

“Jitne connection banenge, utne process ki FD table object banenge kya?”

❌ Nahi

✔️ Jitne process honge, utni FD tables hongi
✔️ Jitne connections honge, utne socket objects honge

Jo system call ek FD return karta hai,
uske peeche kernel me ek naya object hota hai


```

- Data how recieve
```bash
Server already running
lfd = socket()
bind(lfd, 192.168.1.10:8080)
listen(lfd)

Client kahin se connect karega:
Client IP = 192.168.1.20


STEP 0: Server ka initial state
Server FD table
PID 1000 (Server)

FD TABLE:
  3 → struct file → socket A (LISTEN)

Socket A (struct sock) ke andar:
local_ip   = 192.168.1.10
local_port = 8080
state      = LISTEN

Kernel ke paas global port table:
Port 8080 → socket A




STEP 1: Client connect() call karta hai
Client code:
connect(sockfd, 192.168.1.10, 8080);
Client kernel kya karta hai:
Client socket ko random port deta hai
client_port = 53012

TCP SYN packet bhejta hai
SRC: 192.168.1.20 : 53012
DST: 192.168.1.10 : 8080
FLAG: SYN

STEP 2: Server kernel ko SYN packet milta hai

Packet server machine pe aata hai.
Kernel ka logic:

Destination IP check → OK

Destination Port check → 8080

Port table dekhta hai:
8080 → socket A (LISTEN)

Kernel bolta hai:

“Ye server ke listen socket ke liye hai”


STEP 3: Kernel NEW socket object banata hai (connection ke liye)


Bahut important point
LISTEN socket data ke liye use nahi hota.

Kernel kya karta hai:

Naya socket object B banata hai

Ye ek connected socket hoga

Socket B ke andar:

local_ip   = 192.168.1.10
local_port = 8080
peer_ip    = 192.168.1.20
peer_port  = 53012
state      = SYN_RECEIVED

Kernel SYN-ACK bhejta hai.

STEP 4: TCP handshake complete

Client ACK bhejta hai.

Socket B state = ESTABLISHED
Ab connection ban chuka hai



STEP 5: accept() ka role (bahut clear kar lo)
Server code:
cfd = accept(lfd);

Kernel kya karta hai:

Socket B (already created) uthata hai

Server process ki FD table me entry karta hai

FD TABLE:
  3 → socket A (LISTEN)
  4 → socket B (CONNECTED)

cfd = 4 return karta hai
accept() socket nahi banata
accept() already-bane socket ko FD deta hai

STEP 6: Client data bhejta hai

  write(sockfd, "HELLO", 5);

SRC: 192.168.1.20 : 53012
DST: 192.168.1.10 : 8080
DATA: HELLO


STEP 7: Server kernel data ko route karta hai

Server kernel:

Packet dekhta hai

4-tuple match karta hai:
(192.168.1.20, 53012,
 192.168.1.10, 8080)
Match milta hai → Socket B

Data sk_receive_queue me daal deta hai
STEP 8: Server program ko data milta hai
read(cfd, buf, 5);
Kernel:
Socket B ke receive buffer se data nikaal ke deta hai
buf = "HELLO"

NIC → IP → TCP → socket object → receive buffer → read() → user buffer

[ Ethernet | IP | TCP | DATA("HELLO") ][ Ethernet | IP | TCP | DATA("HELLO") ]

STEP 2: Kernel interrupt handler

Kernel:

NIC interrupt handle karta hai

Packet ko kernel data structure me wrap karta hai
struct sk_buff *skb;
skb = packet ka container

STEP 3: IP layer
Kernel:

Ethernet header hataata hai

IP header padhta hai

Destination IP verify karta hai

TCP protocol dekhta hai → TCP ko pass


STEP 4: TCP layer (most important)

TCP stack:

TCP header padhta hai

src_ip, src_port
dst_ip, dst_port

🔥 4-tuple se socket lookup karta hai

Kernel ke paas hota hai:

hash table:
(src_ip, src_port, dst_ip, dst_port) → socket B

Socket B mil gaya

STEP 5: TCP checks

TCP:

Sequence number check

ACK management

Retransmission logic

Order maintain karta hai

Data valid hai → next step

STEP 6: Data socket ke receive buffer me

Kernel:

skb ka DATA part nikaalta hai

Socket B ke receive queue me daal deta hai

socket B:
  sk_receive_queue:
    [ "HELLO" ]

Abhi tak program ko kuch nahi mila


STEP 7: Program read() call karta hai
read(cfd, buf, 5);
Kernel:

FD → socket B

Socket B ke receive buffer check karta hai

Data available hai? → YES

Kernel-to-user copy karta hai
"HELLO" → user buffer (buf)

STEP 8: read() return

read() returns 5

Program ke paas:
buf = "HELLO"
Actual moment yahin hai jahan data mila









Haan — har socket object kernel ke andar unique hota hai.
Lekin socket object ka koi user-visible “number” nahi hota jaise FD hota hai.

Socket object = kernel memory me ek alag structure

Har socket() aur har accept():

naya socket object create karta hai

jo poore OS me alag (unique) hota hai



FD (File Descriptor) sirf ek number hota hai,
jo process ko batata hai: “kernel ke kis object se baat karni hai”.

Bas. FD koi socket nahi, koi data stream nahi, koi file nahi.


```






```bash


Linux Socket Flow (Server)
socket()
   ↓
bind()
   ↓
listen()
   ↓
accept()
   ↓
read()/write()
   ↓
close()



Linux Socket Flow (Client)

socket()
   ↓
connect()
   ↓
read()/write()
   ↓
close()


```


## Basic TCP Client 

```cpp
#include<iostream>
#include<cstring>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define PORT 8080

int main(){

    int clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[1024];

    clientSocket=socket(AF_INET,SOCK_STREAM,0);

    memset(&serverAddr,0,sizeof(serverAddr));

    serverAddr.sin_family=AF_INET;
    serverAddr.sin_port=htons(PORT);
    serverAddr.sin_addr.s_addr=inet_addr("127.0.0.1");

    connect(clientSocket,(struct sockaddr*)&serverAddr,sizeof(serverAddr));

    recv(clientSocket,buffer,1024,0);

    printf("DATA Recieved : %s",buffer);

    return 0;

}
````
- for server run netcat command
```bash
nc 127.0.0.1 -l 8080
```

## Basic TCP server
```cpp
#include<iostream>
#include<cstring>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>

# define PORT 8080

int main(){

    int serverfd, clientfd;;
    struct sockaddr_in serverAddr, clientAddr;
    memset(&serverAddr,0,sizeof(serverAddr));

    socklen_t client_addr_size;
    char buffer[1024];
    strcpy(buffer,"hello client rohit");


    serverfd=socket(AF_INET,SOCK_STREAM,0);

    serverAddr.sin_family=AF_INET;
    serverAddr.sin_port=htons(PORT);
    serverAddr.sin_addr.s_addr=inet_addr("127.0.0.1");

    bind(serverfd,(struct sockaddr*)&serverAddr,sizeof(serverAddr));

    listen(serverfd,5);

    client_addr_size=sizeof(clientAddr);
    clientfd=accept(serverfd,(struct sockaddr*)&clientAddr,&client_addr_size);

    send(clientfd,buffer,strlen(buffer),0);
    
    return 0;
}

```
- we can create server or client for testing
```txt
// its client
// udp,
nc -u 127.0.0.1 8080 

//tcp
nc 127.0.0.1 8080


// its server
//udp
nc -u -l 8080

//tcp
nc  -l 8080
```


## Basic UDP client
```cpp
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argCount, char* argValue[])
{

    if (argCount!=2)
    {
        std::cout<<"Invalid command\nEnter Proper Port\n\n"<<std::endl;
        exit(0);
    }

    int port=std::atoi(argValue[1]);
    int clientFd;
    char buffer[1024];
    struct sockaddr_in serverAddr;
    socklen_t serverAddrSize=sizeof(serverAddr);

    clientFd=socket(AF_INET,SOCK_DGRAM,0);

    memset(&serverAddr,0,sizeof(serverAddr));
    serverAddr.sin_family=AF_INET;
    serverAddr.sin_port=htons(port);
    serverAddr.sin_addr.s_addr=inet_addr("127.0.0.1");

    strcpy(buffer,"Hello guys I am UDP client\n");
    
    // Its UDP, so no connect() needed
    sendto(clientFd,buffer,1024,0,(struct sockaddr*)&serverAddr,serverAddrSize);

    std::cout<<"Data sended"<<std::endl;

    return 0;
}

```
## Basic UDP server
```cpp
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argCount, char* argValue[])
{

    if (argCount!=2)
    {
        std::cout<<"Invalid command\nEnter Proper Port\n\n"<<std::endl;
        exit(0);
    }

    int port=std::atoi(argValue[1]);
    int serverFd, clientFd;
    char buffer[1024];
    struct sockaddr_in serverAddr,clientAddr;
    socklen_t clientAddrSize;
    clientAddrSize=sizeof(clientAddr);

    serverFd=socket(AF_INET,SOCK_DGRAM,0);

    memset(&serverAddr,0,sizeof(serverAddr));
    serverAddr.sin_family=AF_INET;
    serverAddr.sin_port=htons(port);
    serverAddr.sin_addr.s_addr=inet_addr("127.0.0.1");

    bind(serverFd,(struct sockaddr*)&serverAddr,sizeof(serverAddr));

    //UDP is connectionless, so there is no listen() or accept()

    recvfrom(serverFd,buffer,1024,0,(struct sockaddr*)&clientAddr,&clientAddrSize);

    std::cout<<"Data Recieved : "<<buffer<<std::endl;

    return 0;
    // nc -u 127.0.0.1 8080
}
```