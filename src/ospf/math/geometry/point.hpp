#pragma once

#include <ospf/math/algebra/vector.hpp>

namespace ospf
{
    inline namespace math
    {
        inline namespace geometry
        {
            template<usize dim, RealNumber T = f64>
            class Point
            {
            public:
                using ValueType = OriginType<T>;

            public:
                constexpr Point(std::array<ValueType, dim> coordinate)
                    : _coordinate(std::move(coordinate)) {}

            public:
                constexpr Point(const Point& ano) = default;
                constexpr Point(Point&& ano) noexcept = default;
                constexpr Point& operator=(const Point& rhs) = default;
                constexpr Point& operator=(Point&& rhs) = default;
                constexpr ~Point(void) noexcept = default;

            public:
                inline constexpr operator RetType<Vector<dim, ValueType>>(void) const noexcept
                {
                    return Vector<dim, ValueType>{ _coordinate };
                }

            public:
                inline constexpr ArgCLRefType<ValueType> operator[](const usize i) const noexcept
                {
                    return _coordinate[i];
                }

            public:
                inline constexpr RetType<Point> operator+(ArgCLRefType<Vector<dim, ValueType>> vector) const noexcept
                {
                    return Point{ make_array<ValueType, dim>([this, &vector](const usize i)
                        {
                            return this->_coordinate[i] + vector[i];
                        }) };
                }

                inline constexpr RetType<Point> operator-(ArgCLRefType<Vector<dim, ValueType>> vector) const noexcept
                {
                    return Point{ make_array<ValueType, dim>([this, &vector](const usize i)
                        {
                            return this->_coordinate[i] - vector[i];
                        }) };
                }

            private:
                std::array<ValueType, dim> _coordinate;
            };

            template<RealNumber T = f64>
            class Point2
                : public Point<2_uz, T>
            {
                using Base = Point<2_uz, T>;

            public:
                using typename Base::ValueType;

            public:
                constexpr Point2(ArgRRefType<Base> base)
                    : Base(move<Base>(base)) {}

                constexpr Point2(std::array<ValueType, 2_uz> coordinate)
                    : Base(std::move(coordinate)) {}

                constexpr Point2(ArgRRefType<T> x, ArgRRefType<T> y)
                    : Base(move<ValueType>(x), move<ValueType>(y)) {}

            public:
                constexpr Point2(const Point2& ano) = default;
                constexpr Point2(Point2&& ano) noexcept = default;
                constexpr Point2& operator=(const Point2& rhs) = default;
                constexpr Point2& operator=(Point2&& rhs) noexcept = default;
                constexpr ~Point2(void) noexcept = default;

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
            class Point3
                : public Point<3_uz, T>
            {
                using Base = Point<3_uz, T>;

            public:
                using typename Base::ValueType;

            public:
                constexpr Point3(ArgRRefType<Base> base)
                    : Base(move<Base>(base)) {}

                constexpr Point3(std::array<ValueType, 3_uz> coordinate)
                    : Base(std::move(coordinate)) {}

                constexpr Point3(ArgRRefType<T> x, ArgRRefType<T> y, ArgRRefType<T> z)
                    : Base(move<ValueType>(x), move<ValueType>(y), move<ValueType>(z)) {}

            public:
                constexpr Point3(const Point3& ano) = default;
                constexpr Point3(Point3&& ano) noexcept = default;
                constexpr Point3& operator=(const Point3& rhs) = default;
                constexpr Point3& operator=(Point3&& rhs) noexcept = default;
                constexpr ~Point3(void) noexcept = default;

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

            extern template class Point2<f64>;
            extern template class Point3<f64>;
        };
    };
};
