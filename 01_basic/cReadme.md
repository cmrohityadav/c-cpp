# compilations
## steps
### 1 HLL
- file.c
```bash
gcc -E file.c>file.i

```
- it generate file.i

### 2 Pre Processor
- Remove all the comments
- File inclusion eg. #include<>
- Micro Expansion eg. #define


now pure HLL


### 3 Compiler
- assembly language after compiler
```bash
gcc  -S file.i
```
- produce file.S
### 4 Assembler
- now it convert assembly language into machine code 
- relocatble

```bash
gcc -c file.S
```

- produce file.o
### 5 Loader | Linker

```bash
gcc -o 
```
- produce a.out

---

# Format Specifiers
%a.b
- a is atleast width of numerical value(atleast a digit)
- b is precious means after decimal point(atleast b digits after point)
- %d :: decimal
- %f:: floaring point
- %c:: print as ascii character


