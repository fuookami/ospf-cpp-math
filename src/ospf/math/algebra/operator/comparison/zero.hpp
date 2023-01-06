#pragma once

#include <ospf/math/algebra/concept/variant.hpp>
#include <ospf/math/algebra/concept/precision.hpp>
#include <ospf/math/algebra/concept/signed.hpp>
#include <ospf/functional/either.hpp>

namespace ospf
{
    inline namespace math
    {
        inline namespace algebra
        {
            inline namespace comparison_operator
            {
                namespace zero
                {
                    template<Invariant T>
                    class ZeroPreciseImpl
                    {
                    public:
                        using ValueType = OriginType<T>;

                    public:
                        constexpr ZeroPreciseImpl(void) = default;
                        constexpr ZeroPreciseImpl(const ZeroPreciseImpl& ano) = default;
                        constexpr ZeroPreciseImpl(ZeroPreciseImpl&& ano) noexcept = default;
                        constexpr ZeroPreciseImpl& operator=(const ZeroPreciseImpl& rhs) = default;
                        constexpr ZeroPreciseImpl& operator=(ZeroPreciseImpl&& rhs) noexcept = default;
                        constexpr ~ZeroPreciseImpl(void) noexcept = default;

                    public:
                        inline constexpr const bool operator()(CLRefType<ValueType> value) const noexcept
                        {
                            return value == ArithmeticTrait<ValueType>::zero;
                        }
                    };

                    template<Invariant T>
                        requires WithPrecision<T> && requires (const T& value) { { std::abs(value) } -> DecaySameAs<T>; }
                    class ZeroSignedImpreciseImpl
                    {
                    public:
                        using ValueType = OriginType<T>;

                    public:
                        constexpr ZeroSignedImpreciseImpl(CLRefType<ValueType> precision = PrecisionTrait<T>::decimal_precision)
                            : _precision(std::abs(precision)) {}

                        template<typename = void>
                            requires ReferenceFaster<ValueType>&& std::movable<ValueType>
                        ZeroSignedImpreciseImpl(RRefType<ValueType> precision)
                            : _precision(std::abs(move<ValueType>(precision))) {}

                    public:
                        constexpr ZeroSignedImpreciseImpl(const ZeroSignedImpreciseImpl& ano) = default;
                        constexpr ZeroSignedImpreciseImpl(ZeroSignedImpreciseImpl&& ano) noexcept = default;
                        constexpr ZeroSignedImpreciseImpl& operator=(const ZeroSignedImpreciseImpl& rhs) = default;
                        constexpr ZeroSignedImpreciseImpl& operator=(ZeroSignedImpreciseImpl&& rhs) noexcept = default;
                        constexpr ~ZeroSignedImpreciseImpl(void) noexcept = default;

                    public:
                        inline constexpr const bool operator()(CLRefType<ValueType> value) const noexcept
                        {
                            return std::abs(value) <= _precision;
                        }

                    private:
                        ValueType _precision;
                    };

                    template<Invariant T>
                        requires WithPrecision<T>
                    class ZeroUnsignedImpreciseImpl
                    {
                    public:
                        using ValueType = OriginType<T>;

                    public:
                        constexpr ZeroUnsignedImpreciseImpl(CLRefType<ValueType> precision = PrecisionTrait<T>::decimal_precision)
                            : _precision(precision) {}

                        template<typename = void>
                            requires ReferenceFaster<ValueType>&& std::movable<ValueType>
                        ZeroUnsignedImpreciseImpl(RRefType<ValueType> precision)
                            : _precision(move<ValueType>(precision)) {}

                    public:
                        constexpr ZeroUnsignedImpreciseImpl(const ZeroUnsignedImpreciseImpl& ano) = default;
                        constexpr ZeroUnsignedImpreciseImpl(ZeroUnsignedImpreciseImpl&& ano) noexcept = default;
                        constexpr ZeroUnsignedImpreciseImpl& operator=(const ZeroUnsignedImpreciseImpl& rhs) = default;
                        constexpr ZeroUnsignedImpreciseImpl& operator=(ZeroUnsignedImpreciseImpl&& rhs) noexcept = default;
                        constexpr ~ZeroUnsignedImpreciseImpl(void) noexcept = default;

                    public:
                        inline constexpr const bool operator()(CLRefType<ValueType> value) const noexcept
                        {
                            return value <= _precision;
                        }

                    private:
                        ValueType _precision;
                    };
                };

                template<Invariant T>
                class Zero
                {
                    using PreciseImpl = zero::ZeroPreciseImpl<T>;
                    using SignedImpreciseImpl = zero::ZeroSignedImpreciseImpl<T>;
                    using UnsignedImpreciseImpl = zero::ZeroUnsignedImpreciseImpl<T>;
                    using Impl = std::variant<PreciseImpl, SignedImpreciseImpl, UnsignedImpreciseImpl>;

                public:
                    using ValueType = OriginType<T>;

                private:
                    static constexpr Impl impl(CLRefType<ValueType> precision) noexcept
                    {
                        if (precision<ValueType>())
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
                        if (precision<ValueType>())
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
                    constexpr Zero(CLRefType<ValueType> precision = PrecisionTrait<T>::decimal_precision)
                        : _impl(impl(precision)) {}

                    template<typename = void>
                        requires ReferenceFaster<ValueType> && std::movable<ValueType>
                    Zero(RRefType<ValueType> precision)
                        : _impl(impl(move<ValueType>(precision))) {}

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
                class Zero
                    : public zero::ZeroPreciseImpl<T>
                {
                    using Impl = zero::ZeroPreciseImpl<T>;

                public:
                    using typename Impl::ValueType;

                public:
                    constexpr Zero(void) = default;
                    constexpr Zero(CLRefType<ValueType> _) = default;

                public:
                    constexpr Zero(const Zero& ano) = default;
                    constexpr Zero(Zero&& ano) noexcept = default;
                    constexpr Zero& operator=(const Zero& rhs) = default;
                    constexpr Zero& operator=(Zero&& rhs) noexcept = default;
                    constexpr ~Zero(void) noexcept = default;
                };
                
                template<WithPrecision T>
                    requires Imprecise<T> && Signed<T> && requires (const T& value) { { std::abs(value) } -> DecaySameAs<T>; }
                class Zero<T>
                    : public zero::ZeroSignedImpreciseImpl<T>
                {
                    using Impl = zero::ZeroSignedImpreciseImpl<T>;

                public:
                    using typename Impl::ValueType;

                public:
                    constexpr Zero(CLRefType<ValueType> precision = PrecisionTrait<T>::decimal_precision)
                        : Impl(precision) {}

                    template<typename = void>
                        requires ReferenceFaster<ValueType> && std::movable<ValueType>
                    Zero(RRefType<ValueType> precision)
                        : Impl(move<ValueType>(precision)) {}

                public:
                    constexpr Zero(const Zero& ano) = default;
                    constexpr Zero(Zero&& ano) noexcept = default;
                    constexpr Zero& operator=(const Zero& rhs) = default;
                    constexpr Zero& operator=(Zero&& rhs) noexcept = default;
                    constexpr ~Zero(void) noexcept = default;
                };

                template<WithPrecision T>
                    requires Imprecise<T> && Unsigned<T>
                class Zero<T>
                    : public zero::ZeroUnsignedImpreciseImpl<T>
                {
                    using Impl = zero::ZeroUnsignedImpreciseImpl<T>;

                public:
                    using typename Impl::ValueType;

                public:
                    constexpr Zero(CLRefType<ValueType> precision = PrecisionTrait<T>::decimal_precision)
                        : Impl(precision) {}

                    template<typename = void>
                        requires ReferenceFaster<ValueType> && std::movable<ValueType>
                    Zero(RRefType<ValueType> precision)
                        : Impl(move<ValueType>(precision)) {}

                public:
                    constexpr Zero(const Zero& ano) = default;
                    constexpr Zero(Zero&& ano) noexcept = default;
                    constexpr Zero& operator=(const Zero& rhs) = default;
                    constexpr Zero& operator=(Zero&& rhs) noexcept = default;
                    constexpr ~Zero(void) noexcept = default;
                };
            };
        };
    };
};
