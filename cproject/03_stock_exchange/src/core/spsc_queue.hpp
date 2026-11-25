#pragma once

#include<array>
#include<atomic>
#include<cstddef>
#include<cstdint>
#include<type_traits>


namespace exchange::core{
    
    template<typename T,std::size_t N>
    class SPSCQueue{
        static_assert(N>1,"SPSCQueue requires atleast two slots");
        static_assert((N & (N-1U))==0U,"SPSCQueue capacity must be a power of two");

        static_assert(std::is_trivially_copyable_v<T>,"SPSCQueue payloads must be trivially copyable");

        struct alignas(128) Cursor{
            
        };


    };
}
