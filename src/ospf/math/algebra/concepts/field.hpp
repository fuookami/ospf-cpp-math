#pragma once

#include <ospf/math/algebra/operator/arithmetic/add.hpp>
#include <ospf/math/algebra/operator/arithmetic/sub.hpp>
#include <ospf/math/algebra/operator/arithmetic/mul.hpp>
#include <ospf/math/algebra/operator/arithmetic/div.hpp>
#include <ospf/math/algebra/operator/arithmetic/rem.hpp>

namespace ospf
{
    inline namespace math
    {
        inline namespace algebra
        {
            inline namespace concepts
            {
                // todo: fix like i8 + i8 -> i32

                template<typename T>
                concept PlusSemiGroup = Arithmetic<T> && Add<T> && AddAssign<T>;

                template<typename T>
                concept PlusGroup = PlusSemiGroup<T> && Sub<T> && SubAssign<T>;

                template<typename T>
                concept TimesSemiGroup = Arithmetic<T> && Mul<T> && MulAssign<T>;

                template<typename T>
                concept TimesGroup = TimesSemiGroup<T> && Div<T> && DivAssign<T>;

                template<typename T>
                concept NumberRing = PlusGroup<T> && TimesSemiGroup<T>;

                template<typename T>
                concept NumberField = NumberRing<T> && TimesGroup<T>;
            };
        };
    };
};
