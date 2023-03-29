#pragma once

#include <ospf/functional/result.hpp>
#include <ospf/functional/value_or_reference.hpp>
#include <ospf/math/algebra/concepts/real_number.hpp>

namespace ospf
{
    inline namespace math
    {
        inline namespace symbol
        {
            template<Invariant T, typename Self>
            class Expression
            {
                OSPF_CRTP_IMPL;

            public:
                using ValueType = OriginType<T>;

            public:
                constexpr Expression(void) = default;
                constexpr Expression(const Expression& ano) = default;
                constexpr Expression(Expression&& ano) noexcept = default;
                constexpr Expression& operator=(const Expression& rhs) = default;
                constexpr Expression& operator=(Expression&& rhs) noexcept = default;
                constexpr ~Expression(void) noexcept = default;

            public:
                inline constexpr Result<ValueType> value(const StringHashMap<std::string_view, ValueType>& values) const noexcept
                {
                    return Trait::get_value(self(), values());
                }

            private:
                struct Trait : public Self
                {
                    inline static constexpr Result<ValueType> get_value(const Self& self, const StringHashMap<std::string_view, ValueType>& values) noexcept
                    {
                        static const auto get_impl = &Self::OSPF_CRTP_FUNCTION(get_value_by);
                        return (self.*get_impl)();
                    }
                };
            };

            template<typename V, typename T>
            concept ExpressionType = Invariant<V> && std::derived_from<OriginType<T>, Expression<V, T>>;

            template<typename V, typename... Ts>
            struct IsAllExpressionType;

            template<typename V, typename T>
            struct IsAllExpressionType<V, T>
            {
                static constexpr const bool value = ExpressionType<V, T>;
            };

            template<typename V, typename T, typename... Ts>
            struct IsAllExpressionType<V, T, Ts...>
            {
                static constexpr const bool value = ExpressionType<V, T> && IsAllExpressionType<V, Ts...>::value;
            };

            template<typename V, typename... Ts>
            inline static constexpr const bool is_all_expression_type = IsAllExpressionType<V, Ts...>::value;

            template<typename V, typename... Ts>
            concept AllExpressionType = is_all_expression_type<V, Ts...>;
        };
    };
};
