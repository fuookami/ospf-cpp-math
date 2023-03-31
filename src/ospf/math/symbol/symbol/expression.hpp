#pragma once

#include <ospf/math/symbol/symbol/concepts.hpp>
#include <ospf/math/symbol/expression.hpp>

namespace ospf
{
    inline namespace math
    {
        inline namespace symbol
        {
            template<ExpressionType Expr>
            class ExprSymbol
                : public Symbol<ExprSymbol<Expr>>
            {
            };

            // todo: FuncSymbol
        };
    };
};
