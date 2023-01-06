#pragma once

#include <ospf/math/algebra/concept/arithmetic.hpp>

namespace ospf
{
    inline namespace math
    {
        inline namespace algebra
        {
            template<typename T>
            struct ScalarTrait;

            template<typename T>
            concept Scalar = Arithmetic<T>
                && requires
                {
                    { ScalarTrait<T> {} };
                };

            // todo
        };
    };
};
