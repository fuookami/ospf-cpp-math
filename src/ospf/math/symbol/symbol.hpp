#pragma once

#include <ospf/math/algebra/concepts/real_number.hpp>
#include <boost/locale.hpp>

namespace ospf
{
    inline namespace math
    {
        inline namespace symbol
        {
            template<RealNumber T = f64>
            class Symbol
            {
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
                constexpr virtual ~Symbol(void) noexcept = default;

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

            private:
                std::string _name;
                std::optional<std::string> _display_name;
            };

            extern template class Symbol<f64>;
        };
    };
};

namespace std
{
    template<ospf::RealNumber T, ospf::CharType CharT>
    struct formatter<ospf::Symbol<T>, CharT>
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

    template<ospf::RealNumber T>
    struct formatter<ospf::Symbol<T>, char>
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
