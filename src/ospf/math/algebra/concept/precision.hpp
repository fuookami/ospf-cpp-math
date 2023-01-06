#pragma once

#include <ospf/basic_definition.hpp>
#include <ospf/literal_constant.hpp>
#include <ospf/concepts.hpp>
#include <ospf/math/ospf_math_api.hpp>
#include <ospf/math/algebra/concept/arithmetic.hpp>
#include <optional>

namespace ospf
{
    inline namespace math
    {
        inline namespace algebra
        {
            template<typename T>
            struct PrecisionTrait
            {
                static const T epsilon;
                static const std::optional<usize> decimal_digits;
                static const T decimal_precision;
            };

            template<typename T>
            concept WithPrecision = Arithmetic<T> 
                && requires
                {
                    { PrecisionTrait<T>::epsilon } -> DecaySameAs<T>;
                    { PrecisionTrait<T>::decimal_digits } -> DecaySameAs<std::optional<usize>>;
                    { PrecisionTrait<T>::positive_minimum } -> DecaySameAs<T>;
                };

            template<typename T>
            inline static constexpr const bool precision(void) noexcept
            {
                return PrecisionTrait<T>::positive_minimum == ArithmeticTrait<T>::zero;
            }

            template<WithPrecision T>
            struct IsPrecise
            {
                static constexpr const bool value = false;
            };

            template<WithPrecision T>
                requires requires { { PrecisionTrait<T>::positive_minimum == ArithmeticTrait<T>::zero } -> std::same_as<std::true_type>; }
            struct IsPrecise
            {
                static constexpr const bool value = true;
            };

            template<typename T>
            concept Precise = WithPrecision<T> && IsPrecise<T>::value;

            template<typename T>
            concept Imprecise = WithPrecision<T> && !IsPrecise<T>::value;

            template<>
            struct PrecisionTrait<i8>
            {
                static constexpr const i8 epsilon = 0_i8;
                static constexpr const std::optional<usize> decimal_digits = std::nullopt;
                static constexpr const i8 decimal_precision = 0_i8;
            };

            template<>
            struct PrecisionTrait<u8>
            {
                static constexpr const u8 epsilon = 0_u8;
                static constexpr const std::optional<usize> decimal_digits = std::nullopt;
                static constexpr const u8 decimal_precision = 0_u8;
            };

            template<>
            struct PrecisionTrait<i16>
            {
                static constexpr const i16 epsilon = 0_i16;
                static constexpr const std::optional<usize> decimal_digits = std::nullopt;
                static constexpr const i16 decimal_precision = 0_i16;
            };

            template<>
            struct PrecisionTrait<u16>
            {
                static constexpr const u16 epsilon = 0_u16;
                static constexpr const std::optional<usize> decimal_digits = std::nullopt;
                static constexpr const u16 decimal_precision = 0_u16;
            };

            template<>
            struct PrecisionTrait<i32>
            {
                static constexpr const i32 epsilon = 0_i32;
                static constexpr const std::optional<usize> decimal_digits = std::nullopt;
                static constexpr const i32 decimal_precision = 0_i32;
            };

            template<>
            struct PrecisionTrait<u32>
            {
                static constexpr const u32 epsilon = 0_u32;
                static constexpr const std::optional<usize> decimal_digits = std::nullopt;
                static constexpr const u32 decimal_precision = 0_u32;
            };

            template<>
            struct PrecisionTrait<i64>
            {
                static constexpr const i64 epsilon = 0_i64;
                static constexpr const std::optional<usize> decimal_digits = std::nullopt;
                static constexpr const i64 decimal_precision = 0_i64;
            };

            template<>
            struct PrecisionTrait<u64>
            {
                static constexpr const u64 epsilon = 0_u64;
                static constexpr const std::optional<usize> decimal_digits = std::nullopt;
                static constexpr const u64 decimal_precision = 0_u64;
            };

            template<>
            struct PrecisionTrait<i128>
            {
                static constexpr const i128 epsilon = i128{ 0_i64 };
                static constexpr const std::optional<usize> decimal_digits = std::nullopt;
                static constexpr const i128 decimal_precision = i128{ 0_i64 };
            };

            template<>
            struct PrecisionTrait<u128>
            {
                static constexpr const u128 epsilon = u128{ 0_u64 };
                static constexpr const std::optional<usize> decimal_digits = std::nullopt;
                static constexpr const u128 decimal_precision = u128{ 0_u64 };
            };

            template<>
            struct PrecisionTrait<i256>
            {
                static constexpr const i256 epsilon = i256{ 0_i64 };
                static constexpr const std::optional<usize> decimal_digits = std::nullopt;
                static constexpr const i256 decimal_precision = i256{ 0_i64 };
            };

            template<>
            struct PrecisionTrait<u256>
            {
                static constexpr const u256 epsilon = u256{ 0_u64 };
                static constexpr const std::optional<usize> decimal_digits = std::nullopt;
                static constexpr const u256 decimal_precision = u256{ 0_u64 };
            };

            template<>
            struct PrecisionTrait<i512>
            {
                static constexpr const i512 epsilon = i512{ 0_i64 };
                static constexpr const std::optional<usize> decimal_digits = std::nullopt;
                static constexpr const i512 decimal_precision = i512{ 0_i64 };
            };

            template<>
            struct PrecisionTrait<u512>
            {
                static constexpr const u512 epsilon = u512{ 0_u64 };
                static constexpr const std::optional<usize> decimal_digits = std::nullopt;
                static constexpr const u512 decimal_precision = u512{ 0_u64 };
            };

            template<>
            struct PrecisionTrait<i1024>
            {
                static constexpr const i1024 epsilon = i1024{ 0_i64 };
                static constexpr const std::optional<usize> decimal_digits = std::nullopt;
                static constexpr const i1024 decimal_precision = i1024{ 0_i64 };
            };

            template<>
            struct PrecisionTrait<u1024>
            {
                static constexpr const u1024 epsilon = u1024{ 0_u64 };
                static constexpr const std::optional<usize> decimal_digits = std::nullopt;
                static constexpr const u1024 decimal_precision = u1024{ 0_u64 };
            };

            template<u64 bits>
            struct PrecisionTrait<intx<bits>>
            {
                static constexpr const intx<bits> epsilon = intx<bits>{ 0_i64 };
                static constexpr const std::optional<usize> decimal_digits = std::nullopt;
                static constexpr const intx<bits> decimal_precision = intx<bits>{ 0_i64 };
            };

            template<u64 bits>
            struct PrecisionTrait<uintx<bits>>
            {
                static constexpr const uintx<bits> epsilon = uintx<bits>{ 0_u64 };
                static constexpr const std::optional<usize> decimal_digits = std::nullopt;
                static constexpr const uintx<bits> decimal_precision = uintx<bits>{ 0_u64 };
            };

            template<>
            struct PrecisionTrait<bigint>
            {
                OSPF_MATH_API static const bigint epsilon;
                static constexpr const std::optional<usize> decimal_digits = std::nullopt;
                OSPF_MATH_API static const bigint decimal_precision;
            };

            template<>
            struct PrecisionTrait<f32>
            {
                static constexpr const f32 epsilon = std::numeric_limits<f32>::denorm_min();
                static constexpr const std::optional<usize> decimal_digits = static_cast<usize>(std::numeric_limits<f32>::digits10);
                static constexpr const f32 decimal_precision = std::numeric_limits<f32>::epsilon();
            };

            template<>
            struct PrecisionTrait<f64>
            {
                static constexpr const f64 epsilon = std::numeric_limits<f64>::denorm_min();
                static constexpr const std::optional<usize> decimal_digits = static_cast<usize>(std::numeric_limits<f64>::digits10);
                static constexpr const f64 decimal_precision = std::numeric_limits<f64>::epsilon();
            };

            template<>
            struct PrecisionTrait<f128>
            {
                OSPF_MATH_API static const f128 epsilon;
                static constexpr const std::optional<usize> decimal_digits = static_cast<usize>(std::numeric_limits<f128>::digits10);
                OSPF_MATH_API static const f128 decimal_precision;
            };

            template<>
            struct PrecisionTrait<f256>
            {
                OSPF_MATH_API static const f256 epsilon;
                static constexpr const std::optional<usize> decimal_digits = static_cast<usize>(std::numeric_limits<f256>::digits10);
                OSPF_MATH_API static const f256 decimal_precision;
            };

            template<>
            struct PrecisionTrait<f512>
            {
                OSPF_MATH_API static const f512 epsilon;
                static constexpr const std::optional<usize> decimal_digits = static_cast<usize>(std::numeric_limits<f512>::digits10);
                OSPF_MATH_API static const f512 decimal_precision;
            };

            template<>
            struct PrecisionTrait<dec50>
            {
                OSPF_MATH_API static const dec50 epsilon;
                static constexpr const std::optional<usize> decimal_digits = static_cast<usize>(std::numeric_limits<dec50>::digits10);
                OSPF_MATH_API static const dec50 decimal_precision;
            };

            template<>
            struct PrecisionTrait<dec100>
            {
                OSPF_MATH_API static const dec100 epsilon;
                static constexpr const std::optional<usize> decimal_digits = static_cast<usize>(std::numeric_limits<dec100>::digits10);
                OSPF_MATH_API static const dec100 decimal_precision;
            };

            template<u64 digits>
            struct PrecisionTrait<dec<digits>>
            {
                static const dec<digits> epsilon;
                static constexpr const std::optional<usize> decimal_digits = static_cast<usize>(std::numeric_limits<dec<digits>>::digits10);
                static const dec<digits> decimal_precision;
            };
        };
    };
};

template<ospf::u64 digits>
const ospf::dec<digits> ospf::PrecisionTrait<ospf::dec<digits>>::epsilon = std::numeric_limits<ospf::dec<digits>>::denorm_min();

template<ospf::u64 digits>
const ospf::dec<digits> ospf::PrecisionTrait<ospf::dec<digits>>::decimal_precision = std::numeric_limits<ospf::dec<digits>>::epsilon();
