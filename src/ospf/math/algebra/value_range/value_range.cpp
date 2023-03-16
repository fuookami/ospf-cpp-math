#include <ospf/math/algebra/value_range/value_range.hpp>

namespace ospf::math::algebra
{
    extern template class ValueRange<i8, Interval::Open, Interval::Open>;
    extern template class ValueRange<i8, Interval::Close, Interval::Close>;
    extern template class ValueRange<u8, Interval::Open, Interval::Open>;
    extern template class ValueRange<u8, Interval::Close, Interval::Close>;
    extern template class ValueRange<i16, Interval::Open, Interval::Open>;
    extern template class ValueRange<i16, Interval::Close, Interval::Close>;
    extern template class ValueRange<u16, Interval::Open, Interval::Open>;
    extern template class ValueRange<u16, Interval::Close, Interval::Close>;
    extern template class ValueRange<i32, Interval::Open, Interval::Open>;
    extern template class ValueRange<i32, Interval::Close, Interval::Close>;
    extern template class ValueRange<u32, Interval::Open, Interval::Open>;
    extern template class ValueRange<u32, Interval::Close, Interval::Close>;
    extern template class ValueRange<i64, Interval::Open, Interval::Open>;
    extern template class ValueRange<i64, Interval::Close, Interval::Close>;
    extern template class ValueRange<u64, Interval::Open, Interval::Open>;
    extern template class ValueRange<u64, Interval::Close, Interval::Close>;
    //extern template class ValueRange<i128, Interval::Open, Interval::Open>;
    //extern template class ValueRange<i128, Interval::Close, Interval::Close>;
    //extern template class ValueRange<u128, Interval::Open, Interval::Open>;
    //extern template class ValueRange<u128, Interval::Close, Interval::Close>;
    //extern template class ValueRange<i256, Interval::Open, Interval::Open>;
    //extern template class ValueRange<i256, Interval::Close, Interval::Close>;
    //extern template class ValueRange<u256, Interval::Open, Interval::Open>;
    //extern template class ValueRange<u256, Interval::Close, Interval::Close>;
    //extern template class ValueRange<i512, Interval::Open, Interval::Open>;
    //extern template class ValueRange<i512, Interval::Close, Interval::Close>;
    //extern template class ValueRange<u512, Interval::Open, Interval::Open>;
    //extern template class ValueRange<u512, Interval::Close, Interval::Close>;
    //extern template class ValueRange<i1024, Interval::Open, Interval::Open>;
    //extern template class ValueRange<i1024, Interval::Close, Interval::Close>;
    //extern template class ValueRange<u1024, Interval::Open, Interval::Open>;
    //extern template class ValueRange<u1024, Interval::Close, Interval::Close>;
    //extern template class ValueRange<bigint, Interval::Open, Interval::Open>;
    //extern template class ValueRange<bigint, Interval::Close, Interval::Close>;

    extern template class ValueRange<f32, Interval::Open, Interval::Open>;
    extern template class ValueRange<f32, Interval::Close, Interval::Close>;
    extern template class ValueRange<f64, Interval::Open, Interval::Open>;
    extern template class ValueRange<f64, Interval::Close, Interval::Close>;
    //extern template class ValueRange<f128, Interval::Open, Interval::Open>;
    //extern template class ValueRange<f128, Interval::Close, Interval::Close>;
    //extern template class ValueRange<f256, Interval::Open, Interval::Open>;
    //extern template class ValueRange<f256, Interval::Close, Interval::Close>;
    //extern template class ValueRange<f512, Interval::Open, Interval::Open>;
    //extern template class ValueRange<f512, Interval::Close, Interval::Close>;
    //extern template class ValueRange<dec50, Interval::Open, Interval::Open>;
    //extern template class ValueRange<dec50, Interval::Close, Interval::Close>;
    //extern template class ValueRange<dec100, Interval::Open, Interval::Open>;
    //extern template class ValueRange<dec100, Interval::Close, Interval::Close>;

    extern template class DynValueRange<i8>;
    extern template class DynValueRange<u8>;
    extern template class DynValueRange<i16>;
    extern template class DynValueRange<u16>;
    extern template class DynValueRange<i32>;
    extern template class DynValueRange<u32>;
    extern template class DynValueRange<i64>;
    extern template class DynValueRange<u64>;
    //extern template class DynValueRange<i128>;
    //extern template class DynValueRange<u128>;
    //extern template class DynValueRange<i256>;
    //extern template class DynValueRange<u256>;
    //extern template class DynValueRange<i512>;
    //extern template class DynValueRange<u512>;
    //extern template class DynValueRange<i1024>;
    //extern template class DynValueRange<u1024>;
    //extern template class DynValueRange<bigint>;

    extern template class DynValueRange<f32>;
    extern template class DynValueRange<f64>;
    //extern template class DynValueRange<f128>;
    //extern template class DynValueRange<f256>;
    //extern template class DynValueRange<f512>;
    //extern template class DynValueRange<dec50>;
    //extern template class DynValueRange<dec100>;
};