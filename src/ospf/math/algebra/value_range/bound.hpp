#pragma once

#include <ospf/math/algebra/value_range/interval.hpp>

namespace ospf
{
    inline namespace math
    {
        inline namespace algebra
        {
            namespace value_range
            {
                enum class BoundSide : u8
                {
                    Lower,
                    Upper,
                };
            };
        };
    };
};
