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
                namespace equal
                {
                    template<Invariant T>
                    class EqualPreciseImpl
                    {
                    public:
                        using ValueType = OriginType<T>;

                    public:
                        constexpr EqualPreciseImpl(void) = default;
                        constexpr EqualPreciseImpl(const EqualPreciseImpl& ano) = default;
                        constexpr EqualPreciseImpl(EqualPreciseImpl&& ano) noexcept = default;
                        constexpr EqualPreciseImpl& operator=(const EqualPreciseImpl& rhs) = default;
                        constexpr EqualPreciseImpl& operator=(EqualPreciseImpl&& rhs) noexcept = default;
                        constexpr ~EqualPreciseImpl(void) noexcept = default;

                    public:
                        inline constexpr const bool operator()(const CLRefType<ValueType> lhs, const CLRefType<ValueType> rhs) const noexcept
                        {
                            return (lhs - rhs) == ArithmeticTrait<ValueType>::zero;
                        }
                    };

                    template<Invariant T>
                        requires WithPrecision<T> && Abs<T>
                    class EqualSignedImpreciseImpl
                    {
                    public:
                        using ValueType = OriginType<T>;

                    public:
                        constexpr EqualSignedImpreciseImpl(CLRefType<ValueType> precision = PrecisionTrait<T>::decimal_precision)
                            : _precision(std::abs(precision)) {}

                        template<typename = void>
                            requires ReferenceFaster<ValueType> && std::movable<ValueType>
                        EqualSignedImpreciseImpl(RRefType<ValueType> precision)
                            : _precision(std::abs(move<ValueType>(precision))) {}

                    public:
                        constexpr EqualSignedImpreciseImpl(const EqualSignedImpreciseImpl& ano) = default;
                        constexpr EqualSignedImpreciseImpl(EqualSignedImpreciseImpl&& ano) noexcept = default;
                        constexpr EqualSignedImpreciseImpl& operator=(const EqualSignedImpreciseImpl& rhs) = default;
                        constexpr EqualSignedImpreciseImpl& operator=(EqualSignedImpreciseImpl&& rhs) noexcept = default;
                        constexpr ~EqualSignedImpreciseImpl(void) noexcept = default;

                    public:
                        inline constexpr const bool operator()(CLRefType<ValueType> lhs, CLRefType<ValueType> rhs) const noexcept
                        {
                            return std::abs(lhs - rhs) <= _precision;
                        }

                    private:
                        ValueType _precision;
                    };

                    template<Invariant T>
                        requires WithPrecision<T>
                    class EqualUnsignedImpreciseImpl
                    {
                    public:
                        using ValueType = OriginType<T>;

                    public:
                        constexpr EqualUnsignedImpreciseImpl(CLRefType<ValueType> precision = PrecisionTrait<T>::decimal_precision)
                            : _precision(precision) {}

                        template<typename = void>
                            requires ReferenceFaster<ValueType> && std::movable<ValueType>
                        EqualUnsignedImpreciseImpl(RRefType<ValueType> precision)
                            : _precision(move<ValueType>(precision)) {}

                    public:
                        constexpr EqualUnsignedImpreciseImpl(const EqualUnsignedImpreciseImpl& ano) = default;
                        constexpr EqualUnsignedImpreciseImpl(EqualUnsignedImpreciseImpl&& ano) noexcept = default;
                        constexpr EqualUnsignedImpreciseImpl& operator=(const EqualUnsignedImpreciseImpl& rhs) = default;
                        constexpr EqualUnsignedImpreciseImpl& operator=(EqualUnsignedImpreciseImpl&& rhs) noexcept = default;
                        constexpr ~EqualUnsignedImpreciseImpl(void) noexcept = default;

                    public:
                        inline constexpr const bool operator()(CLRefType<ValueType> lhs, CLRefType<ValueType> rhs) const noexcept
                        {
                            if (lhs < rhs)
                            {
                                return (rhs - lhs) <= _precision
                            }
                            else
                            {
                                return (lhs - rhs) <= _precision;
                            }
                        }

                    private:
                        ValueType _precision;
                    };
                };

                template<Invariant T>
                class Equal
                {
                    using PreciseImpl = equal::EqualPreciseImpl<T>;
                    using SignedImpreciseImpl = equal::EqualSignedImpreciseImpl<T>;
                    using UnsignedImpreciseImpl = equal::EqualUnsignedImpreciseImpl;
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
                    constexpr Equal(CLRefType<ValueType> precision = ArithmeticTrait<T>::zero)
                        : _impl(impl(precision)) {}

                    template<typename = void>
                        requires WithPrecision<ValueType>
                    constexpr Equal(CLRefType<ValueType> precision = PrecisionTrait<T>::decimal_precision)
                        : _impl(impl(precision)) {}

                    template<typename = void>
                        requires ReferenceFaster<ValueType> && std::movable<ValueType>
                    Equal(RRefType<ValueType> precision)
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
                class Equal
                    : public equal::EqualPreciseImpl<T>
                {
                    using Impl = equal::EqualPreciseImpl<T>;

                public:
                    using typename Impl::ValueType;

                public:
                    constexpr Equal(void) = default;
                    constexpr Equal(CLRefType<ValueType> _) = default;

                public:
                    constexpr Equal(const Equal& ano) = default;
                    constexpr Equal(Equal&& ano) noexcept = default;
                    constexpr Equal& operator=(const Equal& rhs) = default;
                    constexpr Equal& operator=(Equal&& rhs) noexcept = default;
                    constexpr ~Equal(void) noexcept = default;
                };

                template<Invariant T>
                    requires Imprecise<T> && Signed<T> && Abs<T>
                class Equal<T>
                    : public equal::EqualSignedImpreciseImpl<T>
                {
                    using Impl = equal::EqualSignedImpreciseImpl<T>;

                public:
                    using typename Impl::ValueType;

                public:
                    constexpr Equal(CLRefType<ValueType> precision = PrecisionTrait<T>::decimal_precision)
                        : Impl(precision) {}

                    template<typename = void>
                        requires ReferenceFaster<ValueType> && std::movable<ValueType>
                    Equal(RRefType<ValueType> precision)
                        : Impl(move<ValueType>(precision)) {}

                public:
                    constexpr Equal(const Equal& ano) = default;
                    constexpr Equal(Equal&& ano) noexcept = default;
                    constexpr Equal& operator=(const Equal& rhs) = default;
                    constexpr Equal& operator=(Equal&& rhs) noexcept = default;
                    constexpr ~Equal(void) noexcept = default;
                };

                template<Invariant T>
                    requires Imprecise<T> && Unsigned<T>
                class Equal<T>
                    : public equal::EqualUnsignedImpreciseImpl<T>
                {
                    using Impl = equal::EqualUnsignedImpreciseImpl<T>;

                public:
                    using typename Impl::ValueType;

                public:
                    constexpr Equal(CLRefType<ValueType> precision = PrecisionTrait<T>::decimal_precision)
                        : Impl(precision) {}

                    template<typename = void>
                        requires ReferenceFaster<ValueType> && std::movable<ValueType>
                    Equal(RRefType<ValueType> precision)
                        : Impl(move<ValueType>(precision)) {}

                public:
                    constexpr Equal(const Equal& ano) = default;
                    constexpr Equal(Equal&& ano) noexcept = default;
                    constexpr Equal& operator=(const Equal& rhs) = default;
                    constexpr Equal& operator=(Equal&& rhs) noexcept = default;
                    constexpr ~Equal(void) noexcept = default;
                };

                // todo: extern commom class template specialization
            };
        };
    };
};
