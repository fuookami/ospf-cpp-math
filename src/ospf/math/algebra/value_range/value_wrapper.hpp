#pragma once

#include <ospf/concepts/with_default.hpp>
#include <ospf/exception.hpp>
#include <ospf/math/algebra/concepts/real_number.hpp>
#include <ospf/type_family.hpp>
#include <variant>

namespace ospf
{
    inline namespace math
    {
        inline namespace algebra
        {
            namespace value_range
            {
                template<Arithmetic T>
                class ValueWrapper
                {
                    using Variant = std::variant<OriginType<T>, Infinity, NegativeInfinity>;

                public:
                    using ValueType = OriginType<T>;

                private:
                    inline Variant wrap(ArgCLRefType<ValueType> value)
                    {
                        if constexpr (RealNumber<ValueType>)
                        {
                            if (RealNumberTrait<ValueType>::is_inf(value))
                            {
                                return Variant{ std::in_place_index<1_uz>, inf };
                            }
                            else if (RealNumberTrait<ValueType>::is_neg_inf(value))
                            {
                                return Variant{ std::in_place_index<2_uz>, neg_inf };
                            }
                            else if (RealNumberTrait<ValueType>::is_nan(value))
                            {
                                throw OSPFException{ OSPFErrCode::ApplicationError, "invalid argument NaN for value range" };
                                return Variant{ std::in_place_index<1_uz>, inf };
                            }
                            else
                            {
                                return Variant{ std::in_place_index<0_uz>, value };
                            }
                        }
                        else
                        {
                            return Variant{ std::in_place_index<0_uz>, value };
                        }
                    }

                    template<typename = void>
                        requires ReferenceFaster<ValueType> && std::movable<ValueType>
                    inline Variant wrap(ArgRRefType<ValueType> value)
                    {
                        if constexpr (RealNumber<ValueType>)
                        {
                            if (RealNumberTrait<ValueType>::is_inf(value))
                            {
                                return Variant{ std::in_place_index<1_uz>, inf };
                            }
                            else if (RealNumberTrait<ValueType>::is_neg_inf(value))
                            {
                                return Variant{ std::in_place_index<2_uz>, neg_inf };
                            }
                            else if (RealNumberTrait<ValueType>::is_nan(value))
                            {
                                throw OSPFException{ OSPFErrCode::ApplicationError, "invalid argument NaN for value range" };
                                return Variant{ std::in_place_index<1_uz>, inf };
                            }
                            else
                            {
                                return Variant{ std::in_place_index<0_uz>, move<ValueType>(value) };
                            }
                        }
                        else
                        {
                            return Variant{ std::in_place_index<0_uz>, move<ValueType>(value) };
                        }
                    }

                public:
                    template<typename = void>
                        requires WithDefault<ValueType>
                    constexpr ValueWrapper(void)
                        : ValueWrapper(DefaultValue<ValueType>::value()) {}

                    constexpr ValueWrapper(ArgCLRefType<ValueType> value)
                        : _variant(wrap(value)) {}

                    template<typename = void>
                        requires ReferenceFaster<ValueType> && std::movable<ValueType>
                    constexpr ValueWrapper(ArgRRefType<ValueType> value)
                        : _variant(wrap(move<ValueType>(value))) {}

                    constexpr ValueWrapper(const Infinity _)
                        : _variant(std::in_place_index<1_uz>, inf) {}

                    constexpr ValueWrapper(const NegativeInfinity _)
                        : _variant(std::in_place_index<2_uz>, neg_inf) {}

                public:
                    constexpr ValueWrapper(const ValueWrapper& ano) = default;
                    constexpr ValueWrapper(ValueWrapper&& ano) noexcept = default;
                    constexpr ValueWrapper& operator=(const ValueWrapper& rhs) = default;
                    constexpr ValueWrapper& operator=(ValueWrapper&& rhs) noexcept = default;
                    constexpr ~ValueWrapper(void) noexcept = default;

                public:
                    inline operator const Variant&(void) const noexcept
                    {
                        return _variant;
                    }

                public:
                    inline ValueWrapper operator+(const ValueWrapper& value) const noexcept
                    {

                    }

                    inline ValueWrapper& operator+=(const ValueWrapper& value) const noexcept
                    {

                    }

                    inline ValueWrapper operator+(ArgCLRefType<ValueType> value) const noexcept
                    {

                    }

                    inline ValueWrapper& operator+=(ArgCLRefType<ValueType> value) const noexcept
                    {

                    }

                    inline ValueWrapper operator-(const ValueWrapper& value) const noexcept
                    {

                    }

                    inline ValueWrapper& operator-=(const ValueWrapper& value) const noexcept
                    {

                    }

                    inline ValueWrapper operator-(ArgCLRefType<ValueType> value) const noexcept
                    {

                    }

                    inline ValueWrapper& operator-=(ArgCLRefType<ValueType> value) const noexcept
                    {

                    }

                    inline ValueWrapper operator*(const ValueWrapper& value) const noexcept
                    {

                    }

                    inline ValueWrapper& operator*=(const ValueWrapper& value) const noexcept
                    {

                    }

                    inline ValueWrapper operator*(ArgCLRefType<ValueType> value) const noexcept
                    {

                    }

                    inline ValueWrapper& operator*=(ArgCLRefType<ValueType> value) const noexcept
                    {

                    }

                    inline ValueWrapper operator/(const ValueWrapper& value) const noexcept
                    {

                    }

                    inline ValueWrapper& operator/=(const ValueWrapper& value) const noexcept
                    {

                    }

                    inline ValueWrapper operator/(ArgCLRefType<ValueType> value) const noexcept
                    {

                    }

                    inline ValueWrapper& operator/=(ArgCLRefType<ValueType> value) const noexcept
                    {

                    }

                public:
                    inline const bool operator==(const ValueWrapper& value) const noexcept
                    {
                        if (_variant.index() == 0_uz && _variant.index() == value._variant.index())
                        {
                            return std::get<0_uz>(_variant) == std::get<0_uz>(value._variant);
                        }
                        else if (_variant.index() == 1_uz && _variant.index() == value._variant.index())
                        {
                            return true;
                        }
                        else if (_variant.index() == 2_uz && _variant.index() == value._variant.index())
                        {
                            return true;
                        }
                        else
                        {
                            return false;
                        }
                    }

                    inline const bool operator!=(const ValueWrapper& value) const noexcept
                    {
                        if (_variant.index() == 0_uz && _variant.index() == value._variant.index())
                        {
                            return std::get<0_uz>(_variant) != std::get<0_uz>(value._variant);
                        }
                        else if (_variant.index() == 1_uz && _variant.index() == value._variant.index())
                        {
                            return false;
                        }
                        else if (_variant.index() == 2_uz && _variant.index() == value._variant.index())
                        {
                            return false;
                        }
                        else
                        {
                            return true;
                        }
                    }

                    inline const bool operator==(ArgCLRefType<ValueType> value) const noexcept
                    {
                        if constexpr (RealNumber<ValueType>)
                        {
                            return std::visit([&value](const auto& this_value)
                                {
                                    using ThisValueType = OriginType<decltype(this_value)>;
                                    if constexpr (DecaySameAs<ThisValueType, Infinity>)
                                    {
                                        return RealNumberTrait<ValueType>::is_inf(value);
                                    }
                                    else if constexpr (DecaySameAs<ThisValueType, NegativeInfinity>)
                                    {
                                        return RealNumberTrait<ValueType>::is_neg_inf(value);
                                    }
                                    else
                                    {
                                        return this_value == value;
                                    }
                                }, _variant);
                        }
                        else
                        {
                            return std::visit([&value](const auto& this_value)
                                {
                                    using ThisValueType = OriginType<decltype(this_value)>;
                                    if constexpr (DecaySameAs<ThisValueType, Infinity, NegativeInfinity>)
                                    {
                                        return false;
                                    }
                                    else
                                    {
                                        return this_value == value;
                                    }
                                }, _variant);
                        }
                    }

                    inline const bool operator!=(ArgCLRefType<ValueType> value) const noexcept
                    {
                        if constexpr (RealNumber<ValueType>)
                        {
                            return std::visit([&value](const auto& this_value)
                                {
                                    using ThisValueType = OriginType<decltype(this_value)>;
                                    if constexpr (DecaySameAs<ThisValueType, Infinity>)
                                    {
                                        return !RealNumberTrait<ValueType>::is_inf(value);
                                    }
                                    else if constexpr (DecaySameAs<ThisValueType, NegativeInfinity>)
                                    {
                                        return !RealNumberTrait<ValueType>::is_neg_inf(value);
                                    }
                                    else
                                    {
                                        return this_value != value;
                                    }
                                }, _variant);
                        }
                        else
                        {
                            return std::visit([&value](const auto& this_value)
                                {
                                    using ThisValueType = OriginType<decltype(this_value)>;
                                    if constexpr (DecaySameAs<ThisValueType, Infinity, NegativeInfinity>)
                                    {
                                        return true;
                                    }
                                    else
                                    {
                                        return this_value != value;
                                    }
                                }, _variant);
                        }
                    }

                public:
                    inline const bool operator<(const ValueWrapper& value) const noexcept
                    {
                        return std::visit([&value](const auto& lhs)
                            {
                                using LhsValueType = OriginType<decltype(lhs)>;
                                if constexpr (DecaySameAs<LhsValueType, Infinity>)
                                {
                                    return false;
                                }
                                else if constexpr (DecaySameAs<LhsValueType, NegativeInfinity>)
                                {
                                    return std::visit([](const auto& rhs)
                                        {
                                            using RhsValueType = OriginType<decltype(lhs)>;
                                            if constexpr (DecaySameAs<RhsValueType, NegativeInfinity>)
                                            {
                                                return false;
                                            }
                                            else
                                            {
                                                return true;
                                            }
                                        }, value._variant);
                                }
                                else
                                {
                                    return std::visit([](const auto& rhs)
                                        {
                                            using RhsValueType = OriginType<decltype(rhs)>;
                                            if constexpr (DecaySameAs<RhsValueType, Infinity>)
                                            {
                                                return true;
                                            }
                                            else if constexpr (DecaySameAs<RhsValueType, NegativeInfinity>)
                                            {
                                                return false;
                                            }
                                            else
                                            {
                                                return lhs < rhs;
                                            }
                                        }, value._variant);
                                }
                            }, _variant);
                    }

                    inline const bool operator<=(const ValueWrapper& value) const noexcept
                    {
                        return std::visit([&value](const auto& lhs) 
                            {
                                using LhsValueType = OriginType<decltype(lhs)>;
                                if constexpr (DecaySameAs<LhsValueType, Infinity>)
                                {
                                    return std::visit([](const auto& rhs)
                                        {
                                            using RhsValueType = OriginType<decltype(rhs)>;
                                            if constexpr (DecaySameAs<RhsValueType, Infinity>)
                                            {
                                                return true;
                                            }
                                            else
                                            {
                                                return false;
                                            }
                                        }, value._variant);
                                }
                                else if constexpr (DecaySameAs<LhsValueType, NegativeInfinity>)
                                {
                                    return true;
                                }
                                else
                                {
                                    return std::visit([](const auto& rhs)
                                        {
                                            using RhsValueType = OriginType<decltype(rhs)>;
                                            if constexpr (DecaySameAs<RhsValueType, Infinity>)
                                            {
                                                return true;
                                            }
                                            else if constexpr (DecaySameAs<RhsValueType, NegativeInfinity>)
                                            {
                                                return false;
                                            }
                                            else
                                            {
                                                return lhs <= rhs;
                                            }
                                        }, value._variant);
                                }
                            }, _variant);
                    }

                    inline const bool operator>(const ValueWrapper& value) const noexcept
                    {
                        return std::visit([&value](const auto& lhs) 
                            {
                                using LhsValueType = OriginType<decltype(lhs)>;
                                if constexpr (DecaySameAs<LhsValueType, Infinity>)
                                {
                                    return std::visit([](const auto& rhs)
                                        {
                                            using RhsValueType = OriginType<decltype(rhs)>;
                                            if constexpr (DecaySameAs<RhsValueType, Infinity>)
                                            {
                                                return false;
                                            }
                                            else
                                            {
                                                return true;
                                            }
                                        }, value._variant);
                                }
                                else if constexpr (DecaySameAs<LhsValueType, NegativeInfinity>)
                                {
                                    return false;
                                }
                                else
                                {
                                    return std::visit([](const auto& rhs)
                                        {
                                            using RhsValueType = OriginType<decltype(rhs)>;
                                            if constexpr (DecaySameAs<RhsValueType, Infinity>)
                                            {
                                                return false;
                                            }
                                            else if constexpr (DecaySameAs<RhsValueType, NegativeInfinity>)
                                            {
                                                return true;
                                            }
                                            else
                                            {
                                                return lhs > rhs;
                                            }
                                        }, value._variant);
                                }
                            }, _variant);
                    }

                    inline const bool operator>=(const ValueWrapper& value) const noexcept
                    {
                        return std::visit([&value](const auto& lhs) 
                            {
                                using LhsValueType = OriginType<decltype(lhs)>;
                                if constexpr (DecaySameAs<LhsValueType, Infinity>)
                                {
                                    return true;
                                }
                                else if constexpr (DecaySameAs<LhsValueType, NegativeInfinity>)
                                {
                                    return std::visit([](const auto& rhs)
                                        {
                                            using RhsValueType = OriginType<decltype(rhs)>;
                                            if constexpr (DecaySameAs<RhsValueType, NegativeInfinity>)
                                            {
                                                return true;
                                            }
                                            else
                                            {
                                                return false;
                                            }
                                        }, value._variant);
                                }
                                else
                                {
                                    return std::visit([](const auto& rhs)
                                        {
                                            using RhsValueType = OriginType<decltype(rhs)>;
                                            if constexpr (DecaySameAs<RhsValueType, Infinity>)
                                            {
                                                return false;
                                            }
                                            else if constexpr (DecaySameAs<RhsValueType, NegativeInfinity>)
                                            {
                                                return true;
                                            }
                                            else
                                            {
                                                return lhs >= rhs;
                                            }
                                        }, value._variant);
                                }
                            }, _variant);
                    }

                    inline const bool operator<(ArgCLRefType<ValueType> value) const noexcept
                    {
                        if constexpr (RealNumber<ValueType>)
                        {
                            return std::visit([&value](const auto& this_value)
                                {
                                    using ThisValueType = OriginType<decltype(this_value)>;
                                    if constexpr (DecaySameAs<ThisValueType, Infinity>)
                                    {
                                        return false
                                    }
                                    else if constexpr (DecaySameAs<ThisValueType, NegativeInfinity>)
                                    {
                                        return !RealNumberTrait<ValueType>::is_neg_inf(value);
                                    }
                                    else
                                    {
                                        return this_value < value;
                                    }
                                }, _variant);
                        }
                        else
                        {
                            return std::visit([&value](const auto& this_value)
                                {
                                    using ThisValueType = OriginType<decltype(this_value)>;
                                    if constexpr (DecaySameAs<ThisValueType, Infinity>)
                                    {
                                        return false;
                                    }
                                    else if constexpr (DecaySameAs<ThisValueType, NegativeInfinity>)
                                    {
                                        return true;
                                    }
                                    else
                                    {
                                        return this_value < value;
                                    }
                                }, _variant);
                        }
                    }

                    inline const bool operator<=(ArgCLRefType<ValueType> value) const noexcept
                    {
                        if constexpr (RealNumber<ValueType>)
                        {
                            return std::visit([&value](const auto& this_value)
                                {
                                    using ThisValueType = OriginType<decltype(this_value)>;
                                    if constexpr (DecaySameAs<ThisValueType, Infinity>)
                                    {
                                        return RealNumberTrait<ValueType>::inf(value);
                                    }
                                    else if constexpr (DecaySameAs<ThisValueType, NegativeInfinity>)
                                    {
                                        return !RealNumberTrait<ValueType>::is_neg_inf(value);
                                    }
                                    else
                                    {
                                        return this_value <= value;
                                    }
                                }, _variant);
                        }
                        else
                        {
                            return std::visit([&value](const auto& this_value)
                                {
                                    using ThisValueType = OriginType<decltype(this_value)>;
                                    if constexpr (DecaySameAs<ThisValueType, Infinity>)
                                    {
                                        return false;
                                    }
                                    else if constexpr (DecaySameAs<ThisValueType, NegativeInfinity>)
                                    {
                                        return true;
                                    }
                                    else
                                    {
                                        return this_value <= value;
                                    }
                                }, _variant);
                        }
                    }

                    inline const bool operator>(ArgCLRefType<ValueType> value) const noexcept
                    {
                        if constexpr (RealNumber<ValueType>)
                        {
                            return std::visit([&value](const auto& this_value)
                                {
                                    using ThisValueType = OriginType<decltype(this_value)>;
                                    if constexpr (DecaySameAs<ThisValueType, Infinity>)
                                    {
                                        return !RealNumberTrait<ValueType>::is_inf(value);
                                    }
                                    else if constexpr (DecaySameAs<ThisValueType, NegativeInfinity>)
                                    {
                                        return RealNumberTrait<ValueType>::is_neg_inf(value);
                                    }
                                    else
                                    {
                                        return this_value > value;
                                    }
                                }, _variant);
                        }
                        else
                        {
                            return std::visit([&value](const auto& this_value)
                                {
                                    using ThisValueType = OriginType<decltype(this_value)>;
                                    if constexpr (DecaySameAs<ThisValueType, Infinity>)
                                    {
                                        return true;
                                    }
                                    else if constexpr (DecaySameAs<ThisValueType, NegativeInfinity>)
                                    {
                                        return false;
                                    }
                                    else
                                    {
                                        return this_value > value;
                                    }
                                }, _variant);
                        }
                    }

                    inline const bool operator>=(ArgCLRefType<ValueType> value) const noexcept
                    {
                         if constexpr (RealNumber<ValueType>)
                        {
                            return std::visit([&value](const auto& this_value)
                                {
                                    using ThisValueType = OriginType<decltype(this_value)>;
                                    if constexpr (DecaySameAs<ThisValueType, Infinity>)
                                    {
                                        return !RealNumberTrait<ValueType>::is_inf(value);
                                    }
                                    else if constexpr (DecaySameAs<ThisValueType, NegativeInfinity>)
                                    {
                                        return RealNumberTrait<ValueType>::is_neg_inf(value);
                                    }
                                    else
                                    {
                                        return this_value >= value;
                                    }
                                }, _variant);
                        }
                        else
                        {
                            return std::visit([&value](const auto& this_value)
                                {
                                    using ThisValueType = OriginType<decltype(this_value)>;
                                    if constexpr (DecaySameAs<ThisValueType, Infinity>)
                                    {
                                        return true;
                                    }
                                    else if constexpr (DecaySameAs<ThisValueType, NegativeInfinity>)
                                    {
                                        return false;
                                    }
                                    else
                                    {
                                        return this_value >= value;
                                    }
                                }, _variant);
                        }
                    }

                public:
                    inline std::compare_three_way_result_t<ValueType> operator<=>(const ValueWrapper& value) const noexcept
                    {
                        using RetType = std::compare_three_way_result_t<ValueType>;

                        return std::visit([&value](const auto& lhs_value) -> RetType 
                            {
                                using LhsValueType = OriginType<decltype(lhs_value)>;
                                if constexpr (DecaySameAs<LhsValueType, Infinity>)
                                {
                                    return std::visit([](const auto& rhs_value) -> RetType
                                        {
                                            using RhsValueType = OriginType<decltype(rhs_value)>;
                                            if constexpr (DecaySameAs<RhsValueType, Infinity>)
                                            {
                                                return std::strong_ordering::equal;
                                            }
                                            else
                                            {
                                                return std::strong_ordering::greater;
                                            }
                                        }, value._variant);
                                }
                                else if constexpr (DecaySameAs<LhsValueType, NegativeInfinity>)
                                {
                                    return std::visit([](const auto& rhs_value) -> RetType
                                        {
                                            using RhsValueType = OriginType<decltype(rhs_value)>;
                                            if constexpr (DecaySameAs<RhsValueType, NegativeInfinity>)
                                            {
                                                return std::strong_ordering::equal;
                                            }
                                            else
                                            {
                                                return std::strong_ordering::less;
                                            }
                                        }, value._variant);
                                }
                                else
                                {
                                     return std::visit([&lhs_value](const auto& rhs_value) -> RetType
                                        {
                                            using RhsValueType = OriginType<decltype(rhs_value)>;
                                            if constexpr (DecaySameAs<RhsValueType, Infinity>)
                                            {
                                                return std::strong_ordering::less;
                                            }
                                            if constexpr (DecaySameAs<RhsValueType, NegativeInfinity>)
                                            {
                                                return std::strong_ordering::greater;
                                            }
                                            else
                                            {
                                                return lhs_value <=> rhs_value;
                                            }
                                        }, value._variant);
                                }
                            }, _variant);
                    }

                    inline std::compare_three_way_result_t<ValueType> operator<=>(const ValueType& value) const noexcept
                    {
                        using RetType = std::compare_three_way_result_t<ValueType>;

                        if constexpr (RealNumber<ValueType>)
                        {
                            return std::visit([&value](const auto& this_value) -> RetType
                                {
                                    using ThisValueType = OriginType<decltype(this_value)>;
                                    if constexpr (DecaySameAs<ThisValueType, Infinity>)
                                    {
                                        return RealNumberTrait<ValueType>::is_inf(value) ? std::strong_ordering::equal : std::strong_ordering::greater;
                                    }
                                    else if constexpr (DecaySameAs<ThisValueType, NegativeInfinity>)
                                    {
                                        return RealNumberTrait<ValueType>::is_neg_inf(value) ? std::strong_ordering::equal : std::strong_ordering::less;
                                    }
                                    else
                                    {
                                        return this_value <=> value;
                                    }
                                }, _variant);
                        }
                        else
                        {
                            return std::visit([&value](const auto& this_value) -> RetType
                                {
                                    using ThisValueType = OriginType<decltype(this_value)>;
                                    if constexpr (DecaySameAs<ThisValueType, Infinity>)
                                    {
                                        return std::strong_ordering::greater;
                                    }
                                    else if constexpr (DecaySameAs<ThisValueType, NegativeInfinity>)
                                    {
                                        return std::strong_ordering::less;
                                    }
                                    else
                                    {
                                        return this_value <=> value;
                                    }
                                }, _variant);
                        }
                    }

                private:
                    Variant _variant;
                };

                extern template class ValueWrapper<i8>;
                extern template class ValueWrapper<u8>;
                extern template class ValueWrapper<i16>;
                extern template class ValueWrapper<u16>;
                extern template class ValueWrapper<i32>;
                extern template class ValueWrapper<u32>;
                extern template class ValueWrapper<i64>;
                extern template class ValueWrapper<u64>;
                extern template class ValueWrapper<i128>;
                extern template class ValueWrapper<u128>;
                extern template class ValueWrapper<i256>;
                extern template class ValueWrapper<u256>;
                extern template class ValueWrapper<i512>;
                extern template class ValueWrapper<u512>;
                extern template class ValueWrapper<i1024>;
                extern template class ValueWrapper<u1024>;
                extern template class ValueWrapper<bigint>;

                extern template class ValueWrapper<f32>;
                extern template class ValueWrapper<f64>;
                extern template class ValueWrapper<f128>;
                extern template class ValueWrapper<f256>;
                extern template class ValueWrapper<f512>;
                extern template class ValueWrapper<dec50>;
                extern template class ValueWrapper<dec100>;
            };
        };
    };
};

template<typename T>
inline ospf::RetType<ospf::value_range::ValueWrapper<T>> operator+(const T& lhs, const ospf::value_range::ValueWrapper<T>& rhs) noexcept
{

}

template<typename T>
inline ospf::RetType<ospf::value_range::ValueWrapper<T>> operator-(const T& lhs, const ospf::value_range::ValueWrapper<T>& rhs) noexcept
{

}

template<typename T>
inline ospf::RetType<ospf::value_range::ValueWrapper<T>> operator*(const T& lhs, const ospf::value_range::ValueWrapper<T>& rhs) noexcept
{

}

template<typename T>
inline ospf::RetType<ospf::value_range::ValueWrapper<T>> operator/(const T& lhs, const ospf::value_range::ValueWrapper<T>& rhs) noexcept
{

}

template<typename T>
inline const bool operator==(const T& lhs, const ospf::value_range::ValueWrapper<T>& rhs) noexcept
{
    if constexpr (ospf::RealNumber<T>)
    {
        return std::visit([&lhs](const auto& rhs_value)
            {
                using RhsValueType = ospf::OriginType<decltype(rhs_value)>;
                if constexpr (ospf::DecaySameAs<RhsValueType, ospf::Infinity>)
                {
                    return ospf::RealNumberTrait<T>::is_inf(lhs);
                }
                else if constexpr (ospf::DecaySameAs<RhsValueType, ospf::NegativeInfinity>)
                {
                    return ospf::RealNumberTrait<T>::is_neg_inf(lhs);
                }
                else
                {
                    return lhs == rhs_value;
                }
            }, rhs);
    }
    else
    {
        return std::visit([&lhs](const auto& rhs_value)
            {
                using RhsValueType = ospf::OriginType<decltype(rhs_value)>;
                if constexpr (ospf::DecaySameAs<RhsValueType, ospf::Infinity, ospf::NegativeInfinity>)
                {
                    return false;
                }
                else
                {
                    return lhs == rhs_value;
                }
            }, rhs);
    }
}

template<typename T>
inline const bool operator!=(const T& lhs, const ospf::value_range::ValueWrapper<T>& rhs) noexcept
{
    if constexpr (ospf::RealNumber<T>)
    {
        return std::visit([&lhs](const auto& rhs_value)
            {
                using RhsValueType = ospf::OriginType<decltype(rhs_value)>;
                if constexpr (ospf::DecaySameAs<RhsValueType, ospf::Infinity>)
                {
                    return !ospf::RealNumberTrait<T>::is_inf(lhs);
                }
                else if constexpr (ospf::DecaySameAs<RhsValueType, ospf::NegativeInfinity>)
                {
                    return !ospf::RealNumberTrait<T>::is_neg_inf(lhs);
                }
                else
                {
                    return lhs != rhs_value;
                }
            }, rhs);
    }
    else
    {
        return std::visit([&lhs](const auto& rhs_value)
            {
                using RhsValueType = ospf::OriginType<decltype(rhs_value)>;
                if constexpr (ospf::DecaySameAs<RhsValueType, ospf::Infinity, ospf::NegativeInfinity>)
                {
                    return true;
                }
                else
                {
                    return lhs != rhs_value;
                }
            }, rhs);
    }
}

template<ospf::Arithmetic T>
inline const bool operator<(const T& lhs, const ospf::value_range::ValueWrapper<T>& rhs) noexcept
{
    if constexpr (ospf::RealNumber<T>)
    {
        return std::visit([&lhs](const auto& rhs_value) 
            {
                using RhsValueType = ospf::OriginType<decltype(rhs_value)>;
                if constexpr (ospf::DecaySameAs<RhsValueType, ospf::Infinity>)
                {
                    return !ospf::RealNumberTrait<T>::is_inf(lhs);
                }
                else if constexpr (ospf::DecaySameAs<RhsValueType, ospf::NegativeInfinity>)
                {
                    return false;
                }
                else
                {
                    return lhs < rhs_value;
                }
            }, rhs);
    }
    else
    {
        return std::visit([&lhs](const auto& rhs_value)
            {
                using RhsValueType = ospf::OriginType<decltype(rhs_value)>;
                if constexpr (ospf::DecaySameAs<RhsValueType, ospf::Infinity>)
                {
                    return true;
                }
                else if constexpr (ospf::DecaySameAs<RhsValueType, ospf::NegativeInfinity>)
                {
                    return false;
                }
                else
                {
                    return lhs < rhs_value;
                }
            }, rhs);
    }
}

template<ospf::Arithmetic T>
inline const bool operator<=(const T& lhs, const ospf::value_range::ValueWrapper<T>& rhs) noexcept
{
    if constexpr (ospf::RealNumber<T>)
    {
        return std::visit([&lhs](const auto& rhs_value) 
            {
                using RhsValueType = ospf::OriginType<decltype(rhs_value)>;
                if constexpr (ospf::DecaySameAs<RhsValueType, ospf::Infinity>)
                {
                    return !ospf::RealNumberTrait<T>::is_inf(lhs);
                }
                else if constexpr (ospf::DecaySameAs<RhsValueType, ospf::NegativeInfinity>)
                {
                    return ospf::RealNumberTrait<T>::is_neg_inf(lhs);
                }
                else
                {
                    return lhs <= rhs_value;
                }
            }, rhs);
    }
    else
    {
        return std::visit([&lhs](const auto& rhs_value)
            {
                using RhsValueType = ospf::OriginType<decltype(rhs_value)>;
                if constexpr (ospf::DecaySameAs<RhsValueType, ospf::Infinity>)
                {
                    return true;
                }
                else if constexpr (ospf::DecaySameAs<RhsValueType, ospf::NegativeInfinity>)
                {
                    return false;
                }
                else
                {
                    return lhs <= rhs_value;
                }
            }, rhs);
    }
}

template<ospf::Arithmetic T>
inline const bool operator>(const T& lhs, const ospf::value_range::ValueWrapper<T>& rhs) noexcept
{
    if constexpr (ospf::RealNumber<T>)
    {
        return std::visit([&lhs](const auto& rhs_value) 
            {
                using RhsValueType = ospf::OriginType<decltype(rhs_value)>;
                if constexpr (ospf::DecaySameAs<RhsValueType, ospf::Infinity>)
                {
                    return false;
                }
                else if constexpr (ospf::DecaySameAs<RhsValueType, ospf::NegativeInfinity>)
                {
                    return !ospf::RealNumberTrait<T>::is_neg_inf(lhs);
                }
                else
                {
                    return lhs > rhs_value;
                }
            }, rhs);
    }
    else
    {
        return std::visit([&lhs](const auto& rhs_value)
            {
                using RhsValueType = ospf::OriginType<decltype(rhs_value)>;
                if constexpr (ospf::DecaySameAs<RhsValueType, ospf::Infinity>)
                {
                    return false;
                }
                else if constexpr (ospf::DecaySameAs<RhsValueType, ospf::NegativeInfinity>)
                {
                    return true;
                }
                else
                {
                    return lhs > rhs_value;
                }
            }, rhs);
    }
}

template<ospf::Arithmetic T>
inline const bool operator>=(const T& lhs, const ospf::value_range::ValueWrapper<T>& rhs) noexcept
{
    if constexpr (ospf::RealNumber<T>)
    {
        return std::visit([&lhs](const auto& rhs_value) 
            {
                using RhsValueType = ospf::OriginType<decltype(rhs_value)>;
                if constexpr (ospf::DecaySameAs<RhsValueType, ospf::Infinity>)
                {
                    return ospf::RealNumberTrait<T>::is_inf(lhs);
                }
                else if constexpr (ospf::DecaySameAs<RhsValueType, ospf::NegativeInfinity>)
                {
                    return !ospf::RealNumberTrait<T>::is_neg_inf(lhs);
                }
                else
                {
                    return lhs >= rhs_value;
                }
            }, rhs);
    }
    else
    {
        return std::visit([&lhs](const auto& rhs_value)
            {
                using RhsValueType = ospf::OriginType<decltype(rhs_value)>;
                if constexpr (ospf::DecaySameAs<RhsValueType, ospf::Infinity>)
                {
                    return false;
                }
                else if constexpr (ospf::DecaySameAs<RhsValueType, ospf::NegativeInfinity>)
                {
                    return true;
                }
                else
                {
                    return lhs >= rhs_value;
                }
            }, rhs);
    }
}

template<ospf::Arithmetic T>
inline const bool operator<=>(const T& lhs, const ospf::value_range::ValueWrapper<T>& rhs) noexcept
{
    using RetType = std::compare_three_way_result_t<T>;

    if constexpr (ospf::RealNumber<T>)
    {
        return std::visit([&lhs](const auto& rhs_value) -> RetType
            {
                using RhsValueType = ospf::OriginType<decltype(rhs_value)>;
                if constexpr (ospf::DecaySameAs<RhsValueType, ospf::Infinity>)
                {
                    return ospf::RealNumberTrait<T>::is_inf(lhs) ? std::strong_ordering::equal : std::strong_ordering::less;
                }
                else if constexpr (ospf::DecaySameAs<RhsValueType, ospf::NegativeInfinity>)
                {
                    return ospf::RealNumberTrait<T>::is_neg_inf(lhs) ? std::strong_ordering::equal : std::strong_ordering::greater;
                }
                else
                {
                    return lhs <=> rhs_value;
                }
            }, rhs);
    }
    else
    {
        return std::visit([&lhs](const auto& rhs_value) -> RetType
            {
                using RhsValueType = ospf::OriginType<decltype(rhs_value)>;
                if constexpr (ospf::DecaySameAs<RhsValueType, ospf::Infinity>)
                {
                    return std::strong_ordering::less;
                }
                else if constexpr (ospf::DecaySameAs<RhsValueType, ospf::NegativeInfinity>)
                {
                    return std::strong_ordering::greater;
                }
                else
                {
                    return lhs <=> rhs_value;
                }
            }, rhs);
    }
}

namespace std
{
    template<ospf::Arithmetic T, ospf::CharType CharT>
    struct formatter<ospf::value_range::ValueWrapper<T>, CharT>
        : public formatter<std::basic_string_view<CharT>, CharT>
    {
        template<typename FormatContext>
        inline decltype(auto) format(ospf::ArgCLRefType<ospf::value_range::ValueWrapper<T>> value, FormatContext& fc)
        {
            return std::visit([](const auto& value)
                {
                    static const formatter<ospf::OriginType<decltype(value)>, CharT> _formatter{};
                    return _formatter.format(value, fc);
                }, value);
        }
    };
};
