#pragma once

#include <ospf/math/symbol/symbol/concepts.hpp>
#include <ospf/math/symbol/expression.hpp>

namespace ospf
{
    inline namespace math
    {
        inline namespace symbol
        {
            template<Invariant T, ExpressionCategory cat>
            class IExprSymbol
                : public Symbol<IExprSymbol<T, cat>>, public Expression<T, cat, IExprSymbol<T, cat>>
            {
                using SymbolImpl = Symbol<IExprSymbol<T, cat>>;

            public:
                using ValueType = OriginType<T>;
                static constexpr ExpressionCategory category = cat;

            public:
                constexpr IExprSymbol(std::string name)
                    : SymbolImpl(std::move(name)) {}

                constexpr IExprSymbol(std::string name, std::string display_name)
                    : SymbolImpl(std::move(name), std::move(display_name)) {}

                constexpr IExprSymbol(const IExprSymbol& ano) = default;
                constexpr IExprSymbol(IExprSymbol&& ano) noexcept = default;
                constexpr IExprSymbol& operator=(const IExprSymbol& rhs) = default;
                constexpr IExprSymbol& operator=(IExprSymbol&& rhs) noexcept = default;
                virtual ~IExprSymbol(void) noexcept = default;

            protected:
                virtual RetType<ValueType> value_by(const std::function<Result<ValueType>(const std::string_view)>& values) const noexcept = 0;

            OSPF_CRTP_PERMISSION:
                inline constexpr const bool is_pure(void) const noexcept
                {
                    return false;
                }

                inline constexpr RetType<ValueType> get_value_by(const std::function<Result<ValueType>(const std::string_view)>& values) const noexcept
                {
                    auto ret = values(this->name());
                    if (ret.is_succeeded())
                    {
                        return std::move(ret).unwrap();
                    }
                    else
                    {
                        return value_by(values);
                    }
                }
            };

            template<ExpressionType Expr>
            class ExprSymbol
                : public IExprSymbol<typename Expr::ValueType, Expr::category>
            {
                using Interface = IExprSymbol<typename Expr::ValueType, Expr::category>;

            public:
                using ExpressionType = OriginType<Expr>;
                using typename Interface::ValueType;

            public:
                constexpr ExprSymbol(std::string name)
                    : Interface(std::move(name)) {}

                constexpr ExprSymbol(std::string name, std::string display_name)
                    : Interface(std::move(name), std::move(display_name)) {}

            public:
                constexpr ExprSymbol(const ExprSymbol& ano) = default;
                constexpr ExprSymbol(ExprSymbol&& ano) noexcept = default;
                constexpr ExprSymbol& operator=(const ExprSymbol& rhs) = default;
                constexpr ExprSymbol& operator=(ExprSymbol&& rhs) noexcept = default;
                constexpr ~ExprSymbol(void) noexcept = default;

            public:
                inline RetType<ValueType> value_of(const std::function<Result<ValueType>(const std::string_view)>& values) const noexcept override
                {
                    return _expr.value(values);
                }

            private:
                ExpressionType _expr;
            };

            template<typename T>
            concept ExpressionSymbolType = ExpressionType<T> && SymbolType<T>;

            template<typename... Ts>
            concept AllExpressionSymbolType = AllExpressionType<Ts...> && AllSymbolType<Ts...>;

            template<typename V, ExpressionCategory cat, typename T>
            concept ExpressionSymbolTypeOf = ExpressionTypeOf<V, cat, T> && SymbolType<T>;

            template<typename V, ExpressionCategory cat, typename... Ts>
            concept AllExpressionSymbolTypeOf = AllExpressionTypeOf<V, cat, Ts...> && AllSymbolType<Ts...>;
        };
    };
};
