#pragma once

#include <ospf/math/symbol/polynomial/concepts.hpp>
#include <ospf/math/symbol/monomial/linear.hpp>

namespace ospf
{
    inline namespace math
    {
        inline namespace symbol
        {
            template<Invariant T = f64, Invariant ST = T, PureSymbolType PSym = PureSymbol, typename ESym = IExprSymbol<T, ST, ExpressionCategory::Linear>>
            using LinearPolynomial = Polynomial<T, ST, ExpressionCategory::Linear, LinearMonomial<T, ST, PSym, ESym>>;

            namespace linear
            {
                // operators between value and symbol

                // operators between symbol and value

                // operators between symbol and symbol
            };
        };
    };
};
