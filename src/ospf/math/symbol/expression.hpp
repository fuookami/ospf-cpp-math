#pragma once

#include <ospf/functional/result.hpp>
#include <ospf/functional/value_or_reference.hpp>
#include <ospf/math/algebra/concepts/real_number.hpp>
#include <ospf/math/symbol/category.hpp>

namespace ospf
{
    inline namespace math
    {
        inline namespace symbol
        {
            template<Invariant T, ExpressionCategory cat, typename Self>
            class Expression
            {
                OSPF_CRTP_IMPL;

            public:
                using ValueType = OriginType<T>;
                static constexpr const ExpressionCategory category = cat;

            public:
                constexpr Expression(void) = default;
                constexpr Expression(const Expression& ano) = default;
                constexpr Expression(Expression&& ano) noexcept = default;
                constexpr Expression& operator=(const Expression& rhs) = default;
                constexpr Expression& operator=(Expression&& rhs) noexcept = default;
                constexpr ~Expression(void) noexcept = default;

            public:
                inline constexpr Result<ValueType> value(const std::function<Result<ValueType>(const std::string_view)>& values) const noexcept
                {
                    return Trait::get_value(self(), values);
                }

                inline constexpr Result<ValueType> value(const StringHashMap<std::string_view, ValueType>& values) const noexcept
                {
                    return value([&values](const std::string_view symbol) -> Result<ValueType> 
                        {
                            const auto it = values.find(symbol);
                            if (it == values.cend())
                            {
                                return OSPFError{ OSPFErrCode::ApplicationFail, std::format("value of symbol \"{}\" unmatched", symbol) };
                            }
                            return it->second;
                        });
                }

                template<Invariant V>
                    requires DecayNotSameAs<ValueType, V>
                        && std::convertible_to<ValueType, V>
                        && std::convertible_to<V, ValueType>
                inline constexpr Result<V> value(const StringHashMap<std::string_view, V>& values) const noexcept
                {
                    return static_cast<V>(value([&values](const std::string_view symbol) -> Result<ValueType>
                        {
                            const auto it = values.find(symbol);
                            if (it == values.cend())
                            {
                                return OSPFError{ OSPFErrCode::ApplicationFail, std::format("value of symbol \"{}\" unmatched", symbol) };
                            }
                            return static_cast<ValueType>(it->second);
                        }));
                }

                template<typename F>
                    requires DecaySameAsOrConvertibleTo<std::invoke_result_t<F, std::string_view>, ValueType>
                inline constexpr Result<ValueType> value(const F& values) const noexcept
                {
                    return value([&values](const std::string_view symbol) -> Result<ValueType>
                        {
                            return values(symbol);
                        });
                }

                template<Invariant V, typename F>
                    requires DecayNotSameAs<ValueType, V> 
                        && DecaySameAsOrConvertibleTo<std::invoke_result_t<F, std::string_view>, V>
                        && std::convertible_to<ValueType, V> 
                        && std::convertible_to<V, ValueType>
                inline constexpr Result<V> value(const F& values) const noexcept
                {
                    return static_cast<V>(value([&values](const std::string_view symbol) -> Result<ValueType>
                        {
                            return static_cast<ValueType>(values(symbol));
                        }));
                }


            private:
                struct Trait : public Self
                {
                    inline static constexpr Result<ValueType> get_value(const Self& self, const std::function<Result<ValueType>(const std::string_view)>& values) noexcept
                    {
                        static const auto get_impl = &Self::OSPF_CRTP_FUNCTION(get_value_by);
                        return (self.*get_impl)(values);
                    }
                };
            };

            template<typename T>
            concept ExpressionType = Invariant<typename T::ValueType>
                && requires (const T& expression, const std::function<Result<typename T::ValueType>(const std::string_view)>& values)
                {
                    { T::category } -> DecaySameAs<ExpressionCategory>;
                    { expression.value(values) } -> DecaySameAs<typename T::ValueType>;
                };

            template<typename... Ts>
            struct IsAllExpressionType;

            template<typename T>
            struct IsAllExpressionType<T>
            {
                static constexpr const bool value = ExpressionType<T>;
            };

            template<typename T, typename... Ts>
            struct IsAllExpressionType<T, Ts...>
            {
                static constexpr const bool value = ExpressionType<T> && IsAllExpressionType<Ts...>::value;
            };

            template<typename... Ts>
            inline static constexpr const bool is_all_expression_type = IsAllExpressionType<Ts...>::value;

            template<typename... Ts>
            concept AllExpressionType = is_all_expression_type<Ts...>;

            template<typename T, typename V, ExpressionCategory cat>
            concept ExpressionTypeOf = Invariant<typename T::ValueType> 
                && Invariant<V> 
                && DecaySameAsOrConvertibleTo<typename T::ValueType, V>
                && T::category == cat
                && requires (const T& expression, const std::function<Result<V>(const std::string_view)>& values)
                {
                    { expression.value(values) } -> DecaySameAs<V>;
                };

            template<typename V, ExpressionCategory cat, typename... Ts>
            struct IsAllExpressionTypeOf;

            template<typename V, ExpressionCategory cat, typename T>
            struct IsAllExpressionTypeOf<V, cat, T>
            {
                static constexpr const bool value = ExpressionTypeOf<T, V, cat>;
            };

            template<typename V, ExpressionCategory cat, typename T, typename... Ts>
            struct IsAllExpressionTypeOf<V, cat, T, Ts...>
            {
                static constexpr const bool value = ExpressionTypeOf<T, V, cat> && IsAllExpressionTypeOf<V, cat, Ts...>::value;
            };

            template<typename V, ExpressionCategory cat, typename... Ts>
            inline static constexpr const bool is_all_expression_type_of = IsAllExpressionTypeOf<V, cat, Ts...>::value;

            template<typename V, ExpressionCategory cat, typename... Ts>
            concept AllExpressionTypeOf = is_all_expression_type_of<V, cat, Ts...>;
        };
    };
};
