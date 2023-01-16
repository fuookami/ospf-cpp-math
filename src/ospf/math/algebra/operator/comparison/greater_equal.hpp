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
                namespace greater_equal
                {
                    template<Invariant T>
                    class GreaterEqualPreciseImpl
                    {
                    public:
                        using ValueType = OriginType<T>;

                    public:
                        constexpr GreaterEqualPreciseImpl(void) = default;
                        constexpr GreaterEqualPreciseImpl(const GreaterEqualPreciseImpl& ano) = default;
                        constexpr GreaterEqualPreciseImpl(GreaterEqualPreciseImpl&& ano) noexcept = default;
                        constexpr GreaterEqualPreciseImpl& operator=(const GreaterEqualPreciseImpl& rhs) = default;
                        constexpr GreaterEqualPreciseImpl& operator=(GreaterEqualPreciseImpl&& RHS) noexcept = default;
                        constexpr ~GreaterEqualPreciseImpl(void) noexcept = default;

                    public:
                        inline constexpr const bool operator()(ArgCLRefType<ValueType> lhs, ArgCLRefType<ValueType> rhs) const noexcept
                        {
                            return lhs >= rhs;
                        }
                    };

                    template<Invariant T>
                        requires WithPrecision<T>&& Abs<T>
                    class GreaterEqualSignedImpreciseImpl
                    {
                    public:
                        using ValueType = OriginType<T>;

                    public:
                        constexpr GreaterEqualSignedImpreciseImpl(ArgCLRefType<ValueType> precision = PrecisionTrait<ValueType>::decimal_precision)
                            : _precision(precision) {}

                        template<typename = void>
                            requires ReferenceFaster<ValueType>&& std::movable<ValueType>
                        GreaterEqualSignedImpreciseImpl(ArgRRefType<ValueType> precision)
                            : _precision(precision) {}

                    public:
                        constexpr GreaterEqualSignedImpreciseImpl(const GreaterEqualSignedImpreciseImpl& ano) = default;
                        constexpr GreaterEqualSignedImpreciseImpl(GreaterEqualSignedImpreciseImpl&& ano) noexcept = default;
                        constexpr GreaterEqualSignedImpreciseImpl& operator=(const GreaterEqualSignedImpreciseImpl& rhs) = default;
                        constexpr GreaterEqualSignedImpreciseImpl& operator=(GreaterEqualSignedImpreciseImpl&& RHS) noexcept = default;
                        constexpr ~GreaterEqualSignedImpreciseImpl(void) noexcept = default;

                    public:
                        inline constexpr const bool operator()(ArgCLRefType<ValueType> lhs, ArgCLRefType<ValueType> rhs) const noexcept
                        {
                            return (lhs - rhs) >= -_precision;
                        }

                    private:
                        ValueType _precision;
                    };

                    template<Invariant T>
                        requires WithPrecision<T>
                    class GreaterEqualUnsignedImpreciseImpl
                    {
                    public:
                        using ValueType = OriginType<T>;

                    public:
                        constexpr GreaterEqualUnsignedImpreciseImpl(ArgCLRefType<ValueType> precision = PrecisionTrait<ValueType>::decimal_precision)
                            : _precision(precision) {}

                        template<typename = void>
                            requires ReferenceFaster<ValueType>&& std::movable<ValueType>
                        GreaterEqualUnsignedImpreciseImpl(ArgRRefType<ValueType> precision)
                            : _precision(move<ValueType>(precision)) {}

                    public:
                        constexpr GreaterEqualUnsignedImpreciseImpl(const GreaterEqualUnsignedImpreciseImpl& ano) = default;
                        constexpr GreaterEqualUnsignedImpreciseImpl(GreaterEqualUnsignedImpreciseImpl&& ano) noexcept = default;
                        constexpr GreaterEqualUnsignedImpreciseImpl& operator=(const GreaterEqualUnsignedImpreciseImpl& rhs) = default;
                        constexpr GreaterEqualUnsignedImpreciseImpl& operator=(GreaterEqualUnsignedImpreciseImpl&& rhs) noexcept = default;
                        constexpr ~GreaterEqualUnsignedImpreciseImpl(void) noexcept = default;

                    public:
                        inline constexpr const bool operator()(ArgCLRefType<ValueType> lhs, ArgCLRefType<ValueType> rhs) const noexcept
                        {
                            if (lhs < rhs)
                            {
                                return (rhs - lhs) <= _precision;
                            }
                            else
                            {
                                return true;
                            }
                        }

                    private:
                        ValueType _precision;
                    };
                };

                template<Invariant T>
                class GreaterEqual
                {
                    using PreciseImpl = greater_equal::GreaterEqualPreciseImpl<T>;
                    using SignedImpreciseImpl = greater_equal::GreaterEqualSignedImpreciseImpl<T>;
                    using UnsignedImpreciseImpl = greater_equal::GreaterEqualUnsignedImpreciseImpl<T>;
                    using Impl = std::variant<PreciseImpl, SignedImpreciseImpl, UnsignedImpreciseImpl>;

                public:
                    using ValueType = OriginType<T>;

                private:
                    static constexpr Impl impl(ArgCLRefType<ValueType> precision) noexcept
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

                    static Impl impl(ArgRRefType<ValueType> precision) noexcept
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
                    constexpr GreaterEqual(ArgCLRefType<ValueType> precision = ArithmeticTrait<ValueType>::zero)
                        : _impl(impl(precision)) {}

                    template<typename = void>
                        requires WithPrecision<ValueType>
                    constexpr GreaterEqual(ArgCLRefType<ValueType> precision = PrecisionTrait<ValueType>::decimal_precision)
                        : _impl(impl(precision)) {}

                    template<typename = void>
                        requires ReferenceFaster<ValueType>&& std::movable<ValueType>
                    GreaterEqual(ArgRRefType<ValueType> precision)
                        : _impl(impl(move<ValueType>(precision))) {}

                public:
                    constexpr GreaterEqual(const GreaterEqual& ano) = default;
                    constexpr GreaterEqual(GreaterEqual&& ano) noexcept = default;
                    constexpr GreaterEqual& operator=(const GreaterEqual& rhs) = default;
                    constexpr GreaterEqual& operator=(GreaterEqual&& rhs) noexcept = default;
                    constexpr ~GreaterEqual(void) noexcept = default;

                public:
                    inline constexpr const bool operator()(ArgCLRefType<ValueType> value) const noexcept
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
                class GreaterEqual<T>
                    : public greater_equal::GreaterEqualPreciseImpl<T>
                {
                    using Impl = greater_equal::GreaterEqualPreciseImpl<T>;

                public:
                    using typename Impl::ValueType;

                public:
                    constexpr GreaterEqual(void) = default;
                    constexpr GreaterEqual(ArgCLRefType<ValueType> _) = default;

                public:
                    constexpr GreaterEqual(const GreaterEqual& ano) = default;
                    constexpr GreaterEqual(GreaterEqual&& ano) noexcept = default;
                    constexpr GreaterEqual& operator=(const GreaterEqual& rhs) = default;
                    constexpr GreaterEqual& operator=(GreaterEqual&& rhs) noexcept = default;
                    constexpr ~GreaterEqual(void) noexcept = default;
                };

                template<Invariant T>
                    requires Imprecise<T>&& Signed<T>&& Abs<T>
                class GreaterEqual<T>
                    : public greater_equal::GreaterEqualSignedImpreciseImpl<T>
                {
                    using Impl = greater_equal::GreaterEqualSignedImpreciseImpl<T>;

                public:
                    using typename Impl::ValueType;

                public:
                    constexpr GreaterEqual(ArgCLRefType<ValueType> precision = PrecisionTrait<ValueType>::decimal_precision)
                        : Impl(precision) {}

                    template<typename = void>
                        requires ReferenceFaster<ValueType>&& std::movable<ValueType>
                    GreaterEqual(ArgRRefType<ValueType> precision)
                        : Impl(move<ValueType>(precision)) {}

                public:
                    constexpr GreaterEqual(const GreaterEqual& ano) = default;
                    constexpr GreaterEqual(GreaterEqual&& ano) noexcept = default;
                    constexpr GreaterEqual& operator=(const GreaterEqual& rhs) = default;
                    constexpr GreaterEqual& operator=(GreaterEqual&& rhs) noexcept = default;
                    constexpr ~GreaterEqual(void) noexcept = default;
                };

                template<Invariant T>
                    requires Imprecise<T>&& Unsigned<T>
                class GreaterEqual<T>
                    : public greater_equal::GreaterEqualUnsignedImpreciseImpl<T>
                {
                    using Impl = greater_equal::GreaterEqualUnsignedImpreciseImpl<T>;

                public:
                    using typename Impl::ValueType;

                public:
                    constexpr GreaterEqual(ArgCLRefType<ValueType> precision = PrecisionTrait<ValueType>::decimal_precision)
                        : Impl(precision) {}

                    template<typename = void>
                        requires ReferenceFaster<ValueType>&& std::movable<ValueType>
                    GreaterEqual(ArgRRefType<ValueType> precision)
                        : Impl(move<ValueType>(precision)) {}

                public:
                    constexpr GreaterEqual(const GreaterEqual& ano) = default;
                    constexpr GreaterEqual(GreaterEqual&& ano) noexcept = default;
                    constexpr GreaterEqual& operator=(const GreaterEqual& rhs) = default;
                    constexpr GreaterEqual& operator=(GreaterEqual&& rhs) noexcept = default;
                    constexpr ~GreaterEqual(void) noexcept = default;
                };
            };
        };
    };
};
