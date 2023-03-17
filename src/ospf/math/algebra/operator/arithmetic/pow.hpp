#pragma once

#include <ospf/concepts/base.hpp>
#include <ospf/math/algebra/concepts/field.hpp>
#include <ospf/math/algebra/concepts/variant.hpp>
#include <ospf/math/algebra/operator/arithmetic/reciprocal.hpp>

namespace ospf
{
    inline namespace math
    {
        inline namespace algebra
        {
            inline namespace arithmetic_operator
            {
                template<Invariant T>
                struct PowOperator
                {
                    template<i64 index>
                    inline constexpr RetType<T> operator()(ArgCLRefType<T> value) noexcept
                    {
                        if constexpr (index == 0_i64)
                        {
                            return ArithmeticTrait<T>::one();
                        }
                        else if constexpr (index == 1_i64)
                        {
                            return value;
                        }
                        else if constexpr (index == -1_i64)
                        {
                            return reciprocal(value);
                        }
                        else if constexpr (index > 1_i64)
                        {
                            const auto temp = this->operator()<index / 2_i64>(value);
                            return index % 2_i64 == 0_i64 ? (temp * temp) : (temp * temp * value);
                        }
                        else if constexpr (index < -1_i64)
                        {
                            const auto temp = this->operator()<index / 2_i64>(value);
                            return index % 2_i64 == 0_i64 ? (temp * temp) : (temp * temp * reciprocal(value));
                        }
                    }
                };

                template<i64 index, Invariant T>
                    requires CopyFaster<T> && NumberField<T>
                inline constexpr RetType<T> pow(const T value) noexcept
                {
                    static const PowOperator<T> op{};
                    return op.template operator()<index>(value);
                }

                template<i64 index, Invariant T>
                    requires ReferenceFaster<T> && NumberField<T>
                inline constexpr RetType<T> pow(const T& value) noexcept
                {
                    static const PowOperator<T> op{};
                    return op.template operator()<index>(value);
                }
            };
        };
    };
};
