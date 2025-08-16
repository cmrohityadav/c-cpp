
# Mutex
std::mutex = taala banane ka nuskha (blueprint)

myMtxTaala = woh taala jo tumhare program ke darwaze par laga hai

# lock_guard
```cpp
{
    std::lock_guard<std::mutex> guard(myMtxTaala);
    counter++;
}
```

myMtxTaala (mutex) = sirf taala (ek object, passive cheez)

guard (lock_guard) = ek insaan jo taala use karta hai aur tumhari taraf se manage karta hai (active helper)


