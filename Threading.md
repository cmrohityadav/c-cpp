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