#pragma once

#include <ospf/math/algebra/concepts/field.hpp>
#include <ospf/math/algebra/concepts/precision.hpp>
#include <ospf/math/algebra/concepts/scalar.hpp>
#include <ospf/math/algebra/concepts/signed.hpp>
#include <ospf/math/algebra/concepts/variant.hpp>

namespace ospf
{
    inline namespace math
    {
        inline namespace algebra
        {
            template<typename T>
            struct RealNumberTrait;

            template<typename T>
            concept RealNumber = Scalar<T>
                && WithPrecision<T>
                && Invariant<T>
                && std::default_initializable<RealNumberTrait<T>>
                && requires (const T& value)
                {
                    { RealNumberTrait<T>::two() } -> DecaySameAs<T>;
                    { RealNumberTrait<T>::three() } -> DecaySameAs<T>;
                    { RealNumberTrait<T>::five() } -> DecaySameAs<T>;
                    { RealNumberTrait<T>::nan() } -> DecaySameAs<std::optional<T>, std::optional<Ref<T>>>;
                    { RealNumberTrait<T>::inf() } -> DecaySameAs<std::optional<T>, std::optional<Ref<T>>>;
                    { RealNumberTrait<T>::neg_inf() } -> DecaySameAs<std::optional<T>, std::optional<Ref<T>>>;
                    { RealNumberTrait<T>::is_nan(value) } -> DecaySameAs<bool>;
                    { RealNumberTrait<T>::is_inf(value) } -> DecaySameAs<bool>;
                    { RealNumberTrait<T>::is_neg_inf(value) } -> DecaySameAs<bool>;
                };

            template<typename T>
            concept Integer = RealNumber<T> 
                // RangeTo, Log, PowF, Exp
                && std::three_way_comparable<T, std::weak_ordering>;

            template<typename T>
            concept IntegerNumber = Integer<T>
                && Signed<T>
                && NumberField<T>;
                // Pow

            template<typename T>
            concept UIntegerNumber = Integer<T>
                && Unsigned<T>
                && NumberField<T>;
                // Pow

            template<typename T>
            concept RationalNumber = RealNumber<T>
                && NumberField<T>
                // Log, PowF, Exp, Pow
                && std::three_way_comparable<T, std::weak_ordering>
                && Integer<typename T::IntegerType>
                && requires (const T& value) 
                {
                    { value.num() } -> DecaySameAs<typename T::IntegerType>;
                    { value.den() } -> DecaySameAs<typename T::IntegerType>;
                };

            template<RealNumber T>
            struct FloatingNumberTrait;

            template<typename T>
            concept FloatingNumber = RealNumber<T>
                && Signed<T>
                && NumberField<T>
                // Log, PowF, Exp, Pow
                && std::default_initializable<FloatingNumberTrait<T>>
                && requires
                {
                    { FloatingNumberTrait<T>::pi() } -> DecaySameAs<T>;
                    { FloatingNumberTrait<T>::e() } -> DecaySameAs<T>;
                    // floor, ceil, round, trunc, fract
                };

            // NumericIntegerNumber, NumericUIntegerNumber

            namespace real_number
            {
                template<typename T>
                struct IntegerNumberTraitTemplate
                {
                    inline static constexpr const std::optional<T> nan(void) noexcept
                    {
                        return std::nullopt;
                    }

                    inline static constexpr const std::optional<T> inf(void) noexcept
                    {
                        return std::nullopt;
                    }

                    inline static constexpr const std::optional<T> neg_inf(void) noexcept
                    {
                        return std::nullopt;
                    }

                    inline static constexpr const bool is_nan(ArgCLRefType<T> _) noexcept
                    {
                        return false;
                    }

                    inline static constexpr const bool is_inf(ArgCLRefType<T> _) noexcept
                    {
                        return false;
                    }

                    inline static constexpr const bool is_neg_inf(ArgCLRefType<T> _) noexcept
                    {
                        return false;
                    }
                };
            };

            template<>
            struct RealNumberTrait<i8>
                : public real_number::IntegerNumberTraitTemplate<i8>
            {
                inline static constexpr const i8 two(void) noexcept
                {
                    return 2_i8;
                }

                inline static constexpr const i8 three(void) noexcept
                {
                    return 3_i8;
                }

                inline static constexpr const i8 five(void) noexcept
                {
                    return 5_i8;
                }
            };

            template<>
            struct RealNumberTrait<u8>
                : public real_number::IntegerNumberTraitTemplate<u8>
            {
                inline static constexpr const u8 two(void) noexcept
                {
                    return 2_u8;
                }

                inline static constexpr const u8 three(void) noexcept
                {
                    return 3_u8;
                }

                inline static constexpr const u8 five(void) noexcept
                {
                    return 5_u8;
                }
            };

            template<>
            struct RealNumberTrait<i16>
                : public real_number::IntegerNumberTraitTemplate<i16>
            {
                inline static constexpr const i16 two(void) noexcept
                {
                    return 2_i16;
                }

                inline static constexpr const i16 three(void) noexcept
                {
                    return 3_i16;
                }

                inline static constexpr const i16 five(void) noexcept
                {
                    return 5_i16;
                }
            };

            template<>
            struct RealNumberTrait<u16>
                : public real_number::IntegerNumberTraitTemplate<u16>
            {
                inline static constexpr const u16 two(void) noexcept
                {
                    return 2_u16;
                }

                inline static constexpr const i16 three(void) noexcept
                {
                    return 3_u16;
                }

                inline static constexpr const u16 five(void) noexcept
                {
                    return 5_u16;
                }
            };

            template<>
            struct RealNumberTrait<i32>
                : public real_number::IntegerNumberTraitTemplate<i32>
            {
                inline static constexpr const i32 two(void) noexcept
                {
                    return 2_i32;
                }

                inline static constexpr const i32 three(void) noexcept
                {
                    return 3_i32;
                }

                inline static constexpr const i32 five(void) noexcept
                {
                    return 5_i32;
                }
            };
        };
    };
};
