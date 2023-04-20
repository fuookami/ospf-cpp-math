#pragma once

#include <ospf/math/symbol/polynomial/concepts.hpp>
#include <ospf/math/symbol/monomial/linear.hpp>

namespace ospf
{
    inline namespace math
    {
        inline namespace symbol
        {
            template<Invariant T = f64, Invariant ST = f64, PureSymbolType PSym = PureSymbol, typename ESym = IExprSymbol<T, ST, ExpressionCategory::Linear>>
            using LinearPolynomial = Polynomial<T, ST, ExpressionCategory::Linear, LinearMonomial<T, ST, PSym, ESym>>;

            namespace linear
            {
                // operators between value and symbol

                template<Invariant Lhs, PureSymbolType Rhs>
                inline constexpr decltype(auto) operator+(Lhs&& lhs, const Rhs& rhs) noexcept
                {
                    using ValueType = OriginType<Lhs>;
                    using RetType = LinearPolynomial<ValueType, f64, OriginType<Rhs>>;
                    using MonomialType = typename RetType::MonomialType;
                    return RetType{ { MonomialType{ rhs } }, std::forward<Lhs>(lhs) };
                }

                template<Invariant Lhs, PureSymbolType Rhs>
                inline constexpr decltype(auto) operator-(Lhs&& lhs, const Rhs& rhs) noexcept
                {
                    using ValueType = OriginType<Lhs>;
                    using RetType = LinearPolynomial<ValueType, f64, OriginType<Rhs>>;
                    using MonomialType = typename RetType::MonomialType;
                    return RetType{ { MonomialType{ -ArithmeticTrait<ValueType>::one(), rhs } }, std::forward<Lhs>(lhs) };
                }

                template<Invariant Lhs, ExpressionSymbolType Rhs>
                    requires (Rhs::category == ExpressionCategory::Linear)
                inline constexpr decltype(auto) operator+(Lhs&& lhs, const Rhs& rhs) noexcept
                {
                    using ValueType = OriginType<Lhs>;
                    using RetType = LinearPolynomial<ValueType, f64, PureSymbol, OriginType<Rhs>>;
                    using MonomialType = typename RetType::MonomialType;
                    return RetType{ { MonomialType{ rhs } }, std::forward<Lhs>(lhs) };
                }

                template<Invariant Lhs, ExpressionSymbolType Rhs>
                    requires (Rhs::category == ExpressionCategory::Linear)
                inline constexpr decltype(auto) operator-(Lhs&& lhs, const Rhs& rhs) noexcept
                {
                    using ValueType = OriginType<Lhs>;
                    using RetType = LinearPolynomial<ValueType, f64, PureSymbol, OriginType<Rhs>>;
                    using MonomialType = typename RetType::MonomialType;
                    return RetType{ { MonomialType{ -ArithmeticTrait<ValueType>::one(), rhs } }, std::forward<Lhs>(lhs) };
                }

                // operators between symbol and value

                template<PureSymbolType Lhs, Invariant Rhs>
                inline constexpr decltype(auto) operator+(const Lhs& lhs, Rhs&& rhs) noexcept
                {
                    using ValueType = OriginType<Rhs>;
                    using RetType = LinearPolynomial<ValueType, f64, OriginType<Lhs>>;
                    using MonomialType = typename RetType::MonomialType;
                    return RetType{ { MonomialType{ lhs } }, std::forward<Rhs>(rhs) };
                }

                template<PureSymbolType Lhs, Invariant Rhs>
                inline constexpr decltype(auto) operator-(const Lhs& lhs, Rhs&& rhs) noexcept
                {
                    using ValueType = OriginType<Rhs>;
                    using RetType = LinearPolynomial<ValueType, f64, OriginType<Lhs>>;
                    using MonomialType = typename RetType::MonomialType;
                    return RetType{ { MonomialType{ lhs } }, -std::forward<Rhs>(rhs) };
                }

                template<ExpressionSymbolType Lhs, Invariant Rhs>
                inline constexpr decltype(auto) operator+(const Lhs& lhs, Rhs&& rhs) noexcept
                {
                    using ValueType = OriginType<Rhs>;
                    using RetType = LinearPolynomial<ValueType, f64, PureSymbol, OriginType<Lhs>>;
                    using MonomialType = typename RetType::MonomialType;
                    return RetType{ { MonomialType{ lhs } }, std::forward<Rhs>(rhs) };
                }

                template<ExpressionSymbolType Lhs, Invariant Rhs>
                inline constexpr decltype(auto) operator-(const Lhs& lhs, Rhs&& rhs) noexcept
                {
                    using ValueType = OriginType<Rhs>;
                    using RetType = LinearPolynomial<ValueType, f64, PureSymbol, OriginType<Lhs>>;
                    using MonomialType = typename RetType::MonomialType;
                    return RetType{ { MonomialType{ lhs } }, -std::forward<Rhs>(rhs) };
                }

                // operators between symbol and symbol

                template<PureSymbolType Lhs, PureSymbolType Rhs>
                    requires DecaySameAs<Lhs, Rhs>
                inline constexpr decltype(auto) operator+(Lhs&& lhs, Rhs&& rhs) noexcept
                {
                    using RetType = LinearPolynomial<f64, f64, OriginType<Lhs>>;
                    using MonomialType = typename RetType::MonomialType;
                    return RetType{ { MonomialType{ lhs }, MonomialType{ rhs } } };
                }

                template<PureSymbolType Lhs, PureSymbolType Rhs>
                    requires DecaySameAs<Lhs, Rhs>
                inline constexpr decltype(auto) operator-(Lhs&& lhs, Rhs&& rhs) noexcept
                {
                    using RetType = LinearPolynomial<f64, f64, OriginType<Lhs>>;
                    using MonomialType = typename RetType::MonomialType;
                    return RetType{ { MonomialType{ lhs }, MonomialType{ -1.0_f64, rhs } } };
                }

                template<PureSymbolType Lhs, ExpressionSymbolType Rhs>
                inline constexpr decltype(auto) operator+(Lhs&& lhs, Rhs&& rhs) noexcept
                {
                    using RetType = LinearPolynomial<f64, f64, OriginType<Lhs>, OriginType<Rhs>>;
                    using MonomialType = typename RetType::MonomialType;
                    return RetType{ { MonomialType{ lhs }, MonomialType{ rhs } } };
                }

                template<PureSymbolType Lhs, ExpressionSymbolType Rhs>
                inline constexpr decltype(auto) operator-(Lhs&& lhs, Rhs&& rhs) noexcept
                {
                    using RetType = LinearPolynomial<f64, f64, OriginType<Lhs>, OriginType<Rhs>>;
                    using MonomialType = typename RetType::MonomialType;
                    return RetType{ { MonomialType{ lhs }, MonomialType{ -1.0_f64, rhs } } };
                }

                template<ExpressionSymbolType Lhs, PureSymbolType Rhs>
                inline constexpr decltype(auto) operator+(Lhs&& lhs, Rhs&& rhs) noexcept
                {
                    using RetType = LinearPolynomial<f64, f64, OriginType<Rhs>, OriginType<Lhs>>;
                    using MonomialType = typename RetType::MonomialType;
                    return RetType{ { MonomialType{ lhs }, MonomialType{ rhs } } };
                }

                template<ExpressionSymbolType Lhs, PureSymbolType Rhs>
                inline constexpr decltype(auto) operator-(Lhs&& lhs, Rhs&& rhs) noexcept
                {
                    using RetType = LinearPolynomial<f64, f64, OriginType<Rhs>, OriginType<Lhs>>;
                    using MonomialType = typename RetType::MonomialType;
                    return RetType{ { MonomialType{ lhs }, MonomialType{ -1.0_f64, rhs } } };
                }

                template<ExpressionSymbolType Lhs, ExpressionSymbolType Rhs>
                    requires DecaySameAs<Lhs, Rhs>
                inline constexpr decltype(auto) operator+(Lhs&& lhs, Rhs&& rhs) noexcept
                {
                    using RetType = LinearPolynomial<f64, f64, PureSymbol, OriginType<Lhs>>;
                    using MonomialType = typename RetType::MonomialType;
                    return RetType{ { MonomialType{ lhs }, MonomialType{ rhs } } };
                }

                template<ExpressionSymbolType Lhs, ExpressionSymbolType Rhs>
                    requires DecaySameAs<Lhs, Rhs>
                inline constexpr decltype(auto) operator-(Lhs&& lhs, Rhs&& rhs) noexcept
                {
                    using RetType = LinearPolynomial<f64, f64, PureSymbol, OriginType<Lhs>>;
                    using MonomialType = typename RetType::MonomialType;
                    return RetType{ { MonomialType{ lhs }, MonomialType{ -1.0_f64, rhs } } };
                }
            };
        };
    };
};
