#pragma once

#include <ospf/exception.hpp>
#include <ospf/math/symbol/monomial/concepts.hpp>
#include <ospf/memory/reference.hpp>

namespace ospf
{
    inline namespace math
    {
        inline namespace symbol
        {
            template<Invariant T = f64, PureSymbolType PSym = PureSymbol, typename ESym = IExprSymbol<T, ExpressionCategory::Quadratic>>
                requires ExpressionSymbolTypeOf<ESym, T, ExpressionCategory::Quadratic>
            class QuadraticMonomialCell
                : public Expression<T, ExpressionCategory::Quadratic, QuadraticMonomialCell<T, PSym, ESym>>
            {
                using Variant = std::variant<Ref<OriginType<PSym>>, Ref<OriginType<ESym>>>;
                using Impl = Expression<T, ExpressionCategory::Quadratic, QuadraticMonomialCell>;

            public:
                using ValueType = OriginType<T>;
                using PureSymbolType = OriginType<PSym>;
                using ExprSymbolType = OriginType<ESym>;

            public:
                constexpr QuadraticMonomialCell(const PureSymbolType& sym)
                    : _symbol1(std::in_place_index<0_uz>, Ref<PureSymbolType>{ sym }) {}

                constexpr QuadraticMonomialCell(ArgCLRefType<Ref<PureSymbolType>> sym)
                    : _symbol1(std::in_place_index<0_uz>, sym) {}

                template<typename = void>
                    requires ReferenceFaster<Ref<PureSymbolType>> && std::movable<Ref<PureSymbolType>>
                constexpr QuadraticMonomialCell(ArgRRefType<Ref<PureSymbolType>> sym)
                    : _symbol1(std::in_place_index<0_uz>, move<Ref<PureSymbolType>>(sym)) {}

                constexpr QuadraticMonomialCell(const ExprSymbolType& sym)
                    : _symbol1(std::in_place_index<1_uz>, Ref<ExprSymbolType>{ sym }) {}

                constexpr QuadraticMonomialCell(ArgCLRefType<Ref<ExprSymbolType>> sym)
                    : _symbol1(std::in_place_index<1_uz>, sym) {}

                template<typename = void>
                    requires ReferenceFaster<Ref<ExprSymbolType>> && std::movable<Ref<ExprSymbolType>>
                constexpr QuadraticMonomialCell(ArgRRefType<Ref<ExprSymbolType>> sym)
                    : _symbol1(std::in_place_index<1_uz>, move<Ref<ExprSymbolType>>(sym)) {}

            public:
                template<typename Arg>
                    requires std::constructible_from<QuadraticMonomialCell, Arg>
                constexpr QuadraticMonomialCell(Arg&& arg, const PureSymbolType& sym)
                    : QuadraticMonomialCell(std::forward<Arg>(arg)), _symbol2(Variant{ std::in_place_index<0_uz>, Ref<PureSymbolType>{ sym } }) {}

                template<typename Arg>
                    requires std::constructible_from<QuadraticMonomialCell, Arg>
                constexpr QuadraticMonomialCell(Arg&& arg, ArgCLRefType<Ref<PureSymbolType>> sym)
                    : QuadraticMonomialCell(std::forward<Arg>(arg)), _symbol2(Variant{ std::in_place_index<0_uz>, sym }) {}

                template<typename Arg>
                    requires std::constructible_from<QuadraticMonomialCell, Arg> && ReferenceFaster<Ref<PureSymbolType>>&& std::movable<Ref<PureSymbolType>>
                constexpr QuadraticMonomialCell(Arg&& arg, ArgRRefType<Ref<PureSymbolType>> sym)
                    : QuadraticMonomialCell(std::forward<Arg>(arg)), _symbol2(Variant{ std::in_place_index<0_uz>, move<Ref<PureSymbolType>>(sym) }) {}

                template<typename Arg>
                    requires std::constructible_from<QuadraticMonomialCell, Arg>
                constexpr QuadraticMonomialCell(Arg&& arg, const ExprSymbolType& sym)
                    : QuadraticMonomialCell(std::forward<Arg>(arg)), _symbol2(Variant{ std::in_place_index<1_uz>, Ref<ExprSymbolType>{ sym } }) {}

                template<typename Arg>
                    requires std::constructible_from<QuadraticMonomialCell, Arg>
                constexpr QuadraticMonomialCell(Arg&& arg, ArgCLRefType<Ref<ExprSymbolType>> sym)
                    : QuadraticMonomialCell(std::forward<Arg>(arg)), _symbol2(Variant{ std::in_place_index<1_uz>, sym }) {}

                template<typename Arg>
                    requires std::constructible_from<QuadraticMonomialCell, Arg> && ReferenceFaster<Ref<ExprSymbolType>>&& std::movable<Ref<ExprSymbolType>>
                constexpr QuadraticMonomialCell(Arg&& arg, ArgRRefType<Ref<ExprSymbolType>> sym)
                    : QuadraticMonomialCell(std::forward<Arg>(arg)), _symbol2(Variant{ std::in_place_index<1_uz>, move<Ref<ExprSymbolType>>(sym) }) {}

            public:
                constexpr QuadraticMonomialCell(const QuadraticMonomialCell& ano) = default;
                constexpr QuadraticMonomialCell(QuadraticMonomialCell&& ano) noexcept = default;
                constexpr QuadraticMonomialCell& operator=(const QuadraticMonomialCell& rhs) = default;
                constexpr QuadraticMonomialCell& operator=(QuadraticMonomialCell&& rhs) noexcept = default;
                constexpr ~QuadraticMonomialCell(void) noexcept = default;

            public:
                inline constexpr u64 index(void) const noexcept
                {
                    return _symbol2.has_value() ? 2_uz : 1_uz;
                }

                inline constexpr ArgCLRefType<Variant> symbol1(void) const noexcept
                {
                    return _symbol1;
                }

                inline constexpr ArgCLRefType<std::optional<Variant>> symbol2(void) const noexcept
                {
                    return _symbol2;
                }

            public:
                inline constexpr QuadraticMonomialCell& operator*=(const PureSymbolType& sym)
                {
                    if (_symbol2.has_value())
                    {
                        throw OSPFException{ OSPFErrCode::ApplicationError, "invalid multiply to index 2 quadratic monomial cell" };
                    }
                    _symbol2 = Variant{ std::in_place_index<0_uz>, Ref<PureSymbolType>{ sym } };
                    return *this;
                }

                inline constexpr QuadraticMonomialCell& operator*=(ArgCLRefType<Ref<PureSymbolType>> sym)
                {
                    if (_symbol2.has_value())
                    {
                        throw OSPFException{ OSPFErrCode::ApplicationError, "invalid multiply to index 2 quadratic monomial cell" };
                    }
                    _symbol2 = Variant{ std::in_place_index<0_uz>, sym };
                    return *this;
                }

                template<typename = void>
                    requires ReferenceFaster<Ref<PureSymbolType>> && std::movable<Ref<PureSymbolType>>
                inline constexpr QuadraticMonomialCell& operator*=(ArgRRefType<Ref<PureSymbolType>> sym)
                {
                    if (_symbol2.has_value())
                    {
                        throw OSPFException{ OSPFErrCode::ApplicationError, "invalid multiply to index 2 quadratic monomial cell" };
                    }
                    _symbol2 = Variant{ std::in_place_index<0_uz>, move<Ref<PureSymbolType>>(sym) };
                    return *this;
                }

                inline constexpr QuadraticMonomialCell& operator*=(const ExprSymbolType& sym)
                {
                    if (_symbol2.has_value())
                    {
                        throw OSPFException{ OSPFErrCode::ApplicationError, "invalid multiply to index 2 quadratic monomial cell" };
                    }
                    _symbol2 = Variant{ std::in_place_index<1_uz>, Ref<ExprSymbolType>{ sym } };
                    return *this;
                }

                inline constexpr QuadraticMonomialCell& operator*=(ArgCLRefType<Ref<ExprSymbolType>> sym)
                {
                    if (_symbol2.has_value())
                    {
                        throw OSPFException{ OSPFErrCode::ApplicationError, "invalid multiply to index 2 quadratic monomial cell" };
                    }
                    _symbol2 = Variant{ std::in_place_index<1_uz>, sym };
                    return *this;
                }

                template<typename = void>
                    requires ReferenceFaster<Ref<ExprSymbolType>> && std::movable<Ref<ExprSymbolType>>
                inline constexpr QuadraticMonomialCell& operator*=(ArgRRefType<Ref<ExprSymbolType>> sym)
                {
                    if (_symbol2.has_value())
                    {
                        throw OSPFException{ OSPFErrCode::ApplicationError, "invalid multiply to index 2 quadratic monomial cell" };
                    }
                    _symbol2 = Variant{ std::in_place_index<1_uz>, move<Ref<ExprSymbolType>>(sym) };
                    return *this;
                }

                inline constexpr QuadraticMonomialCell& operator*=(const QuadraticMonomialCell& rhs)
                {
                    if (_symbol2.has_value() || rhs._symbol2.has_value())
                    {
                        throw OSPFException{ OSPFErrCode::ApplicationError, "invalid multiply to index 2 quadratic monomial cell" };
                    }
                    _symbol2 = rhs._symbol1;
                    return *this;
                }

            OSPF_CRTP_PERMISSION:
                inline constexpr RetType<ValueType> get_value_by(const std::function<Result<ValueType>(const std::string_view)>& values) const noexcept
                {
                    OSPF_TRY_GET(value1, std::visit([&values](const auto sym) -> Result<ValueType>
                    {
                        using ThisType = OriginType<decltype(sym)>;
                        if constexpr (DecaySameAs<ThisType, Ref<PureSymbolType>>)
                        {
                            return values(sym->name());
                        }
                        else
                        {
                            return sym->value(values);
                        }
                    }, _symbol1));
                    if (_symbol2.has_value())
                    {
                        OSPF_TRY_GET(value2, std::visit([&values](const auto sym) -> Result<ValueType>
                            {
                                using ThisType = OriginType<decltype(sym)>;
                                if constexpr (DecaySameAs<ThisType, Ref<PureSymbolType>>)
                                {
                                    return values(sym->name());
                                }
                                else
                                {
                                    return sym->value(values);
                                }
                            }, *_symbol2));
                        return value1 * value2;
                    }
                    else
                    {
                        return value1;
                    }
                }

            private:
                Variant _symbol1;
                std::optional<Variant> _symbol2;
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

namespace std
{
    template<ospf::Invariant T, ospf::PureSymbolType PSym, typename ESym>
    struct formatter<ospf::QuadraticMonomialCell<T, PSym, ESym>, char>
        : public formatter<string_view, char>
    {
        template<typename FormatContext>
        inline decltype(auto) format(const ospf::QuadraticMonomialCell<T, PSym, ESym>& cell, FormatContext& fc) const
        {
            static const auto _formatter = formatter<string_view, char>{};
            const auto display_name1 = visit([](const auto sym)
                {
                    return sym->display_name();
                }, cell.symbol1());
            if (cell.symbol2().has_value())
            {
                const auto display_name2 = visit([](const auto sym)
                    {
                        return sym->display_name();
                    }, *cell.symbol2());
                return _formatter.format(format("{} * {}", display_name1, display_name2), fc);
            }
            else
            {
                return _formatter.format(display_name1, fc);
            }
        }
    };

    template<ospf::Invariant T, ospf::PureSymbolType PSym, typename ESym>
    struct formatter<ospf::QuadraticMonomialCell<T, PSym, ESym>, ospf::wchar>
        : public formatter<wstring_view, ospf::wchar>
    {
        template<typename FormatContext>
        inline decltype(auto) format(const ospf::QuadraticMonomialCell<T, PSym, ESym>& cell, FormatContext& fc) const
        {
            static const auto _formatter = formatter<wstring_view, ospf::wchar>{};
            const auto display_name1 = boost::locale::conv::to_utf<ospf::wchar>(string{ visit([](const auto sym)
                {
                    return sym->display_name();
                }, cell.symbol1()) }, locale{});
            if (cell.symbol2().has_value())
            {
                const auto display_name2 = boost::locale::conv::to_utf<ospf::wchar>(string{ visit([](const auto sym)
                    {
                        return sym->display_name();
                    }, *cell.symbol2()) }, locale{});
                return _formatter.format(format("L{} * {}", display_name1, display_name2), fc);
            }
            else
            {
                return _formatter.format(display_name1, fc);
            }
        }
    };
};
