#pragma once

#include <ospf/functional/array.hpp>
#include <ospf/math/algebra/concepts/real_number.hpp>

namespace ospf
{
    inline namespace math
    {
        inline namespace algebra
        {
            template<usize dim, RealNumber T = f64>
            class Vector
            {
            public:
                using ValueType = OriginType<T>;

            public:
                constexpr Vector(std::array<ValueType, dim> values)
                    : _values(std::move(_values)) {}

            public:
                constexpr Vector(const Vector& ano) = default;
                constexpr Vector(Vector&& ano) noexcept = default;
                constexpr Vector& operator=(const Vector& rhs) = default;
                constexpr Vector& operator=(Vector&& rhs) noexcept = default;
                constexpr ~Vector(void) noexcept = default;

            public:
                inline constexpr ArgCLRefType<ValueType> operator[](const usize i) const noexcept
                {
                    return _values[i];
                }

            public:
                inline constexpr Vector operator+(const Vector& rhs) const noexcept
                {
                    return Vector{ make_array<ValueType, dim>([this, &rhs](const usize i)
                        {
                            return this->_values[i] + rhs._values[i];
                        }) };
                }

                inline constexpr Vector operator-(const Vector& rhs) const noexcept
                {
                    return Vector{ make_array<ValueType, dim>([this, &rhs](const usize i)
                        {
                            return this->_values[i] - rhs._values[i];
                        }) };
                }

            private:
                std::array<ValueType, dim> _values;
            };

            template<RealNumber T = f64>
            class Vector2
                : public Vector<2_uz, T>
            {
                using Base = Vector<2_uz, T>;

            public:
                using typename Base::ValueType;
                
            public:
                constexpr Vector2(ArgRRefType<Base> base)
                    : Base(move<Base>(base)) {}

                constexpr Vector2(std::array<ValueType, 2_uz> values)
                    : Base(std::move(values)) {}

                constexpr Vector2(ArgRRefType<ValueType> x, ArgRRefType<ValueType> y)
                    : Base(move<ValueType>(x), move<ValueType>(y)) {}
                
            public:
                constexpr Vector2(const Vector2& ano) = default;
                constexpr Vector2(Vector2&& ano) noexcept = default;
                constexpr Vector2& operator=(const Vector2& rhs) = default;
                constexpr Vector2& operator=(Vector2&& rhs) noexcept = default;
                constexpr ~Vector2(void) noexcept = default;

            public:
                inline constexpr ArgCLRefType<ValueType> x(void) const noexcept
                {
                    return this->operator[](0_uz);
                }

                inline constexpr ArgCLRefType<ValueType> y(void) const noexcept
                {
                    return this->operator[](1_uz);
                }
            };

            template<RealNumber T = f64>
            class Vector3
                : public Vector<3_uz, T>
            {
                using Base = Vector<3_uz, T>;

            public:
                using typename Base::ValueType;

            public:
                constexpr Vector3(ArgRRefType<Base> base)
                    : Base(move<Base>(base)) {}

                constexpr Vector3(std::array<ValueType, 3_uz> values)
                    : Base(std::move(values)) {}

                constexpr Vector3(ArgRRefType<ValueType> x, ArgRRefType<ValueType> y, ArgRRefType<ValueType> z)
                    : Base(move<ValueType>(x), move<ValueType>(y), move<ValueType>(z)) {}

            public:
                constexpr Vector3(const Vector3& ano) = default;
                constexpr Vector3(Vector3&& ano) noexcept = default;
                constexpr Vector3& operator=(const Vector3& rhs) = default;
                constexpr Vector3& operator=(Vector3&& rhs) noexcept = default;
                constexpr ~Vector3(void) noexcept = default;

            public:
                inline constexpr ArgCLRefType<ValueType> x(void) const noexcept
                {
                    return this->operator[](0_uz);
                }

                inline constexpr ArgCLRefType<ValueType> y(void) const noexcept
                {
                    return this->operator[](1_uz);
                }

                inline constexpr ArgCLRefType<ValueType> z(void) const noexcept
                {
                    return this->operator[](2_uz);
                }
            };

            extern template class Vector2<f64>;
            extern template class Vector3<f64>;
        };
    };
};

namespace ospf
{
    template<usize dim, RealNumber T>
    struct ArithmeticTrait<Vector<dim, T>>
    {
        inline static const Vector<dim, T>& zero(void) noexcept
        {
            static const Vector<dim, T> value{ make_array<T, dim>([](const usize i) { return ArithmeticTrait<T>::zero(); }) };
            return value;
        }

        inline static const Vector<dim, T>& one(void) noexcept
        {
            static const Vector<dim, T> value{ make_array<T, dim>([](const usize i) { return ArithmeticTrait<T>::one(); }) };
            return value;
        }
    };

    template<RealNumber T>
    struct ArithmeticTrait<Vector2<T>>
    {
        inline static const Vector2<T> zero(void) noexcept
        {
            return Vector2<T>{ make_array<T, 2_uz>([](const usize _) { return ArithmeticTrait<T>::zero(); }) };
        }

        inline static const Vector2<T> one(void) noexcept
        {
            return Vector2<T>{ make_array<T, 2_uz>([](const usize _) { return ArithmeticTrait<T>::one(); }) };
        }
    };

    template<RealNumber T>
    struct ArithmeticTrait<Vector3<T>>
    {
        inline static const Vector3<T> zero(void) noexcept
        {
            return Vector3<T>{ make_array<T, 3_uz>([](const usize _) { return ArithmeticTrait<T>::zero(); }) };
        }

        inline static const Vector3<T> one(void) noexcept
        {
            return Vector3<T>{ make_array<T, 3_uz>([](const usize _) { return ArithmeticTrait<T>::one(); }) };
        }
    };
};
