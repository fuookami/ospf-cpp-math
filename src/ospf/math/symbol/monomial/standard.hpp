#pragma once

#include <ospf/math/symbol/monomial/concepts.hpp>
#include <ospf/memory/reference.hpp>

namespace ospf
{
    inline namespace math
    {
        inline namespace symbol
        {
            template<Invariant T = f64, PureSymbolType PSym = PureSymbol, typename ESym = IExprSymbol<T, ExpressionCategory::Standard>>
                requires ExpressionSymbolTypeOf<T, ExpressionCategory::Standard, ESym>
            class StandardMonomialCell
                : public Expression<T, ExpressionCategory::Standard, StandardMonomialCell<T, PSym, ESym>>
            {
                using Variant = std::variant<Ref<OriginType<PSym>>, Ref<OriginType<ESym>>>;
                using Impl = Expression<T, ExpressionCategory::Standard, StandardMonomialCell<T, PSym, ESym>>;

            private:
                std::vector<std::pair<Variant, f64>> _symbols;
            };

            template<Invariant T = f64, PureSymbolType PSym = PureSymbol, typename ESym = IExprSymbol<T, ExpressionCategory::Standard>>
            using StandardMonomial = Monomial<T, ExpressionCategory::Standard, StandardMonomialCell<T, PSym, ESym>>;

            namespace standard
            {
                // todo: operators
            };
        };
    };
};
