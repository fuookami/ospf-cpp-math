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
        inline namespace algebra
        {
            template<typename T>
            struct BoundedTrait
            {
                static const std::optional<T> maximum;
                static const std::optional<T> minimum;
                static const T positive_minimum;
            };

            template<typename T>
            concept Bounded = requires
            {
                { BoundedTrait<T>::maximum } -> DecaySameAs<std::optional<T>>;
                { BoundedTrait<T>::minimum } -> DecaySameAs<std::optional<T>>;
                { BoundedTrait<T>::positive_minimum } -> DecaySameAs<T>;
            };

            template<>
            struct BoundedTrait<i8>
            {
                static constexpr const std::optional<i8> maximum = std::numeric_limits<i8>::max();
                static constexpr const std::optional<i8> minimum = std::numeric_limits<i8>::lowest();
                static constexpr const i8 positive_minimum = std::numeric_limits<i8>::min();
            };

            template<>
            struct BoundedTrait<u8>
            {
                static constexpr const std::optional<u8> maximum = std::numeric_limits<u8>::max();
                static constexpr const std::optional<u8> minimum = std::numeric_limits<u8>::lowest();
                static constexpr const u8 positive_minimum = std::numeric_limits<u8>::min();
            };

            template<>
            struct BoundedTrait<i16>
            {
                static constexpr const std::optional<i16> maximum = std::numeric_limits<i16>::max();
                static constexpr const std::optional<i16> minimum = std::numeric_limits<i16>::lowest();
                static constexpr const i16 positive_minimum = std::numeric_limits<i16>::min();
            };

            template<>
            struct BoundedTrait<u16>
            {
                static constexpr const std::optional<u16> maximum = std::numeric_limits<u16>::max();
                static constexpr const std::optional<u16> minimum = std::numeric_limits<u16>::lowest();
                static constexpr const u16 positive_minimum = std::numeric_limits<u16>::min();
            };

            template<>
            struct BoundedTrait<i32>
            {
                static constexpr const std::optional<i32> maximum = std::numeric_limits<i32>::max();
                static constexpr const std::optional<i32> minimum = std::numeric_limits<i32>::lowest();
                static constexpr const i32 positive_minimum = std::numeric_limits<i32>::min();
            };

            template<>
            struct BoundedTrait<u32>
            {
                static constexpr const std::optional<u32> maximum = std::numeric_limits<u32>::max();
                static constexpr const std::optional<u32> minimum = std::numeric_limits<u32>::lowest();
                static constexpr const u32 positive_minimum = std::numeric_limits<u32>::min();
            };

            template<>
            struct BoundedTrait<i64>
            {
                static constexpr const std::optional<i64> maximum = std::numeric_limits<i64>::max();
                static constexpr const std::optional<i64> minimum = std::numeric_limits<i64>::lowest();
                static constexpr const i64 positive_minimum = std::numeric_limits<i64>::min();
            };

            template<>
            struct BoundedTrait<u64>
            {
                static constexpr const std::optional<u64> maximum = std::numeric_limits<u64>::max();
                static constexpr const std::optional<u64> minimum = std::numeric_limits<u64>::lowest();
                static constexpr const u64 positive_minimum = std::numeric_limits<u64>::min();
            };

            template<>
            struct BoundedTrait<i128>
            {
                static constexpr const std::optional<i128> maximum = std::numeric_limits<i128>::max();
                static constexpr const std::optional<i128> minimum = std::numeric_limits<i128>::lowest();
                static constexpr const i128 positive_minimum = std::numeric_limits<i128>::min();
            };

            template<>
            struct BoundedTrait<u128>
            {
                static constexpr const std::optional<u128> maximum = std::numeric_limits<u128>::max();
                static constexpr const std::optional<u128> minimum = std::numeric_limits<u128>::lowest();
                static constexpr const u128 positive_minimum = std::numeric_limits<u128>::min();
            };

            template<>
            struct BoundedTrait<i256>
            {
                static constexpr const std::optional<i256> maximum = std::numeric_limits<i256>::max();
                static constexpr const std::optional<i256> minimum = std::numeric_limits<i256>::lowest();
                static constexpr const i256 positive_minimum = std::numeric_limits<i256>::min();
            };

            template<>
            struct BoundedTrait<u256>
            {
                static constexpr const std::optional<u256> maximum = std::numeric_limits<u256>::max();
                static constexpr const std::optional<u256> minimum = std::numeric_limits<u256>::lowest();
                static constexpr const u256 positive_minimum = std::numeric_limits<u256>::min();
            };

            template<>
            struct BoundedTrait<i512>
            {
                static constexpr const std::optional<i512> maximum = std::numeric_limits<i512>::max();
                static constexpr const std::optional<i512> minimum = std::numeric_limits<i512>::lowest();
                static constexpr const i512 positive_minimum = std::numeric_limits<i512>::min();
            };

            template<>
            struct BoundedTrait<u512>
            {
                static constexpr const std::optional<u512> maximum = std::numeric_limits<u512>::max();
                static constexpr const std::optional<u512> minimum = std::numeric_limits<u512>::lowest();
                static constexpr const u512 positive_minimum = std::numeric_limits<u512>::min();
            };

            template<>
            struct BoundedTrait<i1024>
            {
                static constexpr const std::optional<i1024> maximum = std::numeric_limits<i1024>::max();
                static constexpr const std::optional<i1024> minimum = std::numeric_limits<i1024>::lowest();
                static constexpr const i1024 positive_minimum = std::numeric_limits<i1024>::min();
            };

            template<>
            struct BoundedTrait<u1024>
            {
                static constexpr const std::optional<u1024> maximum = std::numeric_limits<u1024>::max();
                static constexpr const std::optional<u1024> minimum = std::numeric_limits<u1024>::lowest();
                static constexpr const u1024 positive_minimum = std::numeric_limits<u1024>::min();
            };

            template<u64 bits>
            struct BoundedTrait<intx<bits>>
            {
                static constexpr const std::optional<intx<bits>> maximum = std::numeric_limits<intx<bits>>::max();
                static constexpr const std::optional<intx<bits>> minimum = std::numeric_limits<intx<bits>>::lowest();
                static constexpr const intx<bits> positive_minimum = std::numeric_limits<intx<bits>>::min();
            };

            template<u64 bits>
            struct BoundedTrait<uintx<bits>>
            {
                static constexpr const std::optional<uintx<bits>> maximum = std::numeric_limits<uintx<bits>>::max();
                static constexpr const std::optional<uintx<bits>> minimum = std::numeric_limits<uintx<bits>>::lowest();
                static constexpr const uintx<bits> positive_minimum = std::numeric_limits<uintx<bits>>::min();
            };

            template<>
            struct BoundedTrait<bigint>
            {
                OSPF_MATH_API static const std::optional<bigint> maximum;
                OSPF_MATH_API static const std::optional<bigint> minimum;
                OSPF_MATH_API static const bigint positive_minimum;
            };

            template<>
            struct BoundedTrait<f32>
            {
                static constexpr const std::optional<f32> maximum = std::numeric_limits<f32>::max();
                static constexpr const std::optional<f32> minimum = std::numeric_limits<f32>::lowest();
                static constexpr const f32 positive_minimum = std::numeric_limits<f32>::min();
            };

            template<>
            struct BoundedTrait<f64>
            {
                static constexpr const std::optional<f64> maximum = std::numeric_limits<f64>::max();
                static constexpr const std::optional<f64> minimum = std::numeric_limits<f64>::lowest();
                static constexpr const f64 positive_minimum = std::numeric_limits<f64>::min();
            };

            template<>
            struct BoundedTrait<f128>
            {
                OSPF_MATH_API static const std::optional<f128> maximum;
                OSPF_MATH_API static const std::optional<f128> minimum;
                OSPF_MATH_API static const f128 positive_minimum;
            };

            template<>
            struct BoundedTrait<f256>
            {
                OSPF_MATH_API static const std::optional<f256> maximum;
                OSPF_MATH_API static const std::optional<f256> minimum;
                OSPF_MATH_API static const f256 positive_minimum;
            };

            template<>
            struct BoundedTrait<f512>
            {
                OSPF_MATH_API static const std::optional<f512> maximum;
                OSPF_MATH_API static const std::optional<f512> minimum;
                OSPF_MATH_API static const f512 positive_minimum;
            };

            template<>
            struct BoundedTrait<dec50>
            {
                OSPF_MATH_API static const std::optional<dec50> maximum;
                OSPF_MATH_API static const std::optional<dec50> minimum;
                OSPF_MATH_API static const dec50 positive_minimum;
            };

            template<>
            struct BoundedTrait<dec100>
            {
                OSPF_MATH_API static const std::optional<dec100> maximum;
                OSPF_MATH_API static const std::optional<dec100> minimum;
                OSPF_MATH_API static const dec100 positive_minimum;
            };

            template<u64 digits>
            struct BoundedTrait<dec<digits>>
            {
                static constexpr const std::optional<dec<digits>> maximum = std::nullopt;
                static constexpr const std::optional<dec<digits>> minimum = std::nullopt;
                static const dec<digits> positive_minimum;
            };
        };
    };
};

template<ospf::u64 digits>
const ospf::dec<digits> ospf::BoundedTrait<ospf::dec<digits>>::positive_minimum = ospf::dec<digits>{ 1._f64 };
