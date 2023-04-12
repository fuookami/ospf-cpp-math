#pragma once

#include <ospf/math/symbol/polynomial/concepts.hpp>

namespace ospf
{
    inline namespace math
    {
        inline namespace symbol
        {
            template<Invariant T = f64, PureSymbolType PSym = PureSymbol, typename ESym = IExprSymbol<T, ExpressionCategory::Linear>>
            using LinearPolynomial = Polynomial<T, ExpressionCategory::Linear, LinearMonomial<f64, PSym, ESym>>;

            namespace linear
            {
                // operators
            };
        };
    };
};
