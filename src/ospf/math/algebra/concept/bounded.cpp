#include "bounded.hpp"

namespace ospf::math::algebra
{
    const std::optional<bigint> BoundedTrait<bigint>::maximum = std::nullopt;
    const std::optional<bigint> BoundedTrait<bigint>::minimum = std::nullopt;
    const bigint BoundedTrait<bigint>::positive_minimum = bigint{ 1_i64 };

    const std::optional<f128> BoundedTrait<f128>::maximum = std::numeric_limits<f128>::max();
    const std::optional<f128> BoundedTrait<f128>::minimum = std::numeric_limits<f128>::lowest();
    const f128 BoundedTrait<f128>::positive_minimum = std::numeric_limits<f128>::min();

    const std::optional<f256> BoundedTrait<f256>::maximum = std::numeric_limits<f256>::max();
    const std::optional<f256> BoundedTrait<f256>::minimum = std::numeric_limits<f256>::lowest();
    const f256 BoundedTrait<f256>::positive_minimum = std::numeric_limits<f256>::min();

    const std::optional<f512> BoundedTrait<f512>::maximum = std::numeric_limits<f512>::max();
    const std::optional<f512> BoundedTrait<f512>::minimum = std::numeric_limits<f512>::lowest();
    const f512 BoundedTrait<f512>::positive_minimum = std::numeric_limits<f512>::min();

    const std::optional<dec50> BoundedTrait<dec50>::maximum = std::numeric_limits<dec50>::max();
    const std::optional<dec50> BoundedTrait<dec50>::minimum = std::numeric_limits<dec50>::lowest();
    const dec50 BoundedTrait<dec50>::positive_minimum = std::numeric_limits<dec50>::min();

    const std::optional<dec100> BoundedTrait<dec100>::maximum = std::numeric_limits<dec100>::max();
    const std::optional<dec100> BoundedTrait<dec100>::minimum = std::numeric_limits<dec100>::lowest();
    const dec100 BoundedTrait<dec100>::positive_minimum = std::numeric_limits<dec100>::min();
};
