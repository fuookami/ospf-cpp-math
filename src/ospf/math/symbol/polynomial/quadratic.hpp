#pragma once

#include <ospf/math/symbol/polynomial/concepts.hpp>

namespace ospf
{
    inline namespace math
    {
        inline namespace symbol
        {
            template<Invariant T = f64, PureSymbolType PSym = PureSymbol, typename ESym = IExprSymbol<T, ExpressionCategory::Quadratic>>
            using QuadraticPolynomial = Polynomial<T, ExpressionCategory::Quadratic, QuadraticMonomial<f64, PSym, ESym>>;

            namespace quadratic
            {
                // operators
            };
        };
    };
};
