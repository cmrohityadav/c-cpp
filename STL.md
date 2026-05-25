# STL
## Content
- [array](#array)
- [Vector](#vector)
- []()
- []()
- []()
- []()
- []()
- []()
- []()
- []()
- []()
- []()

## array
contiguous memory
zero heap allocation
cache friendliness
predictable latency
compile-time size
STL interoperability

```cpp
std::array<T, N>

//bas ek stack allocated fixed-size C array ka wrapper hai

template<typename T, size_t N>
struct array {
    T elems[N];
};

// T:data type, N:size
```
- heap allocation nahi
- runtime resize nahi
- vector jaisa dynamic growth nahi
- pure contiguous memory

### Why prefer std::array over vector in latency-sensitive code?
1. no heap allocation
2. deterministic memory layout
3. no reallocation pauses
4. better predictability
5. compiler optimization opportunities
6. stack allocation

### Memory Layout
```bash
std::array<int,4>price{1,2,3,4};


#  Memory
| 1 | 2 | 3 | 4 |
- Pure contiguous


# Important property
price.data();
- returns raw pointer to first element

```
### API
```cpp
std::array<int,5>arr{1,2,3,4,5};
// Access
arr[i];
arr.at(i);
arr.front();
arr.back();

// Iterators
std::array<int,5>::iterator p_itr;
begin()
end()
rbegin()
rend()

// Algorithms
std::sort(arr.begin(), arr.end());

// Compile-Time Size
arr.size();
arr.empty();

// Copy Semantics
int a[3];
int b[3];

b = a; // invalid

std::array<int,3> a,b;
b = a; // valid, Because std::array ek proper class hai
```
# TODO
```bash
std::array<Order, 1024>
Sequential traversal:

fewer cache misses
predictable access
hardware prefetching

Interviewer keywords:

L1 cache
cache line
spatial locality
false sharing


std::array<int, n> // invalid if n runtime
Constexpr + Compile-Time Programming
constexpr std::array<int,3> arr{1,2,3};

Alignment + SIMD
alignas(64) std::array<int,16> arr;

memory alignment
cache lines
branch prediction
allocators
move semantics
RAII
constexpr
templates
lock-free programming
atomics
NUMA basics

```

## Vector
- std::vector = `contiguous dynamic array`

```cpp
std::vector<int> v = {10,20,30};

```
### Most Important Internal Structure
```cpp
T* data_;
size_t size_;
size_t capacity_;
```
- size() : Actual elements
- capacity() : Allocated memory slots

### Push_back internally kya karta hai?
```bash
v.push_back(10)

case 1: capacity available -> Simple insert O(1)

case 2: capacity full 
size = 4
capacity = 4
# Now push_back
1. new bigger memory allocate karega
2. old elements copy/move karega
3. old memory free karega
4. new element insert karega
- Yeh expensive hai.
```

### Reallocation ka dangerous part
- Sab iterators/pointers/reference invalid ho sakte hain.
```cpp
std::vector<int> v;

v.push_back(1);

int* p = &v[0];

v.push_back(2); // may reallocate

std::cout << *p; // UB possible
```

### reserve()
```cpp
std::vector<int> v;
v.reserve(100000);
```
- Ab repeated reallocations nahi hongi

### resize()
```cpp
v.resize(100);
```
### emplace_back()



<!-- TODO -->
memory layout
cache locality
allocator
iterator invalidation
growth strategy
latency impact
move vs copy
reallocation cost
thread-safety
false assumptions in interviews
production use-cases

Companies ask:

Why vector contiguous?
Why amortized O(1)?
Difference between reserve and resize?
Iterator invalidation?
Why vector faster than list?
When vector bad?
How vector grows internally?
Why noexcept move important?
What happens during reallocation?
Difference between emplace_back and push_back?
Thread safety?
Can vector store polymorphic objects?
Why vector<bool> special?

##  Best Way To Study (Realistic HFT Path)
Phase 1

Master:

memory layout
stack vs heap
contiguous storage
Phase 2

Implement:

ring buffer
small vector
fixed allocator
Phase 3

Read:

generated assembly (-S)
Godbolt Compiler Explorer
cache miss behavior
Phase 4