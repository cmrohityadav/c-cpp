#pragma once

#include<array>
#include<cstddef>
#include<memory>

namespace exchange::core{
    template<typename T,std::size_t N>
    class MemoryPool{
        static_assert(N>0,"MemoryPool capacity must be positive");
        static_assert(sizeof(T)>=sizeof(void *),"Object storage must fit an instrusive free List pointer");


        struct alignas((alignof(T)>64U)? alignof(T):64U) Slot{
            std::array<std::byte,sizeof(T)> storage{};

        };

        struct FreeNode{
            FreeNode* nextNode;
        };

        public:
        MemoryPool():slots_(std::make_unique<Slot[]>(N)) {
            initialize_free_list();
        }

        MemoryPool(const MemoryPool& )=delete;
        MemoryPool& operator=(const MemoryPool&)=delete;
        MemoryPool(MemoryPool&&)=delete;
        MemoryPool& operator =(MemoryPool&&)=delete;

        private:

        void initialize_free_list() noexcept{
            free_list_head_=nullptr;

            for(std::size_t index=0;index<N;++index){
                auto* node=reinterpret_cast<FreeNode*>(slots_[index].storage.data());
                node->next=free_list_head_;
                free_list_head_=node;
            }
        }

        std::unique_ptr<Slot[]>slots_;
        FreeNode* free_list_head_{nullptr};

    };
}

