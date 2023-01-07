#pragma once

#include <ospf/math/algebra/concept/arithmetic.hpp>

namespace ospf
{
    inline namespace math
    {
        inline namespace algebra
        {
            inline namespace arithmetic_operator
            {
                template<typename T>
                concept Abs = Arithmetic<T>
                    && requires (const T & value) 
                    { 
                        { std::abs(value) } -> DecaySameAs<T>; 
                    };
            };
        };
    };
};
