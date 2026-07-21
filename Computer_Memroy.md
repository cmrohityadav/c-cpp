# Computer Memory

## Decimal Number
- Har ek position Represents a Power of 10
```txt
eg. 352
- Right side se position denge 0,1,2,3...
2 × 10⁰ = 2
5 × 10¹ = 50
3 × 10² = 300

final sum = 300 + 50 + 2 = 352

```
## Binary Number
- Har ek position Represents a Power of 2
- Binary Number System uses only 2 digits: 1 and 0
```txt
eg. 11001

- right side se position denge 0,1,2,3...

1 × 2⁰ = 1
0 × 2¹ = 0
0 × 2² = 0
1 × 2³ = 8
1 × 2⁴ = 16

final sum = 16 + 8 + 0 + 0 + 1 = 25
```
## Bits and Bytes
### What is a Bit?
- A bit (Binary Digit) is the smallest unit of data in a computer.
- A bit can have only two possible values:
- 1 = ON (high voltage)
- 0 = OFF (low voltage)
- 0 or 1 = a bit

### What is a Byte?
- A single bit can store only one of two values: 0 or 1
- To store more information, bits are grouped together
- It's combination of 8 bit = 1 byte
- Example: 10101100= 8 bits = 1 byte

- `Every piece of data inside a computer is ultimately stored as bits`

## Decimal to Binary Conversion
- Step 1: Repeatedly divide the decimal number by 2.
- Step 2: Store the remainder after each division.

- Step 3:Read all remainders from `bottom to top`
```txt
25 ÷ 2 = 12 remainder 1
12 ÷ 2 = 6  remainder 0
6  ÷ 2 = 3  remainder 0
3  ÷ 2 = 1  remainder 1
1  ÷ 2 = 0  remainder 1

Read remainders from bottom to top: 11001

Therefore:

25₁₀ = 11001₂
```
- Read remainders from `bottom to top`: `11001`

# Binary  to  Decimal Conversion
- Step 1: Start from the `rightmost` bit.
- Step 2: Assign powers of 2.
- Step 3: Multiply each bit by its power of 2.
- Step 4: Add all results.
```txt
11001₂ = ?

Step 1: Assign Powers of 2

Binary Bit : 1   1   0   0   1
Power      : 2⁴  2³  2²  2¹  2⁰

Step 2: Multiply Each Bit

1 × 2⁰ = 1
0 × 2¹ = 0
0 × 2² = 0
1 × 2³ = 8
1 × 2⁴ = 16

Step 3: Add All Values
16 + 8 + 0 + 0 + 1
= 25
Final Answer
11001₂ = 25₁₀
```
## Unsigned Integers
### What is an Unsigned Integer?
- An unsigned integer stores only non-negative values.
- eg.: 0,1,2,3,4,....
- There is no negative sign.

### How Many Values Can n Bits Store?
```txt
Each bit has two possible values:
0
1

Therefore:
Total Values = 2ⁿ

where:
n = number of bits
```
```txt
Example: 1 Bit
0
1

Total:
2¹ = 2 values
------------------------
Example: 2 Bits
00 = 0
01 = 1
10 = 2
11 = 3

Total:

2² = 4 values

Range:

0 to 3
------------------------
Example: 3 Bits
000 = 0
001 = 1
010 = 2
011 = 3
100 = 4
101 = 5
110 = 6
111 = 7

Total:

2³ = 8 values

Range:

0 to 7
------------------------
Example: 8 Bits
00000000 = 0
...
11111111 = 255

Total values:

2⁸ = 256

Range:

0 to 255

------------------------

```
- 2^8=256 different values(number of combination)
```txt
Number of possible combinations = 2ⁿ

2⁸ = 256 combinations
they are:
00000000
00000001
00000010
...
...
11111111

There are exactly 256 different bit patterns

```
- each unique bit pattern represents one value
```txt
For an 8-bit unsigned integer:

00000000 = 0
00000001 = 1
00000010 = 2
...
...
11111111 = 255

256 combinations = 256 representable values
2⁸ = 256 possible bit combinations
```

## Unsigned Integers
n bits (unsigned)

Minimum = 0
Maximum = 2ⁿ - 1

```txt
Examples

8 Bits

Minimum = 0

Maximum = 2⁸ - 1 = 256 - 1 = 255

Range:

0 to 255
```

| Bits | Range           |
| ---- | --------------- |
| 8    | 0 to 255        |
| 16   | 0 to 65535      |
| 32   | 0 to 4294967295 |

## Signed Integers
### What is a Signed Integer?
- A signed integer can store: Negative Numbers, Zero, Positive Numbers

- Example:-5,-1,0,1,2,5

```txt
8 bits

Range: -128 to 127

Same 256 combinations exist.

But now some combinations represent negative numbers
-------------------
Total Combinations Do Not Change

For 8 bits:

2⁸ = 256 combinations

This never changes.

Whether the number is signed or unsigned:

Total combinations = 256

Only the interpretation changes
----------------------
```
### General Formula
- Minimum = -2ⁿ⁻¹
- Maximum = 2ⁿ⁻¹ - 1

Example: 8-bit signed integer

Minimum =-2⁷= -128
Maximum = 2⁷-1= 127

```txt
DIVIDE By Half
256 / 2 = 128

Negative side: 128 values
(-128 ... -1)

Non-negative side: 128 values
(0 ... 127)
```
## Two's Complement
```txt
Problem??

We know that an 8-bit signed integer can store: -128 to 127

But how does the computer store a negative number?

Example:-1,-5,-10,-128

Memory can store only:
0
1

So how are negative numbers represented?

The answer is: Two's Complement

```
### What is Two's Complement?
- Two's Complement is the standard method used by modern computers to represent negative numbers
- Almost every CPU uses Two's Complement
```txt
How to Find Two's Complement?
Step 1

Write the positive number in binary.

Example:

5

00000101
Step 2

Invert all bits (0→1, 1→0)

00000101

↓

11111010
Step 3

Add 1

11111010
+       1
---------
11111011

Result:

11111011

Therefore:

-5 = 11111011

in an 8-bit signed integer.
--------------------------------
Example: -1
Positive 1
00000001
Invert Bits
11111110
Add 1
11111111

Therefore:

-1 = 11111111
-----------------------------
In signed integers:

Most Significant Bit (MSB)

acts as the sign indicator.

0xxxxxxx → Positive

1xxxxxxx → Negative
```
```txt
Suppose memory contains:
11111011

Memory only stores bits
It does NOT store:
positive
negative
char
int
float

Memory simply stores:

11111011

If Interpreted as Unsigned
11111011

Convert to decimal:

128 + 64 + 32 + 16 + 8 + 2 + 1
= 251

Result:

251
---------------------------------
If Interpreted as Signed (Two's Complement)

11111011

MSB (leftmost bit) is:

1

In signed integers:

MSB = 1 → Negative
MSB = 0 → Positive

Now apply Two's Complement rules:

11111011

Invert:
00000100

Add 1:
00000101

= 5

Therefore:

-5

Same bits:

11111011

can mean:

251   (unsigned)
-5    (signed)
```

////
## ASCII and Character Encoding
```txt
ASCII stands for:
American Standard Code for Information Interchange

ASCII assigns a number to every character.

Character Decimal Value 
A 65 
B 66 
C 67 

a 97 
b 98 
c 99 

0 48 
1 49 
2 50
```
```txt
Everything is Bits in Memory

char ch = 'A';
Inside memory, the computer does not store "A".
It stores a number.

For the character 'A', the ASCII code is:

A = 65

And 65 in binary is:

01000001

So memory contains:

Address     Data
1000        01000001


-------------------------
char ch = 'A';
int x = 65;

Both represent the number 65.

The difference is how your program interprets the bits

---------------------------------
Where Does 'A' Come From?

The operating system, terminal, or console knows a character encoding such as ASCII or UTF-8.

```
```txt
Problem with ASCII

ASCII assigns a number to each character.

Example:

A = 65
B = 66
C = 67

ASCII works well for English.

But what about:

नमस्ते
你好
こんにちは
😀
€
₹

ASCII cannot represent these characters.

ASCII supports only about 128 standard characters.


Unicode

Unicode is a universal character standard.

Goal:

Every character in every language
gets a unique number.

Examples:

A        → U+0041
₹        → U+20B9
😀       → U+1F600
न        → U+0928

These values are called:

Unicode Code Points


What is a Code Point?

A code point is a unique number assigned to a character.

Examples:

Character      Code Point

A              U+0041
B              U+0042
₹              U+20B9
😀             U+1F600

Think of it as:

Character ID

Unicode is NOT Storage

Unicode only defines:

Character → Number

Example:

A → U+0041

But it does not define:

How bytes are stored in memory.

For that we need an encoding.



UTF-8

UTF-8 is the most popular Unicode encoding.

It converts Unicode characters into bytes.

Almost all modern systems use UTF-8.

Examples:

Web Browsers
Linux
Windows
Databases
REST APIs
JSON

UTF-8 Storage
Character: A

Unicode:

U+0041

UTF-8 bytes:

41

Binary:

01000001

Storage:

1 byte
Character: ₹

Unicode:

U+20B9

UTF-8 bytes:

E2 82 B9

Storage:

3 bytes
Character: 😀

Unicode:

U+1F600

UTF-8 bytes:

F0 9F 98 80

Storage:

4 bytes



ASCII
│
├─ Character Set
├─ 128 Characters
└─ 1 Byte
Unicode
│
├─ Universal Character Standard
└─ Defines Code Points
UTF-8
│
├─ Encoding for Unicode
├─ 1 to 4 Bytes
└─ Most Widely Used
```

## Memory Layout
```txt
main.cpp
      ↓

Compiler

      ↓

Executable (.exe / a.out)

      ↓

Run

```
- Jab OS executable run karta hai...
- OS process create karta hai
- Har process ko apna virtual memory space milta hai
- Imagine karo ek 64-bit process
- Uske andar memory kuch aisi dikhti hai
- Ye hi process memory layout hai
```txt
Higher Address
+----------------------+
|        Stack         |
|                      |
|                      |
|----------------------|
|                      |
|                      |
|        Heap          |
|                      |
|----------------------|
|        (empty)       |
|----------------------|
|        BSS           |
|----------------------|
|       Data           |
|----------------------|
|       Text           |
+----------------------+

Lower Address
```
### Text Segment (Code Segment)
```txt
+----------------------+
| main()               |
| printf()             |
| functions            |
| instructions         |
+----------------------+
```
- Isme Machine code hota hai, Compiler ne jo assembly generate ki thi...
- Ye sirf instructions hain
```bash
mov
add
call
ret
```
- Ye CPU execute karta hai
### Data Segment
- Yaha initialized global variables rehte hain.
```c++
int age = 22;
int g = 100;

double pi = 3.14;

char c = 'A';
```
- Sab initialized hai
- `Age` program start hone se pehle hi memory me aa jata hai, Kab??  Executable load hote hi
#### Lifetime
```txt
Program Start

↓

exists

↓

exists

↓

exists

↓

Program End
```
- Kabhi destroy nahi hota beech me
### BSS Segment
- Block Started by Symbol
- Uninitialized globals
```bash
int x;

char buffer[1000];

static int cnt;
```
- Compiler auto matically 0 initize kr deta hai
#### Static Storage
Ab confusion hota hai.

Log bolte

Static Segment

Actually

Static storage me

Global variables

Static variables

Data

BSS

sab included hote hain.

Example

void fun()
{
    static int count = 0;

    count++;
}

count stack pe nahi hai.

Heap pe bhi nahi.

Ye static storage me hai.

### Stack
```cpp
main()
{
    int a;

    int b;
}
```
- Run Hua
- CPU bolta 
```txt
main call hua.

Stack frame banao.
```
```bash
Stack

--------------

return address

saved registers

a

b

```
- Ye pura  `Stack Frame` Kehlata hai
#### Function call
```cpp
void fun()
{
    int x;
}
```
```txt
Main

↓

fun()

Ab stack

+------------+

fun()

x

-------------

main()

a

b

-------------



Jab

fun return

hua

poora frame remove.

main()

a

b

Bas.

Isliye

Automatic Storage.
```
### Heap
```txt
int* p = new int(50);
Step 1

Pointer

p

Stack pe.

Stack

p

Step 2

Memory

50

Heap pe.

Heap

50

Step 3

p

ke andar

heap ka address.

Example

Stack

p = 0x5000

↓

Heap

0x5000

50

Difference

Stack

Automatic

Heap

Manual

Tumko

delete

karna padega.

```
### Complete Memory Layout 

Higher Address
```
+---------------------+
|       Stack         |
|                     |
| int a               |
| int b               |
| pointer p           |
+---------------------+
|                     |
|                     |
|        Heap         |
|                     |
| new int             |
| vector              |
| string data         |
+---------------------+
|                     |
|                     |
|     Free Space      |
+---------------------+
|        BSS          |
| int x;              |
| static int cnt;     |
+---------------------+
|       Data          |
| int g=10;           |
| pi=3.14             |
+---------------------+
|       Text          |
| main()              |
| fun()               |
| machine code        |
+---------------------+

Lower Address
```
---
| Memory Area           | Created         | Destroyed            | Example                       |
| --------------------- | --------------- | -------------------- | ----------------------------- |
| Text                  | Program load    | Program end          | Functions, machine code       |
| Data                  | Program load    | Program end          | `int g = 10;`                 |
| BSS                   | Program load    | Program end          | `int x;`                      |
| Static (local/global) | Program load    | Program end          | `static int count;`           |
| Stack                 | Function call   | Function return      | Local variables, parameters   |
| Heap                  | `new`/allocator | `delete`/deallocator | Dynamically allocated objects |

---
```txt
TEXT   → Code (CPU kya execute karega)
DATA   → Initialized globals/statics
BSS    → Uninitialized globals/statics (zero-initialized)
HEAP   → Dynamic memory (new/delete, malloc/free)
STACK  → Function calls, local variables, parameters
```
- Agar variable ki storage duration static hai (global ya static local), to:
- Initialized → Data Segment (.data)
- Uninitialized ya zero-initialized → BSS Segment (.bss)





