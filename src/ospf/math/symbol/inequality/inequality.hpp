#pragma once

#include <ospf/math/symbol/expression.hpp>

namespace ospf
{
    inline namespace math
    {
        inline namespace symbol
        {
            template<ExpressionType Lhs, ExpressionType Rhs = Lhs>
            class Inequality
            {
            public:
                using LhsType = OriginType<Lhs>;
                using LhsValueType = typename LhsType::ValueType;
                using RhsType = OriginType<Rhs>;
                using RhsValueType = typename RhsType::ValueType;

            private:
                LhsType _lhs;
                RhsType _rhs;
                InequalitySign _sign;
            };
        };
    };
};
