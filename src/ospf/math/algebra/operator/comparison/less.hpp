#pragma once

#include <ospf/math/algebra/concept/variant.hpp>
#include <ospf/math/algebra/concept/precision.hpp>
#include <ospf/math/algebra/concept/signed.hpp>
#include <ospf/math/algebra/operator/arithmetic/abs.hpp>
#include <ospf/functional/either.hpp>

namespace ospf
{
    inline namespace math
    {
        inline namespace algebra
        {
            inline namespace comparison_operator
            {
                namespace less
                {
                    template<Invariant T>
                    class LessPreciseImpl
                    {
                    public:
                        using ValueType = OriginType<T>;

                    public:
                        constexpr LessPreciseImpl(void) = default;
                        constexpr LessPreciseImpl(const LessPreciseImpl& ano) = default;
                        constexpr LessPreciseImpl(LessPreciseImpl&& ano) noexcept = default;
                        constexpr LessPreciseImpl& operator=(const LessPreciseImpl& rhs) = default;
                        constexpr LessPreciseImpl& operator=(LessPreciseImpl&& RHS) noexcept = default;
                        constexpr ~LessPreciseImpl(void) noexcept = default;

                    public:
                        inline constexpr const bool operator()(CLRefType<ValueType> lhs, CLRefType<ValueType> rhs) const noexcept
                        {
                            return lhs < rhs;
                        }
                    };

                    template<Invariant T>
                        requires WithPrecision<T> && Abs<T>
                    class LessSignedImpreciseImpl
                    {
                    public:
                        using ValueType = OriginType<T>;

                    public:
                        constexpr LessSignedImpreciseImpl(CLRefType<ValueType> precision = PrecisionTrait<ValueType>::decimal_precision)
                            : _precision(std::abs(precision)) {}

                        template<typename = void>
                            requires ReferenceFaster<ValueType> && std::movable<ValueType>
                        LessSignedImpreciseImpl(RRefType<ValueType> precision)
                            : _precision(std::abs(move<ValueType>(precision))) {}

                    public:
                        constexpr LessSignedImpreciseImpl(const LessSignedImpreciseImpl& ano) = default;
                        constexpr LessSignedImpreciseImpl(LessSignedImpreciseImpl&& ano) noexcept = default;
                        constexpr LessSignedImpreciseImpl& operator=(const LessSignedImpreciseImpl& rhs) = default;
                        constexpr LessSignedImpreciseImpl& operator=(LessSignedImpreciseImpl&& rhs) noexcept = default;
                        constexpr ~LessSignedImpreciseImpl(void) noexcept = default;

                    public:
                        inline constexpr const bool operator()(CLRefType<ValueType> lhs, CLRefType<ValueType> rhs) const noexcept
                        {
                            return (lhs - rhs) < -_precision;
                        }

                    private:
                        ValueType _precision;
                    };

                    template<Invariant T>
                        requires WithPrecision<T>
                    class LessUnsignedImpreciseImpl
                    {
                    public:
                        using ValueType = OriginType<T>;

                    public:
                        constexpr LessUnsignedImpreciseImpl(CLRefType<ValueType> precision = PrecisionTrait<ValueType>::decimal_precision)
                            : _precision(precision) {}

                        template<typename = void>
                            requires ReferenceFaster<ValueType> && std::movable<ValueType>
                        LessUnsignedImpreciseImpl(RRefType<ValueType> precision)
                            : _precision(move<ValueType>(precision)) {}

                    public:
                        constexpr LessUnsignedImpreciseImpl(const LessUnsignedImpreciseImpl& ano) = default;
                        constexpr LessUnsignedImpreciseImpl(LessUnsignedImpreciseImpl&& ano) noexcept = default;
                        constexpr LessUnsignedImpreciseImpl& operator=(const LessUnsignedImpreciseImpl& rhs) = default;
                        constexpr LessUnsignedImpreciseImpl& operator=(LessUnsignedImpreciseImpl&& rhs) noexcept = default;
                        constexpr ~LessUnsignedImpreciseImpl(void) noexcept = default;

                    public:
                        inline constexpr const bool operator()(CLRefType<ValueType> lhs, CLRefType<ValueType> rhs) const noexcept
                        {
                            if (lhs < rhs)
                            {
                                return (rhs - lhs) < _precision;
                            }
                            else
                            {
                                return false;
                            }
                        }

                    private:
                        ValueType _precision;
                    };
                };

                template<Invariant T>
                class Less
                {
                    using PreciseImpl = less::LessPreciseImpl<T>;
                    using SignedImpreciseImpl = less::LessSignedImpreciseImpl<T>;
                    using UnsignedImpreciseImpl = less::LessUnsignedImpreciseImpl<T>;
                    using Impl = std::variant<PreciseImpl, SignedImpreciseImpl, UnsignedImpreciseImpl>;

                public:
                    using ValueType = OriginType<T>;

                private:
                    static constexpr Impl impl(CLRefType<ValueType> precision) noexcept
                    {
                        if (precise<ValueType>())
                        {
                            return PreciseImpl{ precision };
                        }
                        else
                        {
                            if constexpr (Signed<ValueType>)
                            {
                                return SignedImpreciseImpl{ precision };
                            }
                            else
                            {
                                return UnsignedImpreciseImpl{ precision };
                            }
                        }
                    }

                    static Impl impl(RRefType<ValueType> precision) noexcept
                    {
                        if (precise<ValueType>())
                        {
                            return PreciseImpl{ move<ValueType>(precision) };
                        }
                        else
                        {
                            if constexpr (Signed<ValueType>)
                            {
                                return SignedImpreciseImpl{ move<ValueType>(precision) };
                            }
                            else
                            {
                                return UnsignedImpreciseImpl{ move<ValueType>(precision) };
                            }
                        }
                    }

                public:
                    template<typename = void>
                        requires WithoutPrecision<ValueType>
                    constexpr Less(CLRefType<ValueType> precision = ArithmeticTrait<ValueType>::zero)
                        : _impl(impl(precision)) {}

                    template<typename = void>
                        requires WithPrecision<ValueType>
                    constexpr Less(CLRefType<ValueType> precision = PrecisionTrait<ValueType>::decimal_precision)
                        : _impl(impl(precision)) {}

                    template<typename = void>
                        requires ReferenceFaster<ValueType>&& std::movable<ValueType>
                    Less(RRefType<ValueType> precision)
                        : _impl(impl(move<ValueType>(precision))) {}

                public:
                    constexpr Less(const Less& ano) = default;
                    constexpr Less(Less&& ano) noexcept = default;
                    constexpr Less& operator=(const Less& rhs) = default;
                    constexpr Less& operator=(Less&& rhs) noexcept = default;
                    constexpr ~Less(void) noexcept = default;

                public:
                    inline constexpr const bool operator()(CLRefType<ValueType> value) const noexcept
                    {
                        if constexpr (CopyFaster<ValueType>)
                        {
                            return std::visit(_impl, [value](const auto& impl)
                                {
                                    return impl(value);
                                });
                        }
                        else
                        {
                            return std::visit(_impl, [&value](const auto& impl)
                                {
                                    return impl(value);
                                });
                        }
                    }

                private:
                    Impl _impl;
                };

                template<Invariant T>
                    requires Precise<T>
                class Less<T>
                    : public less::LessPreciseImpl<T>
                {
                    using Impl = less::LessPreciseImpl<T>;

                public:
                    using typename Impl::ValueType;

                public:
                    constexpr Less(void) = default;
                    constexpr Less(CLRefType<ValueType> _) = default;

                public:
                    constexpr Less(const Less& ano) = default;
                    constexpr Less(Less&& ano) noexcept = default;
                    constexpr Less& operator=(const Less& rhs) = default;
                    constexpr Less& operator=(Less&& rhs) noexcept = default;
                    constexpr ~Less(void) noexcept = default;
                };

                template<Invariant T>
                    requires Imprecise<T> && Signed<T> && Abs<T>
                class Less<T>
                    : public less::LessSignedImpreciseImpl<T>
                {
                    using Impl = less::LessSignedImpreciseImpl<T>;

                public:
                    using typename Impl::ValueType;

                public:
                    constexpr Less(CLRefType<ValueType> precision = PrecisionTrait<ValueType>::decimal_precision)
                        : Impl(precision) {}

                    template<typename = void>
                        requires ReferenceFaster<ValueType>&& std::movable<ValueType>
                    Less(RRefType<ValueType> precision)
                        : Impl(move<ValueType>(precision)) {}

                public:
                    constexpr Less(const Less& ano) = default;
                    constexpr Less(Less&& ano) noexcept = default;
                    constexpr Less& operator=(const Less& rhs) = default;
                    constexpr Less& operator=(Less&& rhs) noexcept = default;
                    constexpr ~Less(void) noexcept = default;
                };

                template<Invariant T>
                    requires Imprecise<T> && Unsigned<T>
                class Less<T>
                    : public less::LessUnsignedImpreciseImpl<T>
                {
                    using Impl = less::LessUnsignedImpreciseImpl<T>;

                public:
                    using typename Impl::ValueType;

                public:
                    constexpr Less(CLRefType<ValueType> precision = PrecisionTrait<ValueType>::decimal_precision)
                        : Impl(precision) {}

                    template<typename = void>
                        requires ReferenceFaster<ValueType>&& std::movable<ValueType>
                    Less(RRefType<ValueType> precision)
                        : Impl(move<ValueType>(precision)) {}

                public:
                    constexpr Less(const Less& ano) = default;
                    constexpr Less(Less&& ano) noexcept = default;
                    constexpr Less& operator=(const Less& rhs) = default;
                    constexpr Less& operator=(Less&& rhs) noexcept = default;
                    constexpr ~Less(void) noexcept = default;
                };

                // todo: extern commom class template specialization
            };
        };
    };
};
