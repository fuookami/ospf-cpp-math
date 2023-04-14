#pragma once

#include <ospf/math/algebra/operator/arithmetic/pow.hpp>
#include <ospf/math/symbol/monomial/concepts.hpp>
#include <ospf/memory/reference.hpp>
#include <span>

namespace ospf
{
    inline namespace math
    {
        inline namespace symbol
        {
            template<Invariant T = f64, PureSymbolType PSym = PureSymbol, typename ESym = IExprSymbol<T, ExpressionCategory::Standard>>
                requires ExpressionSymbolTypeOf<ESym, T, ExpressionCategory::Standard>
            class StandardMonomialCell
                : public Expression<T, ExpressionCategory::Standard, StandardMonomialCell>
            {
                using Variant = std::variant<Ref<OriginType<PSym>>, Ref<OriginType<ESym>>>;
                using Impl = Expression<T, ExpressionCategory::Standard, StandardMonomialCell>;

            public:
                using ValueType = OriginType<T>;
                using PureSymbolType = OriginType<PSym>;
                using ExprSymbolType = OriginType<ESym>;

            public:
                constexpr StandardMonomialCell(const PureSymbolType& sym)
                    : _symbols({ std::make_pair(Variant{ std::in_place_index<0_uz>, Ref<PureSymbolType>{ sym } }, 1_u64) }) {}

                constexpr StandardMonomialCell(ArgCLRefType<Ref<PureSymbolType>> sym)
                    : _symbols({ std::make_pair(Variant{ std::in_place_index<0_uz>, sym }, 1_u64) }) {}

                template<typename = void>
                    requires ReferenceFaster<Ref<PureSymbolType>> && std::movable<Ref<PureSymbolType>>
                constexpr StandardMonomialCell(ArgRRefType<Ref<PureSymbolType>> sym)
                    : _symbols({ std::make_pair(Variant{ std::in_place_index<0_uz>, move<Ref<PureSymbolType>>(sym) }, 1_u64) }) {}

                constexpr StandardMonomialCell(const ExprSymbolType& sym)
                    : _symbols({ std::make_pair(Variant{ std::in_place_index<1_uz>, Ref<ExprSymbolType>{ sym } }, 1_u64) }) {}

                constexpr StandardMonomialCell(ArgCLRefType<Ref<ExprSymbolType>> sym)
                    : _symbols({ std::make_pair(Variant{ std::in_place_index<1_uz>, sym }, 1_u64) }) {}

                template<typename = void>
                    requires ReferenceFaster<Ref<ExprSymbolType>> && std::movable<Ref<ExprSymbolType>>
                constexpr StandardMonomialCell(ArgRRefType<Ref<ExprSymbolType>> sym)
                    : _symbols({ std::make_pair(Variant{ std::in_place_index<1_uz>, move<Ref<ExprSymbolType>>(sym) } , 1_u64) }) {}

                constexpr StandardMonomialCell(std::vector<std::pair<Variant, u64>> symbols)
                    : _symbols(std::move(symbols)) {}

            public:
                constexpr StandardMonomialCell(const StandardMonomialCell& ano) = default;
                constexpr StandardMonomialCell(StandardMonomialCell&& ano) noexcept = default;
                constexpr StandardMonomialCell& operator=(const StandardMonomialCell& rhs) = default;
                constexpr StandardMonomialCell& operator=(StandardMonomialCell&& rhs) noexcept = default;
                constexpr ~StandardMonomialCell(void) noexcept = default;

            public:
                inline constexpr u64 index(void) const noexcept
                {
                    return std::accumulate(_symbols.cbegin(), _symbols.cend(), 0_u64, 
                        [](const u64 lhs, const std::pair<Variant, u64>& rhs)
                        {
                            return lhs + rhs.second;
                        });
                }

                inline constexpr const std::span<const std::pair<Variant, u64>> symbols(void) const noexcept
                {
                    return _symbols;
                }

            public:
                inline constexpr StandardMonomialCell& operator*=(const PureSymbolType& sym) noexcept
                {
                    auto it = std::find_if(_symbols.begin(), _symbols.end(),
                        [&sym](const std::pair<Variant, u64>& rhs) 
                        {
                            return same_as(rhs.first, sym);
                        });
                    if (it == _symbols.cend())
                    {
                        _symbols.push_back(std::make_pair(Variant{ std::in_place_index<0_uz>, Ref<PureSymbolType>{ sym } }, 1_i64));
                    }
                    else
                    {
                        it->second += 1_uz;
                    }
                    return *this;
                }

                inline constexpr StandardMonomialCell& operator*=(ArgCLRefType<Ref<PureSymbolType>> sym) noexcept
                {
                    auto it = std::find_if(_symbols.begin(), _symbols.end(),
                        [sym](const std::pair<Variant, u64>& rhs)
                        {
                            return same_as(rhs.first, *sym);
                        });
                    if (it == _symbols.cend())
                    {
                        _symbols.push_back(std::make_pair(Variant{ std::in_place_index<0_uz>, sym }, 1_i64));
                    }
                    else
                    {
                        it->second += 1_uz;
                    }
                    return *this;
                }

                template<typename = void>
                    requires ReferenceFaster<Ref<PureSymbolType>> && std::movable<Ref<PureSymbolType>>
                inline constexpr StandardMonomialCell& operator*=(ArgRRefType<Ref<PureSymbolType>> sym) noexcept
                {
                    auto it = std::find_if(_symbols.begin(), _symbols.end(),
                        [&sym](const std::pair<Variant, u64>& rhs)
                        {
                            return same_as(rhs.first, *sym);
                        });
                    if (it == _symbols.cend())
                    {
                        _symbols.push_back(std::make_pair(Variant{ std::in_place_index<0_uz>, move<Ref<PureSymbolType>>(sym) }, 1_i64));
                    }
                    else
                    {
                        it->second += 1_uz;
                    }
                    return *this;
                }

                inline constexpr StandardMonomialCell& operator*=(const ExprSymbolType& sym) noexcept
                {
                    auto it = std::find_if(_symbols.begin(), _symbols.end(),
                        [&sym](const std::pair<Variant, u64>& rhs)
                        {
                            return same_as(rhs.first, sym);
                        });
                    if (it == _symbols.cend())
                    {
                        _symbols.push_back(std::make_pair(Variant{ std::in_place_index<0_uz>, Ref<ExprSymbolType>{ sym } }, 1_i64));
                    }
                    else
                    {
                        it->second += 1_uz;
                    }
                    return *this;
                }

                inline constexpr StandardMonomialCell& operator*=(ArgCLRefType<Ref<ExprSymbolType>> sym) noexcept
                {
                    auto it = std::find_if(_symbols.begin(), _symbols.end(),
                        [sym](const std::pair<Variant, u64>& rhs)
                        {
                            return same_as(rhs.first, *sym);
                        });
                    if (it == _symbols.cend())
                    {
                        _symbols.push_back(std::make_pair(Variant{ std::in_place_index<0_uz>, sym }, 1_i64));
                    }
                    else
                    {
                        it->second += 1_uz;
                    }
                    return *this;
                }

                template<typename = void>
                    requires ReferenceFaster<Ref<ExprSymbolType>> && std::movable<Ref<ExprSymbolType>>
                inline constexpr StandardMonomialCell& operator*=(ArgRRefType<Ref<ExprSymbolType>> sym) noexcept
                {
                    auto it = std::find_if(_symbols.begin(), _symbols.end(),
                        [&sym](const std::pair<Variant, u64>& rhs)
                        {
                            return same_as(rhs.first, *sym);
                        });
                    if (it == _symbols.cend())
                    {
                        _symbols.push_back(std::make_pair(Variant{ std::in_place_index<0_uz>, move<Ref<ExprSymbolType>>(sym) }, 1_i64));
                    }
                    else
                    {
                        it->second += 1_uz;
                    }
                    return *this;
                }

                inline constexpr StandardMonomialCell& operator*=(const StandardMonomialCell& rhs) noexcept
                {
                    _symbols.reserve(_symbols.size() + rhs._symbols.size());
                    for (const auto [symbol, index] : rhs._symbols)
                    {
                        auto it = std::find_if(_symbols.begin(), _symbols.end(),
                            [symbol](const std::pair<Variant, u64>& rhs)
                            {
                                return rhs.first == symbol;
                            });
                        if (it == _symbols.cend())
                        {
                            _symbols.push_back(std::make_pair(symbol, index));
                        }
                        else
                        {
                            it->second += index;
                        }
                    }
                    _symbols.shrink_to_fit();
                    return *this;
                }

            private:
                inline static constexpr const bool same_as(const Variant& lhs, const PureSymbolType& sym) noexcept
                {
                    return std::visit([&sym](const auto symbol) 
                        {
                            using ThisType = DecaySameAs<decltype(symbol)>;
                            if constexpr (DecaySameAs<ThisType, Ref<PureSymbolType>>)
                            {
                                return sym == symbol;
                            }
                            else
                            {
                                return false;
                            }
                        });
                }

                inline static constexpr const bool same_as(const Variant& lhs, const ExprSymbolType& sym) noexcept
                {
                    return std::visit([&sym](const auto symbol)
                        {
                            using ThisType = DecaySameAs<decltype(symbol)>;
                            if constexpr (DecaySameAs<ThisType, Ref<ExprSymbolType>>)
                            {
                                return sym == symbol;
                            }
                            else
                            {
                                return false;
                            }
                        });
                }

            OSPF_CRTP_PERMISSION :
                inline constexpr RetType<ValueType> get_value_by(const std::function<Result<ValueType>(const std::string_view)>& values) const noexcept
                {
                    auto ret = ArithmeticTrait<ValueType>::zero();
                    for (const auto [symbol, index] : _symbols)
                    {
                        OSPF_TRY_GET(value, std::visit([&values](const auto sym) -> Result<ValueType>
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
                            }, symbol));
                        ret += pow(value, static_cast<i64>(index));
                    }
                    return ret;
                }

            private:
                std::vector<std::pair<Variant, u64>> _symbols;
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

namespace std
{
    template<ospf::Invariant T, ospf::PureSymbolType PSym, typename ESym>
    struct formatter<ospf::StandardMonomialCell<T, PSym, ESym>, char>
        : public formatter<string_view, char>
    {
        template<typename FormatContext>
        inline decltype(auto) format(const ospf::StandardMonomialCell<T, PSym, ESym>& cell, FormatContext& fc) const
        {
            ostringstream sout;
            assert(!cell.symbols().empty());
            transform(cell.symbols().begin(), cell.symbols().end(), ostream_iterator<string>{ sout, " * " },
                [](const auto& symbol)
                {
                    const auto display_name = visit([](const auto sym)
                        {
                            return sym->display_name();
                        }, symbol.first);

                    assert(symbol.second >= 1_u64);
                    if (symbol.second == 1_u64)
                    {
                        return string{ display_name };
                    }
                    else
                    {
                        return format("{}^{}", display_name, symbol.second);
                    }
                });

            static const auto _formatter = formatter<string_view, char>{};
            return _formatter.format(sout.str(), fc);
        }
    };

    template<ospf::Invariant T, ospf::PureSymbolType PSym, typename ESym>
    struct formatter<ospf::StandardMonomialCell<T, PSym, ESym>, ospf::wchar>
        : public formatter<wstring_view, ospf::wchar>
    {
        template<typename FormatContext>
        inline decltype(auto) format(const ospf::StandardMonomialCell<T, PSym, ESym>& cell, FormatContext& fc) const
        {
            wostringstream sout;
            assert(!cell.symbols().empty());
            transform(cell.symbols().begin(), cell.symbols().end(), ostream_iterator<wstring, ospf::wchar>{ sout, L" * " },
                [](const auto& symbol)
                {
                    const auto display_name = boost::locale::conv::to_utf<ospf::wchar>(string{ visit([](const auto sym)
                        {
                            return sym->display_name();
                        }, symbol.first) }, locale{});

                    assert(symbol.second >= 1_u64);
                    if (symbol.second == 1_u64)
                    {
                        return display_name;
                    }
                    else
                    {
                        return format("L{}^{}", display_name, symbol.second);
                    }
                });

            static const auto _formatter = formatter<wstring_view, ospf::wchar>{};
            return _formatter.format(sout.str(), fc);
        }
    };
};
