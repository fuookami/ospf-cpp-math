#pragma once

#include <ospf/math/symbol/expression.hpp>
#include <boost/locale.hpp>

namespace ospf
{
    inline namespace math
    {
        inline namespace symbol
        {
            template<Invariant T, typename Self>
            class Symbol
                : public Expression<T, Self>
            {
                OSPF_CRTP_IMPL;

            public:
                using ValueType = OriginType<T>;

            public:
                constexpr Symbol(std::string name)
                    : _name(std::move(name)) {}
                
                constexpr Symbol(std::string name, std::string display_name)
                    : _name(std::move(name)), _display_name(std::move(display_name)) {}

            public:
                constexpr Symbol(const Symbol& ano) = default;
                constexpr Symbol(Symbol&& ano) noexcept = default;
                constexpr Symbol& operator=(const Symbol& rhs) = default;
                constexpr Symbol& operator=(Symbol&& rhs) noexcept = default;
                constexpr ~Symbol(void) noexcept = default;

            public:
                inline constexpr std::string_view name(void) const noexcept
                {
                    return _name;
                }

                inline constexpr std::string_view display_name(void) const noexcept
                {
                    if (_display_name.has_value())
                    {
                        return *_display_name;
                    }
                    else
                    {
                        return _name;
                    }
                }

                inline void set_display_name(std::string new_display_name) noexcept
                {
                    _display_name = std::move(new_display_name);
                }

            public:
                inline constexpr const bool pure(void) const noexcept
                {
                    return Trait::is_pure(self());
                }

            private:
                struct Trait : public Self
                {
                    inline static constexpr const bool is_pure(const Self& self) noexcept
                    {
                        static const auto impl = &Self::OSPF_CRTP_FUNCTION(is_pure);
                        return (self.*impl)();
                    }
                };

            private:
                std::string _name;
                std::optional<std::string> _display_name;
            };

            template<typename V, typename T>
            concept SymbolType = Invariant<V> && std::derived_from<OriginType<T>, Symbol<V, T>>;

            template<typename V, typename... Ts>
            struct IsAllSymbolType;

            template<typename V, typename T>
            struct IsAllSymbolType<V, T>
            {
                static constexpr const bool value = SymbolType<V, T>;
            };

            template<typename V, typename T, typename... Ts>
            struct IsAllSymbolType<V, T, Ts...>
            {
                static constexpr const bool value = SymbolType<V, T> && IsAllSymbolType<V, Ts...>::value;
            };

            template<typename V, typename... Ts>
            static constexpr const bool is_all_symbol_type = IsAllSymbolType<V, Ts...>::value;

            template<typename V, typename... Ts>
            concept AllSymbolType = is_all_symbol_type<V, Ts...>;
        };
    };
};

namespace std
{
    template<ospf::Invariant T, typename Self, ospf::CharType CharT>
    struct formatter<ospf::Symbol<T, Self>, CharT>
        : public formatter<basic_string_view<CharT>, CharT>
    {
        template<typename FormatContext>
        inline decltype(auto) format(const ospf::Symbol<T>& symbol, FormatContext& fc)
        {
            static const auto _formatter = formatter<basic_string_view<CharT>, CharT>{};
            const auto display_name = boost::locale::conv::to_utf<CharT>(string{ symbol.display_name() }, locale{});
            return _formatter.format(display_name, fc);
        }
    };

    template<ospf::Invariant T, typename Self>
    struct formatter<ospf::Symbol<T, Self>, char>
        : public formatter<string_view, char>
    {
        template<typename FormatContext>
        inline decltype(auto) format(const ospf::Symbol<T>& symbol, FormatContext& fc)
        {
            static const auto _formatter = formatter<string_view, char>{};
            return _formatter.format(symbol.display_name(), fc);
        }
    };
};
