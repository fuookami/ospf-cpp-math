#pragma once

#include <ospf/math/symbol/symbol.hpp>
#include <ospf/math/algebra/operator/comparison/equal.hpp>
#include <ospf/math/algebra/operator/arithmetic/neg.hpp>

namespace ospf
{
    inline namespace math
    {
        inline namespace symbol
        {
            template<Invariant T, ExpressionCategory cat, typename Cell>
                requires ExpressionTypeOf<T, cat, Cell>
            class Monomial
                : public Expression<T, cat, Monomial<T, cat, Cell>>
            {
            public:
                using ValueType = OriginType<T>;
                using CellType = OriginType<Cell>;

            public:
                constexpr Monomial(CellType cell)
                    : _coefficient(ArithmeticTrait<ValueType>::one()), _cell(std::move(cell)) {}

                constexpr Monomial(ArgCLRefType<ValueType> coefficient, CellType cell)
                    : _coefficient(coefficient), _cell(std::move(cell)) {}

                template<typename = void>
                    requires ReferenceFaster<ValueType> && std::movable<ValueType>
                constexpr Monomial(ArgRRefType<ValueType> coefficient, CellType cell)
                    : _coefficient(move<ValueType>(coefficient)), _cell(std::move(cell)) {}

            public:
                constexpr Monomial(const Monomial& ano) = default;
                constexpr Monomial(Monomial&& ano) noexcept = default;
                constexpr Monomial& operator=(const Monomial& rhs) = default;
                constexpr Monomial& operator=(Monomial&& rhs) noexcept = default;
                constexpr ~Monomial(void) noexcept = default;

            public:
                inline constexpr ArgCLRefType<ValueType> coefficient(void) const noexcept
                {
                    return _coefficient;
                }

                inline constexpr CLRefType<CellType> cell(void) const noexcept
                {
                    return _cell;
                }

            public:
                inline constexpr Monomial& operator*=(ArgCLRefType<ValueType> rhs) noexcept
                {
                    _coefficient *= rhs;
                    return *this;
                }

                inline constexpr Monomial& operator/=(ArgCLRefType<ValueType> rhs) noexcept
                {
                    _coefficient /= rhs;
                    return *this;
                }

            OSPF_CRTP_PERMISSION:
                inline constexpr RetType<ValueType> get_value_by(const std::function<Result<ValueType>(const std::string_view)>& values) const noexcept
                {
                    return _coefficient * _cell.value(values);
                }

            private:
                ValueType _coefficient;
                CellType _cell;
            };

            template<typename T>
            concept MonomialType = ExpressionType<T>
                && requires (const T& monomial)
                {
                    { T::coefficient() } -> DecaySameAs<typename T::ValueType>;
                    { T::cell() } -> ExpressionType;
                };

            template<typename... Ts>
            struct IsAllMonomialType;

            template<typename T>
            struct IsAllMonomialType<T>
            {
                static constexpr const bool value = MonomialType<T>;
            };

            template<typename T, typename... Ts>
            struct IsAllMonomialType<T, Ts...>
            {
                static constexpr const bool value = MonomialType<T> && IsAllMonomialType<Ts...>::value;
            };

            template<typename... Ts>
            static constexpr const bool is_all_monomial_type = IsAllMonomialType<Ts...>::value;

            template<typename... Ts>
            concept AllMonomialType = is_all_monomial_type<Ts...>;

            template<typename V, ExpressionCategory cat, typename T>
            concept MonomialTypeOf = ExpressionTypeOf<V, cat, T>
                && requires (const T& monomial)
                {
                    { T::coefficient() } -> DecaySameAs<typename T::ValueType>;
                    { T::cell() } -> ExpressionType;
                };

            template<typename V, ExpressionCategory cat, typename... Ts>
            struct IsAllMonomialTypeOf;

            template<typename V, ExpressionCategory cat, typename T>
            struct IsAllMonomialTypeOf<V, cat, T>
            {
                static constexpr const bool value = MonomialTypeOf<V, cat, T>
            };

            template<typename V, ExpressionCategory cat, typename T, typename... Ts>
            struct IsAllMonomialTypeOf<V, cat, T, Ts...>
            {
                static constexpr const bool value = MonomialTypeOf<V, cat, T> && IsAllMonomialTypeOf<V, cat, Ts...>;
            };

            template<typename V, ExpressionCategory cat, typename... Ts>
            static constexpr const bool is_all_monomial_type_of = IsAllMonomialTypeOf<V, cat, Ts...>::value;

            template<typename V, ExpressionCategory cat, typename... Ts>
            concept AllMonomialTypeOf = is_all_monomial_type_of<V, cat, Ts...>;
        };
    };
};

namespace std
{
    template<ospf::Invariant T, ospf::ExpressionCategory cat, typename Cell>
    struct formatter<ospf::Monomial<T, cat, Cell>>
        : public formatter<string_view, char>
    {
        template<typename FormatContext>
        inline decltype(auto) format(const ospf::Monomial<T, cat, Cell>& monomial, FormatContext& fc) const
        {
            static const auto _formatter = formatter<string_view, char>{};
            static const ospf::Equal<T> eq{};
            if (eq(monomial.coefficient(), ospf::ArithmeticTrait<T>::zero()))
            {
                return _formatter.format("0", fc);
            }
            else if (eq(monomial.coefficient(), ospf::ArithmeticTrait<T>::one()))
            {
                return _formatter.format(std::format("{}", monomial.cell()), fc);
            }
            else
            {
                if constexpr (ospf::Signed<T> && ospf::Neg<T>)
                {
                    if (eq(monomial.coefficient(), -ospf::ArithmeticTrait<T>::one()))
                    {
                        return _formatter.format(std::format("-{}", monomial.cell()), fc);
                    }
                    else
                    {
                        return _formatter.format(std::format("{} * {}", monomial.coefficient(), monomial.cell()), fc);
                    }
                }
                else
                {
                    return _formatter.format(std::format("{} * {}", monomial.coefficient(), monomial.cell()), fc);
                }
            }
        }
    };

    template<ospf::Invariant T, ospf::ExpressionCategory cat, typename Cell>
    struct formatter<ospf::Monomial<T, cat, Cell>>
        : public formatter<wstring_view, ospf::wchar>
    {
        template<typename FormatContext>
        inline decltype(auto) format(const ospf::Monomial<T, cat, Cell, Self>& monomial, FormatContext& fc) const
        {
            static const auto _formatter = formatter<wstring_view, ospf::wchar>{};
            static const ospf::Equal<T> eq{};
            if (eq(monomial.coefficient(), ospf::ArithmeticTrait<T>::zero()))
            {
                return _formatter.format(L"0", fc);
            }
            else if (eq(monomial.coefficient(), ospf::ArithmeticTrait<T>::one()))
            {
                return _formatter.format(std::format(L"{}", monomial.cell()), fc);
            }
            else
            {
                if constexpr (ospf::Signed<T> && ospf::Neg<T>)
                {
                    if (eq(monomial.coefficient(), -ospf::ArithmeticTrait<T>::one()))
                    {
                        return _formatter.format(std::format(L"-{}", monomial.cell()), fc);
                    }
                    else
                    {
                        return _formatter.format(std::format(L"{} * {}", monomial.coefficient(), monomial.cell()), fc);
                    }
                }
                else
                {
                    return _formatter.format(std::format(L"{} * {}", monomial.coefficient(), monomial.cell()), fc);
                }
            }
        }
    };
};
