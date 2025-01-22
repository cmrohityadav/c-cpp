# Register
- When you declare a register int, you are telling the compiler: "I do not need a memory address for this variable because it will be accessed frequently."
- Registers are designed for temporary storage of data during computation, and they are not meant to be accessed via memory pointers
- The register keyword in C was historically used to suggest that a variable should be stored in a CPU register instead of RAM to optimize its access speed. Accessing data from a register is much faster than accessing it from memory because registers are part of the CPU itself.



# Static Variable Characteristics

- Declared with the static keyword inside the function.
- Its memory is allocated in the data segment (not in the call stack).
- It retains its value between function calls, unlike normal local variables that are destroyed once the function call ends.
- The static variable is initialized only once, and its value persists across multiple calls to the function.