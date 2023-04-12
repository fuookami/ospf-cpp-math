#pragma once

#include <ospf/math/symbol/polynomial/concepts.hpp>

namespace ospf
{
    inline namespace math
    {
        inline namespace symbol
        {
            template<Invariant T = f64, PureSymbolType PSym = PureSymbol, typename ESym = IExprSymbol<T, ExpressionCategory::Standard>>
            using StandardPolynomial = Polynomial<T, ExpressionCategory::Standard, StandardMonomial<f64, PSym, ESym>>;

            namespace standard
            {
                // operators
            };
        };
    };
};
