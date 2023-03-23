#pragma once

#include <ospf/concepts/enum.hpp>

namespace ospf
{
    inline namespace math
    {
        inline namespace symbol
        {
            enum class SymbolCategory : u8
            {
                Linear,
                Quadratic,
                Standard,
                Nonlinear
            };
        };
    };
};
