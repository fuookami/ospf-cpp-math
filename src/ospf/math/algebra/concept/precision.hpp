#pragma once

#include <ospf/basic_definition.hpp>
#include <ospf/literal_constant.hpp>
#include <ospf/concepts.hpp>
#include <ospf/math/ospf_math_api.hpp>
#include <optional>

namespace ospf
{
    inline namespace math
    {
        template<typename T>
        struct PrecisionTrait
        {
            static const T epsilon;
            static const std::optional<usize> decimal_digits;
            static const T decimal_precision;
        };

        template<typename T>
        concept WithPrecision = requires
        {
            { PrecisionTrait<T>::epsilon } -> DecaySameAs<T>;
            { PrecisionTrait<T>::decimal_digits } -> DecaySameAs<std::optional<usize>>;
            { PrecisionTrait<T>::positive_minimum } -> DecaySameAs<T>;
        };

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
    };
};
