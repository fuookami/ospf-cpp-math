#pragma once

#include <ospf/math/symbol/monomial/concepts.hpp>
#include <ospf/memory/reference.hpp>

namespace ospf
{
    inline namespace math
    {
        inline namespace symbol
        {
            template<Invariant T = f64, PureSymbolType PSym = PureSymbol, typename ESym = IExprSymbol<T, ExpressionCategory::Quadratic>>
                requires ExpressionSymbolTypeOf<T, ExpressionCategory::Quadratic, ESym>
            class QuadraticMonomialCell
                : public Expression<T, ExpressionCategory::Quadratic, QuadraticMonomialCell<T, PSym, ESym>>
            {
                using Variant = std::variant<Ref<OriginType<PSym>>, Ref<OriginType<ESym>>>;
                using Impl = Expression<T, ExpressionCategory::Quadratic, QuadraticMonomialCell<T, PSym, ESym>>;

            private:
                Variant _symbol1;
                Variant _symbol2;
            };

            template<Invariant T = f64, PureSymbolType PSym = PureSymbol, typename ESym = IExprSymbol<T, ExpressionCategory::Quadratic>>
            using QuadraticMonomial = Monomial<T, ExpressionCategory::Quadratic, QuadraticMonomialCell<T, PSym, ESym>>;

            namespace quadratic
            {
                // todo: operators
            };
        };
    };
};
