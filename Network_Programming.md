# Network Programming (Socket Programming)
- Build a program that recieves and transmits data between two or more computers by means of a network

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
```cpp
#include<sys/socket.h>

int sockfd=socket(int domain,int type,int protocol)
```
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

```bash
1. int s=socket(int domain,int type,int protocol)
# Program ke paas ek data stream
# Abhi kisi port se juda nahi

2. bind(s, IP, 8080);
# Program kernel ko bolta hai
# Port 8080 mujhe de do
# Port 8080 agar koi use kare,to uska data is socket ko dena
3. Kernel apni table me entry karta hai
# Port 8080 → Socket FD 3 → Process PID 1234
# Port ab “program ka” ho gaya

```

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