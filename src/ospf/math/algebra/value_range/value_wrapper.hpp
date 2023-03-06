#pragma once

#include <ospf/math/algebra/concepts/arithmetic.hpp>
#include <ospf/type_family.hpp>
#include <variant>

namespace ospf
{
    inline namespace math
    {
        inline namespace algebra
        {
            namespace value_range
            {
                template<Arithmetic T>
                class ValueWrapper
                {
                    using Variant = std::variant<OriginType<T>, Infinity, NegetivInfinity>;

                public:
                    using ValueType = OriginType<T>;

                public:


                private:
                    Variant _variant;
                };
            };
        };
    };
};
