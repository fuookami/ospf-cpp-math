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
                requires ExpressionSymbolTypeOf<ESym, T, ExpressionCategory::Linear>
            class LinearMonomialCell
                : public Expression<T, ExpressionCategory::Linear, LinearMonomialCell<T, PSym, ESym>>
            {
                using Variant = std::variant<Ref<OriginType<PSym>>, Ref<OriginType<ESym>>>;
                using Impl = Expression<T, ExpressionCategory::Linear, LinearMonomialCell>;

            public:
                using ValueType = OriginType<T>;
                using PureSymbolType = OriginType<PSym>;
                using ExprSymbolType = OriginType<ESym>;

            public:
                constexpr LinearMonomialCell(const PureSymbolType& sym)
                    : _symbol(std::in_place_index<0_uz>, Ref<PureSymbolType>{ sym }) {}

                constexpr LinearMonomialCell(ArgCLRefType<Ref<PureSymbolType>> sym)
                    : _symbol(std::in_place_index<0_uz>, sym) {}

                template<typename = void>
                    requires ReferenceFaster<Ref<PureSymbolType>> && std::movable<Ref<PureSymbolType>>
                constexpr LinearMonomialCell(ArgRRefType<Ref<PureSymbolType>> sym)
                    : _symbol(std::in_place_index<0_uz>, move<Ref<PureSymbolType>>(sym)) {}

                constexpr LinearMonomialCell(const ExprSymbolType& sym)
                    : _symbol(std::in_place_index<1_uz>, Ref<ExprSymbolType>{ sym }) {}

                constexpr LinearMonomialCell(ArgCLRefType<Ref<ExprSymbolType>> sym)
                    : _symbol(std::in_place_index<1_uz>, sym) {}

                template<typename = void>
                    requires ReferenceFaster<Ref<ExprSymbolType>> && std::movable<Ref<ExprSymbolType>>
                constexpr LinearMonomialCell(ArgRRefType<Ref<ExprSymbolType>> sym)
                    : _symbol(std::in_place_index<1_uz>, move<Ref<ExprSymbolType>>(sym)) {}

            public:
                constexpr LinearMonomialCell(const LinearMonomialCell& ano) = default;
                constexpr LinearMonomialCell(LinearMonomialCell&& ano) noexcept = default;
                constexpr LinearMonomialCell& operator=(const LinearMonomialCell& rhs) = default;
                constexpr LinearMonomialCell& operator=(LinearMonomialCell&& rhs) noexcept = default;
                constexpr ~LinearMonomialCell(void) noexcept = default;

            public:
                inline constexpr ArgCLRefType<Variant> symbol(void) const noexcept
                {
                    return _symbol;
                }

            OSPF_CRTP_PERMISSION:
                inline constexpr RetType<ValueType> get_value_by(const std::function<Result<ValueType>(const std::string_view)>& values) const noexcept
                {
                    return std::visit([&values](const auto sym) -> Result<ValueType>
                        {
                            using ThisType = OriginType<decltype(sym)>;
                            if constexpr (DecaySameAs<ThisType, Ref<PureSymbolType>)
                            {
                                return values(sym->name());
                            }
                            else
                            {
                                return sym->value(values);
                            }
                        }, _symbol);
                }

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

namespace std
{
    template<ospf::Invariant T, ospf::PureSymbolType PSym, typename ESym, ospf::CharType CharT>
    struct formatter<ospf::LinearMonomialCell<T, PSym, ESym>, CharT>
        : public formatter<basic_string_view<CharT>, CharT>
    {
        template<typename FormatContext>
        inline decltype(auto) format(const ospf::LinearMonomialCell<T, PSym, ESym>& cell, FormatContext& fc) const
        {
            static const auto _formatter = formatter<basic_string_view<CharT>, CharT>{};
            const auto display_name = boost::locale::conv::to_utf<CharT>(string{ std::visit([](const auto sym)
                {
                    return sym->display_name();
                }, cell.symbol()) }, locale{});
            return _formatter.format(display_name, fc);
        }
    };

    template<ospf::Invariant T, ospf::PureSymbolType PSym, typename ESym>
    struct formatter<ospf::LinearMonomialCell<T, PSym, ESym>, char>
        : public formatter<string_view, char>
    {
        template<typename FormatContext>
        inline decltype(auto) format(const ospf::LinearMonomialCell<T, PSym, ESym>& cell, FormatContext& fc) const
        {
            static const auto _formatter = formatter<string_view, char>{};
            const auto display_name = std::visit([](const auto sym)
                {
                    return sym->display_name();
                }, cell.symbol());
            return _formatter.format(display_name, fc);
        }
    };
};
