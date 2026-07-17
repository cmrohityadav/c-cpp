
## auto
### Return  Type Deduction
```cpp
auto add(int a,int b)
{
    return a+b;
}

```

### Generic Lambadas
```cpp
auto add =[](auto x,auto y){ return x+ y;};
std::cout<<add(10,20)<<std::endl;
```