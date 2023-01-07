#pragma once

#include <ospf/math/algebra/concept/arithmetic.hpp>

namespace ospf
{
    inline namespace math
    {
        inline namespace algebra
        {
            template<Arithmetic T>
            struct IsVariant
            {
                static constexpr const bool value = false;
            };

            template<typename T>
            concept Variant = Arithmetic<T> && IsVariant<T>::value;

            template<typename T>
            concept Invariant = Arithmetic<T> && !IsVariant<T>::value;

            // todo
        };
    };
};
