#pragma once

#include <ospf/math/algebra/concepts/arithmetic.hpp>
#include <ospf/math/algebra/operator/arithmetic/neg.hpp>

namespace ospf
{
    inline namespace math
    {
        inline namespace algebra
        {
            inline namespace concepts
            {
                template<Arithmetic T>
                struct SignedTrait;

                template<Arithmetic T>
                struct UnsignedTrait;

                template<typename T>
                concept Signed = Arithmetic<T>
                    && Neg<T>
                    && std::default_initializable<SignedTrait<T>>;

                template<typename T>
                concept Unsigned = Arithmetic<T>
                    && std::default_initializable<UnsignedTrait<T>>;

                template<> struct UnsignedTrait<u8> {};
                template<> struct UnsignedTrait<u16> {};
                template<> struct UnsignedTrait<u32> {};
                template<> struct UnsignedTrait<u64> {};
                template<> struct UnsignedTrait<u128> {};
                template<> struct UnsignedTrait<u256> {};
                template<> struct UnsignedTrait<u512> {};
                template<> struct UnsignedTrait<u1024> {};
                template<usize bits> struct UnsignedTrait<uintx<bits>> {};

                template<> struct SignedTrait<i8> {};
                template<> struct SignedTrait<i16> {};
                template<> struct SignedTrait<i32> {};
                template<> struct SignedTrait<i64> {};
                template<> struct SignedTrait<i128> {};
                template<> struct SignedTrait<i256> {};
                template<> struct SignedTrait<i512> {};
                template<> struct SignedTrait<i1024> {};
                template<usize bits> struct SignedTrait<intx<bits>> {};
                template<> struct SignedTrait<bigint> {};

                template<> struct SignedTrait<f32> {};
                template<> struct SignedTrait<f64> {};
                template<> struct SignedTrait<f128> {};
                template<> struct SignedTrait<f256> {};
                template<> struct SignedTrait<f512> {};
                template<> struct SignedTrait<dec50> {};
                template<> struct SignedTrait<dec100> {};
                template<usize digits> struct SignedTrait<dec<digits>> {};
            };
        };
    };
};
