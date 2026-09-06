#pragma once

#include<array>
#include<cstddef>
#include<memory>

namespace exchange::core{
    template<typename T,std::size_t N>
    class MemoryPool{
        static_assert(N>0,"MemoryPool capacity must be positive");
        static_assert(sizeof(T)>=sizeof(void *),"Object storage must fit an instrusive free List pointer");
        
    };
}