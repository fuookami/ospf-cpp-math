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
                namespace greater
                {
                    template<Invariant T>
                    class GreaterPreciseImpl
                    {
                    public:
                        using ValueType = OriginType<T>;

                    public:
                        constexpr GreaterPreciseImpl(void) = default;
                        constexpr GreaterPreciseImpl(const GreaterPreciseImpl& ano) = default;
                        constexpr GreaterPreciseImpl(GreaterPreciseImpl&& ano) noexcept = default;
                        constexpr GreaterPreciseImpl& operator=(const GreaterPreciseImpl& rhs) = default;
                        constexpr GreaterPreciseImpl& operator=(GreaterPreciseImpl&& RHS) noexcept = default;
                        constexpr ~GreaterPreciseImpl(void) noexcept = default;

                    public:
                        inline constexpr const bool operator()(CLRefType<ValueType> lhs, CLRefType<ValueType> rhs) const noexcept
                        {
                            return lhs > rhs;
                        }
                    };

                    template<Invariant T>
                        requires WithPrecision<T>&& Abs<T>
                    class GreaterSignedImpreciseImpl
                    {
                    public:
                        using ValueType = OriginType<T>;

                    public:
                        constexpr GreaterSignedImpreciseImpl(CLRefType<ValueType> precision = PrecisionTrait<ValueType>::decimal_precision)
                            : _precision(precision) {}

                        template<typename = void>
                            requires ReferenceFaster<ValueType>&& std::movable<ValueType>
                        GreaterSignedImpreciseImpl(RRefType<ValueType> precision)
                            : _precision(precision) {}

                    public:
                        constexpr GreaterSignedImpreciseImpl(const GreaterSignedImpreciseImpl& ano) = default;
                        constexpr GreaterSignedImpreciseImpl(GreaterSignedImpreciseImpl&& ano) noexcept = default;
                        constexpr GreaterSignedImpreciseImpl& operator=(const GreaterSignedImpreciseImpl& rhs) = default;
                        constexpr GreaterSignedImpreciseImpl& operator=(GreaterSignedImpreciseImpl&& RHS) noexcept = default;
                        constexpr ~GreaterSignedImpreciseImpl(void) noexcept = default;

                    public:
                        inline constexpr const bool operator()(CLRefType<ValueType> lhs, CLRefType<ValueType> rhs) const noexcept
                        {
                            return (lhs - rhs) > _precision;
                        }

                    private:
                        ValueType _precision;
                    };

                    template<Invariant T>
                        requires WithPrecision<T>
                    class GreaterUnsignedImpreciseImpl
                    {
                    public:
                        using ValueType = OriginType<T>;

                    public:
                        constexpr GreaterUnsignedImpreciseImpl(CLRefType<ValueType> precision = PrecisionTrait<ValueType>::decimal_precision)
                            : _precision(precision) {}

                        template<typename = void>
                            requires ReferenceFaster<ValueType>&& std::movable<ValueType>
                        GreaterUnsignedImpreciseImpl(RRefType<ValueType> precision)
                            : _precision(move<ValueType>(precision)) {}

                    public:
                        constexpr GreaterUnsignedImpreciseImpl(const GreaterUnsignedImpreciseImpl& ano) = default;
                        constexpr GreaterUnsignedImpreciseImpl(GreaterUnsignedImpreciseImpl&& ano) noexcept = default;
                        constexpr GreaterUnsignedImpreciseImpl& operator=(const GreaterUnsignedImpreciseImpl& rhs) = default;
                        constexpr GreaterUnsignedImpreciseImpl& operator=(GreaterUnsignedImpreciseImpl&& rhs) noexcept = default;
                        constexpr ~GreaterUnsignedImpreciseImpl(void) noexcept = default;

                    public:
                        inline constexpr const bool operator()(CLRefType<ValueType> lhs, CLRefType<ValueType> rhs) const noexcept
                        {
                            if (lhs < rhs)
                            {
                                return false;
                            }
                            else
                            {
                                return (lhs - rhs) > _precision;
                            }
                        }

                    private:
                        ValueType _precision;
                    };
                };

                template<Invariant T>
                class Greater
                {
                    using PreciseImpl = greater::GreaterPreciseImpl<T>;
                    using SignedImpreciseImpl = greater::GreaterSignedImpreciseImpl<T>;
                    using UnsignedImpreciseImpl = greater::GreaterUnsignedImpreciseImpl<T>;
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
                    constexpr Greater(CLRefType<ValueType> precision = ArithmeticTrait<ValueType>::zero)
                        : _impl(impl(precision)) {}

                    template<typename = void>
                        requires WithPrecision<ValueType>
                    constexpr Greater(CLRefType<ValueType> precision = PrecisionTrait<ValueType>::decimal_precision)
                        : _impl(impl(precision)) {}

                    template<typename = void>
                        requires ReferenceFaster<ValueType>&& std::movable<ValueType>
                    Greater(RRefType<ValueType> precision)
                        : _impl(impl(move<ValueType>(precision))) {}

                public:
                    constexpr Greater(const Greater& ano) = default;
                    constexpr Greater(Greater&& ano) noexcept = default;
                    constexpr Greater& operator=(const Greater& rhs) = default;
                    constexpr Greater& operator=(Greater&& rhs) noexcept = default;
                    constexpr ~Greater(void) noexcept = default;

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
                class Greater<T>
                    : public greater::GreaterPreciseImpl<T>
                {
                    using Impl = greater::GreaterPreciseImpl<T>;

                public:
                    using typename Impl::ValueType;

                public:
                    constexpr Greater(void) = default;
                    constexpr Greater(CLRefType<ValueType> _) = default;

                public:
                    constexpr Greater(const Greater& ano) = default;
                    constexpr Greater(Greater&& ano) noexcept = default;
                    constexpr Greater& operator=(const Greater& rhs) = default;
                    constexpr Greater& operator=(Greater&& rhs) noexcept = default;
                    constexpr ~Greater(void) noexcept = default;
                };

                template<Invariant T>
                    requires Imprecise<T>&& Signed<T>&& Abs<T>
                class Greater<T>
                    : public greater::GreaterSignedImpreciseImpl<T>
                {
                    using Impl = greater::GreaterSignedImpreciseImpl<T>;

                public:
                    using typename Impl::ValueType;

                public:
                    constexpr Greater(CLRefType<ValueType> precision = PrecisionTrait<ValueType>::decimal_precision)
                        : Impl(precision) {}

                    template<typename = void>
                        requires ReferenceFaster<ValueType>&& std::movable<ValueType>
                    Greater(RRefType<ValueType> precision)
                        : Impl(move<ValueType>(precision)) {}

                public:
                    constexpr Greater(const Greater& ano) = default;
                    constexpr Greater(Greater&& ano) noexcept = default;
                    constexpr Greater& operator=(const Greater& rhs) = default;
                    constexpr Greater& operator=(Greater&& rhs) noexcept = default;
                    constexpr ~Greater(void) noexcept = default;
                };

                template<Invariant T>
                    requires Imprecise<T>&& Unsigned<T>
                class Greater<T>
                    : public greater::GreaterUnsignedImpreciseImpl<T>
                {
                    using Impl = greater::GreaterUnsignedImpreciseImpl<T>;

                public:
                    using typename Impl::ValueType;

                public:
                    constexpr Greater(CLRefType<ValueType> precision = PrecisionTrait<ValueType>::decimal_precision)
                        : Impl(precision) {}

                    template<typename = void>
                        requires ReferenceFaster<ValueType>&& std::movable<ValueType>
                    Greater(RRefType<ValueType> precision)
                        : Impl(move<ValueType>(precision)) {}

                public:
                    constexpr Greater(const Greater& ano) = default;
                    constexpr Greater(Greater&& ano) noexcept = default;
                    constexpr Greater& operator=(const Greater& rhs) = default;
                    constexpr Greater& operator=(Greater&& rhs) noexcept = default;
                    constexpr ~Greater(void) noexcept = default;
                };
            };
        };
    };
};
