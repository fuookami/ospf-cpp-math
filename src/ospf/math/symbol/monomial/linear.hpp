#pragma once

#include <ospf/math/symbol/monomial/concepts.hpp>
#include <ospf/memory/reference.hpp>

namespace ospf
{
    inline namespace math
    {
        inline namespace symbol
        {
            template<Invariant T = f64, PureSymbolType PSym = PureSymbol, typename ESym = IExprSymbol<T, ExpressionCategory::Linear>>
                requires ExpressionSymbolTypeOf<T, ExpressionCategory::Linear, ESym>
            class LinearMonomialCell
                : public Expression<T, ExpressionCategory::Linear, LinearMonomialCell<T, PSym, ESym>>
            {
                using Variant = std::variant<Ref<OriginType<PSym>>, Ref<OriginType<ESym>>>;
                using Impl = Expression<T, ExpressionCategory::Linear, LinearMonomialCell<T, PSym, ESym>>;

            private:
                Variant _symbol;
            };

            template<Invariant T = f64, PureSymbolType PSym = PureSymbol, typename ESym = IExprSymbol<T, ExpressionCategory::Linear>>
            using LinearMonomial = Monomial<T, ExpressionCategory::Linear, LinearMonomialCell<T, PSym, ESym>>;

            namespace linear
            {
                // todo: operators
            };
        };
    };
};
