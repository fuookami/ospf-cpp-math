#include <ospf/math/algebra/concept/precision.hpp>

namespace ospf::math::algebra
{
    const bigint PrecisionTrait<bigint>::epsilon = bigint{ 0_i64 };
    const bigint PrecisionTrait<bigint>::decimal_precision = bigint{ 0_i64 };

    const f128 PrecisionTrait<f128>::epsilon = std::numeric_limits<f128>::denorm_min();
    const f128 PrecisionTrait<f128>::decimal_precision = std::numeric_limits<f128>::epsilon();

    const f256 PrecisionTrait<f256>::epsilon = std::numeric_limits<f256>::denorm_min();
    const f256 PrecisionTrait<f256>::decimal_precision = std::numeric_limits<f256>::epsilon();

    const f512 PrecisionTrait<f512>::epsilon = std::numeric_limits<f512>::denorm_min();
    const f512 PrecisionTrait<f512>::decimal_precision = std::numeric_limits<f512>::epsilon();

    const dec50 PrecisionTrait<dec50>::epsilon = std::numeric_limits<dec50>::denorm_min();
    const dec50 PrecisionTrait<dec50>::decimal_precision = std::numeric_limits<dec50>::epsilon();

    const dec100 PrecisionTrait<dec100>::epsilon = std::numeric_limits<dec100>::denorm_min();
    const dec100 PrecisionTrait<dec100>::decimal_precision = std::numeric_limits<dec100>::epsilon();
};
