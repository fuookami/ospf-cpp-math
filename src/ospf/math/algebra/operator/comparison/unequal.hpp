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
                namespace unequal
                {
                    template<Invariant T>
                    class UnequalPreciseImpl
                    {
                    public:
                        using ValueType = OriginType<T>;

                    public:
                        constexpr UnequalPreciseImpl(void) = default;
                        constexpr UnequalPreciseImpl(const UnequalPreciseImpl& ano) = default;
                        constexpr UnequalPreciseImpl(UnequalPreciseImpl&& ano) noexcept = default;
                        constexpr UnequalPreciseImpl& operator=(const UnequalPreciseImpl& rhs) = default;
                        constexpr UnequalPreciseImpl& operator=(UnequalPreciseImpl&& rhs) noexcept = default;
                        constexpr ~UnequalPreciseImpl(void) noexcept = default;

                    public:
                        inline constexpr const bool operator()(ArgCLRefType<ValueType> lhs, ArgCLRefType<ValueType> rhs) const noexcept
                        {
                            return lhs != rhs;
                        }
                    };

                    template<Invariant T>
                        requires WithPrecision<T> && Abs<T>
                    class UnequalSignedImpreciseImpl
                    {
                    public:
                        using ValueType = OriginType<T>;

                    public:
                        constexpr UnequalSignedImpreciseImpl(ArgCLRefType<ValueType> precision = PrecisionTrait<ValueType>::decimal_precision)
                            : _precision(std::abs(precision)) {}

                        template<typename = void>
                            requires ReferenceFaster<ValueType> && std::movable<ValueType>
                        UnequalSignedImpreciseImpl(ArgRRefType<ValueType> precision)
                            : _precision(std::abs(move<ValueType>(precision))) {}

                    public:
                        constexpr UnequalSignedImpreciseImpl(const UnequalSignedImpreciseImpl& ano) = default;
                        constexpr UnequalSignedImpreciseImpl(UnequalSignedImpreciseImpl&& ano) noexcept = default;
                        constexpr UnequalSignedImpreciseImpl& operator=(const UnequalSignedImpreciseImpl& rhs) = default;
                        constexpr UnequalSignedImpreciseImpl& operator=(UnequalSignedImpreciseImpl&& rhs) noexcept = default;
                        constexpr ~UnequalSignedImpreciseImpl(void) = default;

                    public:
                        inline constexpr const bool operator()(ArgCLRefType<ValueType> lhs, ArgCLRefType<ValueType> rhs) const noexcept
                        {
                            return std::abs(lhs - rhs) > _precision;
                        }

                    private:
                        ValueType _precision;
                    };

                    template<Invariant T>
                        requires WithPrecision<T>
                    class UnequalUnsignedImpreciseImpl
                    {
                    public:
                        using ValueType = OriginType<T>;

                    public:
                        constexpr UnequalUnsignedImpreciseImpl(ArgCLRefType<ValueType> precision = PrecisionTrait<ValueType>::decimal_precision)
                            : _precision(std::abs(precision)) {}

                        template<typename = void>
                            requires ReferenceFaster<ValueType> && std::movable<ValueType>
                        UnequalUnsignedImpreciseImpl(ArgRRefType<ValueType> precision)
                            : _precision(std::abs(move<ValueType>(precision))) {}

                    public:
                        constexpr UnequalUnsignedImpreciseImpl(const UnequalUnsignedImpreciseImpl& ano) = default;
                        constexpr UnequalUnsignedImpreciseImpl(UnequalUnsignedImpreciseImpl&& ano) noexcept = default;
                        constexpr UnequalUnsignedImpreciseImpl& operator=(const UnequalUnsignedImpreciseImpl& rhs) = default;
                        constexpr UnequalUnsignedImpreciseImpl& operator=(UnequalUnsignedImpreciseImpl&& rhs) noexcept = default;
                        constexpr ~UnequalUnsignedImpreciseImpl(void) = default;

                    public:
                        inline constexpr const bool operator()(ArgCLRefType<ValueType> lhs, ArgCLRefType<ValueType> rhs) const noexcept
                        {
                            if (lhs < rhs)
                            {
                                return (rhs - lhs) > _precision;
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
                class Unequal
                {
                    using PreciseImpl = unequal::UnequalPreciseImpl<T>;
                    using SignedImpreciseImpl = unequal::UnequalSignedImpreciseImpl<T>;
                    using UnsignedImpreciseImpl = unequal::UnequalUnsignedImpreciseImpl<T>;
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
                    constexpr Unequal(ArgCLRefType<ValueType> precision = ArithmeticTrait<ValueType>::zero)
                        : _impl(impl(precision)) {}

                    template<typename = void>
                        requires WithPrecision<ValueType>
                    constexpr Unequal(ArgCLRefType<ValueType> precision = PrecisionTrait<ValueType>::decimal_precision)
                        : _impl(impl(precision)) {}

                    template<typename = void>
                        requires ReferenceFaster<ValueType> && std::movable<ValueType>
                    Unequal(ArgRRefType<ValueType> precision)
                        : _impl(impl(move<ValueType>(precision))) {}

                public:
                    constexpr Unequal(const Unequal& ano) = default;
                    constexpr Unequal(Unequal&& ano) noexcept = default;
                    constexpr Unequal& operator=(const Unequal& rhs) = default;
                    constexpr Unequal& operator=(Unequal&& rhs) noexcept = default;
                    constexpr ~Unequal(void) noexcept = default;

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
                class Unequal<T>
                    : public unequal::UnequalPreciseImpl<T>
                {
                    using Impl = unequal::UnequalPreciseImpl<T>;

                public:
                    using typename Impl::ValueType;

                public:
                    constexpr Unequal(void) = default;
                    constexpr Unequal(ArgCLRefType<ValueType> _) = default;

                public:
                    constexpr Unequal(const Unequal& ano) = default;
                    constexpr Unequal(Unequal&& ano) noexcept = default;
                    constexpr Unequal& operator=(const Unequal& rhs) = default;
                    constexpr Unequal& operator=(Unequal&& rhs) noexcept = default;
                    constexpr ~Unequal(void) noexcept = default;
                };

                template<Invariant T>
                    requires Imprecise<T> && Signed<T> && Abs<T>
                class Unequal<T>
                    : public unequal::UnequalSignedImpreciseImpl<T>
                {
                    using Impl = unequal::UnequalSignedImpreciseImpl<T>;

                public:
                    using typename Impl::ValueType;

                public:
                    constexpr Unequal(ArgCLRefType<ValueType> precision = PrecisionTrait<ValueType>::decimal_precision)
                        : Impl(precision) {}

                    template<typename = void>
                        requires ReferenceFaster<ValueType> && std::movable<ValueType>
                    Unequal(ArgRRefType<ValueType> precision)
                        : Impl(move<ValueType>(precision)) {}

                public:
                    constexpr Unequal(const Unequal& ano) = default;
                    constexpr Unequal(Unequal&& ano) noexcept = default;
                    constexpr Unequal& operator=(const Unequal& rhs) = default;
                    constexpr Unequal& operator=(Unequal&& rhs) noexcept = default;
                    constexpr ~Unequal(void) noexcept = default;
                };

                template<Invariant T>
                    requires Imprecise<T> && Unsigned<T>
                class Unequal<T>
                    : public unequal::UnequalUnsignedImpreciseImpl<T>
                {
                    using Impl = unequal::UnequalUnsignedImpreciseImpl<T>;

                public:
                    using typename Impl::ValueType;

                public:
                    constexpr Unequal(ArgCLRefType<ValueType> precision = PrecisionTrait<ValueType>::decimal_precision)
                        : Impl(precision) {}

                    template<typename = void>
                        requires ReferenceFaster<ValueType> && std::movable<ValueType>
                    Unequal(ArgRRefType<ValueType> precision)
                        : Impl(move<ValueType>(precision)) {}

                public:
                    constexpr Unequal(const Unequal& ano) = default;
                    constexpr Unequal(Unequal&& ano) noexcept = default;
                    constexpr Unequal& operator=(const Unequal& rhs) = default;
                    constexpr Unequal& operator=(Unequal&& rhs) noexcept = default;
                    constexpr ~Unequal(void) noexcept = default;
                };

                // todo: extern commom class template specialization
            };
        };
    };
};
