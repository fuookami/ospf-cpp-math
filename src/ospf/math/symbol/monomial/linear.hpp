#pragma once

#include <ospf/math/symbol/monomial/concepts.hpp>
#include <ospf/memory/reference.hpp>

namespace ospf
{
    inline namespace math
    {
        inline namespace symbol
        {
            template<Invariant T = f64, Invariant ST = T, PureSymbolType PSym = PureSymbol, typename ESym = IExprSymbol<T, ST, ExpressionCategory::Linear>>
                requires ExpressionSymbolTypeOf<ESym, T, ST, ExpressionCategory::Linear>
            class LinearMonomialCell
                : public Expression<T, ST, ExpressionCategory::Linear, LinearMonomialCell<T, PSym, ESym>>
            {
                using Variant = std::variant<Ref<OriginType<PSym>>, Ref<OriginType<ESym>>>;
                using Impl = Expression<T, ST, ExpressionCategory::Linear, LinearMonomialCell>;

            public:
                using ValueType = OriginType<T>;
                using SymbolValueType = OriginType<ST>;
                using TransferType = Extractor<SymbolValueType, ValueType>;
                using PureSymbolType = OriginType<PSym>;
                using ExprSymbolType = OriginType<ESym>;

            public:
                template<typename = void>
                    requires DecaySameAsOrConvertibleTo<SymbolValueType, ValueType>
                constexpr LinearMonomialCell(const PureSymbolType& sym)
                    : _symbol(std::in_place_index<0_uz>, Ref<PureSymbolType>{ sym }) {}

                template<typename = void>
                    requires DecaySameAsOrConvertibleTo<SymbolValueType, ValueType>
                constexpr LinearMonomialCell(ArgCLRefType<Ref<PureSymbolType>> sym)
                    : _symbol(std::in_place_index<0_uz>, sym) {}

                template<typename = void>
                    requires DecaySameAsOrConvertibleTo<SymbolValueType, ValueType> && ReferenceFaster<Ref<PureSymbolType>> && std::movable<Ref<PureSymbolType>>
                constexpr LinearMonomialCell(ArgRRefType<Ref<PureSymbolType>> sym)
                    : _symbol(std::in_place_index<0_uz>, move<Ref<PureSymbolType>>(sym)) {}

                constexpr LinearMonomialCell(const PureSymbolType& sym, TransferType transfer)
                    : _symbol(std::in_place_index<0_uz>, Ref<PureSymbolType>{ sym }), _transfer(std::move(transfer)) {}

                constexpr LinearMonomialCell(ArgCLRefType<Ref<PureSymbolType>> sym, TransferType transfer)
                    : _symbol(std::in_place_index<0_uz>, sym), _transfer(std::move(transfer)) {}

                template<typename = void>
                    requires ReferenceFaster<Ref<PureSymbolType>> && std::movable<Ref<PureSymbolType>>
                constexpr LinearMonomialCell(ArgRRefType<Ref<PureSymbolType>> sym, TransferType transfer)
                    : _symbol(std::in_place_index<0_uz>, move<Ref<PureSymbolType>>(sym)), _transfer(std::move(transfer)) {}

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
                inline constexpr RetType<ValueType> OSPF_CRTP_FUNCTION(get_value_by)(const std::function<Result<SymbolValueType>(const std::string_view)>& values) const noexcept
                {
                    return std::visit([this, &values](const auto sym) -> Result<ValueType>
                        {
                            using ThisType = OriginType<decltype(sym)>;
                            if constexpr (DecaySameAs<ThisType, Ref<PureSymbolType>)
                            {
                                if (_transfer.has_value())
                                {
                                    return (*_transfer)(values(sym->name()));
                                }
                                else
                                {
                                    if constexpr (DecaySameAs<SymbolValueType, ValueType>)
                                    {
                                        return values(sym->name());
                                    }
                                    else if (std::convertible_to<SymbolValueType, ValueType>)
                                    {
                                        return static_cast<SymbolValueType>(values(sym->name()));
                                    }
                                    else
                                    {
                                        return OSPFError{ OSPFErrCode::ApplicationFail, std::format("lost transfer for {} to {}", TypeInfo<SymbolValueType>::name(), TypeInfo<ValueType>::name()) };
                                    }
                                }
                            }
                            else
                            {
                                return sym->value(values);
                            }
                        }, _symbol);
                }

            private:
                Variant _symbol;
                std::optional<TransferType> _transfer;
            };

            template<Invariant T = f64, Invariant ST = T, PureSymbolType PSym = PureSymbol, typename ESym = IExprSymbol<T, ST, ExpressionCategory::Linear>>
            using LinearMonomial = Monomial<T, ST, ExpressionCategory::Linear, LinearMonomialCell<T, ST, PSym, ESym>>;

            namespace linear
            {
                template<Invariant T, PureSymbolType PSym>
                inline constexpr LinearMonomial operator*(const T& lhs, const PSym& rhs) noexcept
                {
                    return LinearMonomial{ static_cast<f64>(lhs), LinearMonomialCell{ rhs } };
                }

                template<Invariant T, typename ESym>
                    requires ExpressionSymbolTypeOf<ESym, f64, f64, ExpressionCategory::Linear>
                inline constexpr LinearMonomial operator*(const T& lhs, const ESym& rhs) noexcept
                {
                    return LinearMonomial{ static_cast<f64>(lhs), LinearMonomialCell{ rhs } };
                }

                template<Invariant T, PureSymbolType PSym>
                inline constexpr LinearMonomial operator*(const PSym& lhs, const T& rhs) noexcept
                {
                    return LinearMonomial{ static_cast<f64>(rhs), LinearMonomialCell{ lhs } };
                }

                template<Invariant T, typename ESym>
                    requires ExpressionSymbolTypeOf<ESym, f64, f64, ExpressionCategory::Linear>
                inline constexpr LinearMonomial operator*(const ESym& lhs, const T& rhs) noexcept
                {
                    return LinearMonomial{ static_cast<f64>(rhs), LinearMonomialCell{ lhs } };
                }

                template<Invariant T, PureSymbolType PSym>
                inline constexpr LinearMonomial operator/(const PSym& lhs, const T& rhs) noexcept
                {
                    return LinearMonomial{ reciprocal(static_cast<f64>(rhs)), LinearMonomialCell{ lhs } };
                }

                template<Invariant T, typename ESym>
                    requires ExpressionSymbolTypeOf<ESym, f64, f64, ExpressionCategory::Linear>
                inline constexpr LinearMonomial operator/(const ESym& lhs, const T& rhs) noexcept
                {
                    return LinearMonomial{ reciprocal(static_cast<f64>(rhs)), LinearMonomialCell{ lhs } };
                }
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
