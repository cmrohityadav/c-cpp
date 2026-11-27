#pragma once

#include<cstddef>
#include<type_traits>

#include "core/types.hpp"

namespace exchange::matching{

    struct Level;

    struct alignas(64) Order{
        core::OrderId id{0};
        core::Side side{core::Side::BUY};
        core::Price price{0};
        core::Quantity qty{0};
        core::Quantity original_qty{0};
        core::Quantity display_qty{0};
        core::Quantity hidden_qty{0};
        core::OrderType type{core::OrderType::LIMIT};
        core::OrderStatus status{core::OrderStatus::NEW};
        core::ParticipantId participant_id{0};
        core::Price trigger_price{0};
        core::Quantity peak_qty{0};

        Order* prev{nullptr};
        Order* next{nullptr};
        Level* parent_level{nullptr};

    };

}