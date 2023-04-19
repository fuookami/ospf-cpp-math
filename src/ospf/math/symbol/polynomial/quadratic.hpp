#pragma once

#include <ospf/math/symbol/polynomial/concepts.hpp>
#include <ospf/math/symbol/monomial/quadratic.hpp>

namespace ospf
{
    inline namespace math
    {
        inline namespace symbol
        {
            template<Invariant T = f64, Invariant ST = T, PureSymbolType PSym = PureSymbol, typename ESym = IExprSymbol<T, ST, ExpressionCategory::Quadratic>>
            using QuadraticPolynomial = Polynomial<T, ST, ExpressionCategory::Quadratic, QuadraticMonomial<T, ST, PSym, ESym>>;

            namespace quadratic
            {
                // operators between value and symbol

                // operators between symbol and value

                // operators between symbol and symbol
            };
        };
    };
};
