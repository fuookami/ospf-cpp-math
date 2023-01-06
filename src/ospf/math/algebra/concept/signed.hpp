#pragma once

namespace ospf
{
    inline namespace math
    {
        inline namespace algebra
        {
            template<typename T>
            struct IsSigned
            {
                static constexpr const bool value = false;
            };

            template<typename T>
            concept Signed = IsSigned<T>::value;

            template<typename T>
            concept Unsigned = !IsSigned<T>::value;

            // todo
        };
    };
};
