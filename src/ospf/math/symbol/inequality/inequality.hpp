#pragma once

#include <ospf/math/symbol/expression.hpp>
#include <ospf/math/symbol/inequality/sign.hpp>

namespace ospf
{
    inline namespace math
    {
        inline namespace symbol
        {
            template<ExpressionType Lhs, ExpressionType Rhs = Lhs>
                requires DecaySameAsOrConvertibleTo<typename Lhs::SymbolValueType, typename Rhs::SymbolValueType>
            class Inequality
                : public Expression<bool, typename Lhs::SymbolValueType, std::max(Lhs::category, Rhs::category), Inequality<Lhs, Rhs>>
            {
            public:
                using LhsType = OriginType<Lhs>;
                using LhsValueType = typename LhsType::ValueType;
                using RhsType = OriginType<Rhs>;
                using RhsValueType = typename RhsType::ValueType;

                using ValueType = bool;
                using SymbolValueType = typename Lhs::SymbolValueType;

            public:
                constexpr Inequality(ArgCLRefType<LhsType> lhs, ArgCLRefType<RhsType> rhs, const InequalitySign sign)
                    : _lhs(lhs), _rhs(rhs), _sign(sign) {}

                template<typename = void>
                    requires ReferenceFaster<LhsType> && std::movable<LhsType>
                constexpr Inequality(ArgRRefType<LhsType> lhs, ArgCLRefType<RhsType> rhs, const InequalitySign sign)
                    : _lhs(move<LhsType>(lhs)), _rhs(rhs), _sign(sign) {}

                template<typename = void>
                    requires ReferenceFaster<RhsType> && std::movable<RhsType>
                constexpr Inequality(ArgCLRefType<LhsType> lhs, ArgRRefType<RhsType> rhs, const InequalitySign sign)
                    : _lhs(lhs), _rhs(move<RhsType>(rhs)), _sign(sign) {}

                template<typename = void>
                    requires ReferenceFaster<LhsType> && std::movable<LhsType> &&
                        ReferenceFaster<RhsType> && std::movable<RhsType>
                            constexpr Inequality(ArgRRefType<RhsType> lhs, ArgRRefType<RhsType> rhs, const InequalitySign sign)
                    : _lhs(move<LhsType>(lhs)), _rhs(move<RhsType>(rhs)), _sign(sign) {}

            public:
                constexpr Inequality(const Inequality& ano) = default;
                constexpr Inequality(Inequality&& ano) noexcept = default;
                constexpr Inequality& operator=(const Inequality& rhs) = default;
                constexpr Inequality& operator=(Inequality&& rhs) noexcept = default;
                constexpr ~Inequality(void) noexcept = default;

            public:
                inline constexpr ArgCLRefType<LhsType> lhs(void) const noexcept
                {
                    return _lhs;
                }

                inline constexpr ArgCLRefType<RhsType> rhs(void) const noexcept
                {
                    return _rhs;
                }

                inline constexpr const InequalitySign sign(void) const noexcept
                {
                    return _sign;
                }

                inline constexpr decltype(auto) comparison_operator(void) const noexcept
                {
                    using ValueType = OriginType<decltype(std::declval<LhsValueType>() - std::declval<RhsValueType>())>;
                    return comparison_operator_of<ValueType>(_sign);
                }

            OSPF_CRTP_PERMISSION:
                inline constexpr Result<bool> OSPF_CRTP_FUNCTION(get_value_by)(const std::function<Result<SymbolValueType>(const std::string_view)>& values) const noexcept
                {
                    OSPF_TRY_GET(lhs_value, _lhs.value(values));
                    OSPF_TRY_GET(rhs_value, _rhs.value(values));

                    const auto op = comparison_operator();
                    return op(lhs_value, rhs_value);
                }

            private:
                LhsType _lhs;
                RhsType _rhs;
                InequalitySign _sign;
            };

            // operators
        };
    };
};

namespace std
{
    template<ospf::ExpressionType Lhs, ospf::ExpressionType Rhs>
    struct formatter<ospf::Inequality<Lhs, Rhs>, char>
        : public formatter<string_view, char>
    {
        template<typename FormatContext>
        inline decltype(auto) format(const ospf::Inequality<Lhs, Rhs>& ineq, FormatContext& fc) const
        {
            static const auto _formatter = formatter<string_view, char>{};
            return _formatter(std::format("{} {} {}", ineq.lhs(), ospf::to_string(ineq.sign()), ineq.rhs()), fc);
        }
    };

    template<ospf::ExpressionType Lhs, ospf::ExpressionType Rhs>
    struct formatter<ospf::Inequality<Lhs, Rhs>, ospf::wchar>
        : public formatter<wstring_view, ospf::wchar>
    {
        template<typename FormatContext>
        inline decltype(auto) format(const ospf::Inequality<Lhs, Rhs>& ineq, FormatContext& fc) const
        {
            static const auto _formatter = formatter<wstring_view, ospf::wchar>{};
            return _formatter(std::format("L{} {} {}", ineq.lhs(), ospf::to_string<ospf::InequalitySign, ospf::wchar>(ineq.sign()), ineq.rhs()), fc);
        }
    };
};
