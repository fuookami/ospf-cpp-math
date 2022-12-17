#include "arithmetic.hpp"

namespace ospf::math
{
    const bigint ArithmeticTrait<bigint>::zero = bigint{ 0_i64 };
    const bigint ArithmeticTrait<bigint>::one = bigint{ 1_i64 };

    const f128 ArithmeticTrait<f128>::zero = f128{ 0._f64 };
    const f128 ArithmeticTrait<f128>::one = f128{ 1._f64 };

    const f256 ArithmeticTrait<f256>::zero = f256{ 0._f64 };
    const f256 ArithmeticTrait<f256>::one = f256{ 1._f64 };

    const f512 ArithmeticTrait<f512>::zero = f512{ 0._f64 };
    const f512 ArithmeticTrait<f512>::one = f512{ 1._f64 };

    const dec50 ArithmeticTrait<dec50>::zero = dec50{ 0._f64 };
    const dec50 ArithmeticTrait<dec50>::one = dec50{ 1._f64 };

    const dec100 ArithmeticTrait<dec100>::zero = dec100{ 0._f64 };
    const dec100 ArithmeticTrait<dec100>::one = dec100{ 1._f64 };
};
