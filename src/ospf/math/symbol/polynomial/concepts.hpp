#pragma once

#include <ospf/math/symbol/monomial/concepts.hpp>

namespace ospf
{
    inline namespace math
    {
        inline namespace symbol
        {
            template<Invariant T, ExpressionCategory cat, typename Mono>
                requires MonomialTypeOf<T, cat, Mono>
            class Polynomial
            {
            public:
                using ValueType = OriginType<T>;
                using MonomialType = OriginType<Mono>;

            private:
                std::vector<MonomialType> _monos;
                ValueType _constant;
            };
        };
    };
};
