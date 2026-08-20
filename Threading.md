# Threading
## Process

```
High Address
+------------------+
|      Stack       |  ← function calls, local variables
|        ↓         |
+------------------+

|                  |
|   Free / unused  |
|      space       |
|                  |
+------------------+

|        ↑         |
|       Heap       |  ← dynamic memory (malloc/new)
+------------------+
|      Data        |  ← global/static initialized variables
+------------------+
|       BSS        |  ← global/static uninitialized variables
+------------------+
|   Text / Code    |  ← program instructions
+------------------+
Low Address
```
- ek process k under multiple thread ho skte hai
- Har thread ka apna:
### Stack
Local variables,
Function calls,
Return addresses,
Recursive calls
### Registers / CPU context
Program Counter / Instruction Pointer,
Stack Pointer,
General-purpose registers,
### Thread ID
Thread state,
Running,
Ready,
Blocked / Waiting, etc.
### Thread Control Block (TCB)
OS thread ki information maintain karta hai.

### Process and thread kya kya share krta hai

```

Process
│
├── Code / Text Segment       ← Shared
├── Data Segment              ← Shared
├── BSS                       ← Shared
├── Heap                      ← Shared
│
├── Thread 1
│     ├── Stack 1             ← Private
│     └── Registers / Context ← Private
│
├── Thread 2
│     ├── Stack 2             ← Private
│     └── Registers / Context ← Private
│
└── Thread 3
      ├── Stack 3             ← Private
      └── Registers / Context ← Private

```
## Thread
- Ek process ke andar multiple independent instruction streams ko concurrently execute karna
- Concurrency ≠ Parallelism
- `std::thread t(function, argument1, argument2, ...);`

```
                 std::thread t(work)
                         |
              +----------+----------+
              |                     |
            join()                detach()
              |                     |
              ↓                     ↓
      Current thread          Current thread
        BLOCKS ⛔              doesn't wait
              |                     |
              ↓                     ↓
    t ke finish hone tak     t independently
       wait karta hai          execute karta hai
```
- detach() ke baad std::thread object destroy ho sakta hai, actual detached thread nahi — woh process ke alive rehne tak independently chal sakta hai
```cpp
// Member function of class
class A {
public:
    void work(int x) {
        std::cout << x;
    }
};



A obj;

std::thread t(&A::work, &obj, 100);

t.join();
```

- below example for: why we need mutex
```cpp
#include<iostream>
#include <thread>
int counter=0;

void inc(){
    for(int i=0;i<1000000;i++){
        counter++;
    }
}

void dec(){
    for(int i=0;i<1000000;i++){
        counter--;
    }
}
int main(){

    std::thread tInc(inc);

    std::thread tDec(dec);

    tDec.join();
    tInc.join();

    std::cout<<counter<<std::endl;

    return 0;
}
```

## Mutex
- Shared resources ko ek time pe ek hi Thread acccess kare
- Agar koi shared variable/resource multiple threads use kar rahe hain, aur humne usko protect karne ke liye ek mutex choose kiya hai, toh jitni bhi jagah se us shared resource ko access karenge, wahan same mutex ka lock lena hoga.
```
🚿 Washroom = Shared Resource

🚪 Washroom ka door = Mutex
🔒 Door ko lock karna = mutex.lock()

🔓 Door ko unlock karna = mutex.unlock()

👤 Washroom use karne wala = Thread

```
- as per above example  comparing with counter example
```
counter = 🚿 Washroom

tInc = 👤 Person A
tDec = 👤 Person B

```
- code
```cpp
#include <iostream>
#include <thread>
#include <mutex>

int counter = 0;
std::mutex m;

void inc() {
    for (int i = 0; i < 1000000; i++) {
        m.lock();       // 🚪🔒 washroom occupied

        counter++;

        m.unlock();     // 🚪🔓 washroom free
    }
}

void dec() {
    for (int i = 0; i < 1000000; i++) {
        m.lock();       // same door!

        counter--;

        m.unlock();
    }
}

int main() {
    std::thread tInc(inc);
    std::thread tDec(dec);

    tInc.join();
    tDec.join();

    std::cout << counter << std::endl;
}
```
-  Actual execution ko feel karo
```
Start:

    counter = 0


========== ROUND 1 ==========

tInc:

    🚪🔒 m.lock()
    counter++ : 0 -> 1

Isi time tDec:

    🚪🔒 m.lock() try kiya
    ❌ Door already locked
    🧍 WAIT

Phir tInc:

    🚪🔓 m.unlock()

Ab tDec:

    🚪🔒 Door lock kiya
    counter-- : 1 -> 0
    🚪🔓 Door unlock kiya


========== ROUND 2 ==========

Is baar scheduler ne pehle tDec ko chance diya:

tDec:

    🚪🔒 Door lock
    counter-- : 0 -> -1

Isi time tInc:

    🚪🔒 lock try
    ❌ Door locked
    🧍 WAIT

tDec:

    🚪🔓 unlock

Ab tInc:

    🚪🔒 lock
    counter++ : -1 -> 0
    🚪🔓 unlock


========== ROUND 3 ==========

tInc:

    🚪🔒 lock
    counter++ : 0 -> 1

tDec:

    🚪🔒 lock try
    ❌ WAIT

tInc:

    🚪🔓 unlock

tDec:

    🚪🔒 lock
    counter-- : 1 -> 0
    🚪🔓 unlock


Final:

    counter = 0

```

## Critical section
- lock() aur unlock() ke beech ka woh protected code jahan shared resource ko access ya modify kiya ja raha hai, critical section kehlata hai
```
👤 Thread
   |
   v
🚪🔒 m.lock()      ← Mutex lock / entry secure
   |
   v
🚿 Shared Resource use ho raha hai
   |
   | counter++ / counter--
   | ↑
   | CRITICAL SECTION
   |
   v
🚪🔓 m.unlock()    ← Mutex unlock / doosre thread ke liye free

///

m.lock();

counter++;   // ← Critical Section

m.unlock();

```
```cpp
m.lock();

// ===== CRITICAL SECTION START =====

counter++;
// shared resource ko use/modify kar rahe hain

// ===== CRITICAL SECTION END =====

m.unlock();
```
```
🚿 Washroom        = Shared Resource
🚪 Gate/Door       = Mutex

🔒 m.lock()        = Gate lock karke entry secure karna

🧍 counter++       = Washroom/resource ko use karna
                    ↑
              Critical work

🔓 m.unlock()      = Gate free karna
```
## Locking Mechanisms
### std::lock_guard

- kyu lock_guard?? automatic lock/unlock
```
👤 Person A
   |
   v
🚪🔒 Door lock
   |
   v
🚿 Washroom use
   |
   v
💥 Person ko emergency mein bahar nikalna pada(throw exception,return other..)
   |
   v
🚪🔓 Door unlock karna bhool gaya ❌

Result:
🚪🔒 Door permanently locked
```
- lock guard kya krte hai?
```cpp
std::lock_guard<std::mutex> lock(m);

counter++;
```
```
std::lock_guard
      |
      +---- constructor → 🔒 lock
      |
      +---- scope khatam → 🔓 unlock automatically

/// Analogy

👤 Person
   |
   v
"Main washroom enter kar raha hoon"
   |
   v
🚪🔒 Door automatically lock
   |
   v
🚿 Washroom use
   |
   v
Scope khatam
   |
   v
🚪🔓 Door automatically unlock

```

```cpp
#include <iostream>
#include <thread>
#include <mutex>

int counter = 0;
std::mutex m;

void inc() {
    for (int i = 0; i < 1000000; i++) {

        std::lock_guard<std::mutex> lock(m);

        counter++;
    }
}

void dec() {
    for (int i = 0; i < 1000000; i++) {

        std::lock_guard<std::mutex> lock(m);

        counter--;
    }
}

int main() {
    std::thread tInc(inc);
    std::thread tDec(dec);

    tInc.join();
    tDec.join();

    std::cout << counter << std::endl;
}
```

### std::uniue_lock 
- lock_guard ka more powerful version
- hum bich me .unlock() and .lock() kr skte hai
- scope khatm hote hi unlock() ho jayega
```cpp
#include<iostream>
#include<thread>
#include<mutex>
std::mutex mtx;
void worker(){

    std::unique_lock<std::mutex>lock(mtx);

    std::cout<<"Doing Critical Section..."<<std::endl;

    lock.unlock();

    std::cout << "Doing Non-critical work...\n";

    lock.lock();

    std::cout << "Doing Critical section again...\n";

}

int main(){

    std::thread t1(worker);

    t1.join();

    return 0;
}
```

### std::scoped_lock
// later
### try_lock()
// later
### shared_lock
// later

## 7. Mutex Types

### 7.1 `std::mutex`

### 7.2 `std::recursive_mutex`
### 7.2 `std::shared_mutex`

## 8. Condition Variable

### 8.1 `std::condition_variable`

### 8.2 `wait()`

### 8.3 `notify_one()`

### 8.4 `notify_all()`

## 9. Atomic

### 9.1 `std::atomic`

## 10. Common Problems

### 10.1 Race Condition

### 10.2 Data Race

### 10.3 Deadlock

### 10.4 Starvation

### 10.5 Livelock

## 11. Thread Communication

### 11.1 Producer-Consumer

### 11.2 Future / Promise

### 11.3 `std::async`

## 12. Thread Pool

## 13. Thread-Safe Design

## 14. Real-World Examples

### 14.1 Thread-Safe Counter

### 14.2 Thread-Safe Queue

### 14.3 Producer-Consumer Queue

### 14.4 Thread Pool
