# STL
## Content
- [array](#array)
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