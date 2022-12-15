#pragma once

#include <ospf/basic_definition.hpp>
#include <ospf/literal_constant.hpp>
#include <optional>

namespace ospf
{
	inline namespace math
	{
		template<typename T>
		struct BoundedTrait {};

		template<typename T>
		concept Bounded = requires
		{
			{ BoundedTrait<T>::maximum } -> std::same_as<std::optional<T>>;
			{ BoundedTrait<T>::minimum } -> std::same_as<std::optional<T>>;
			{ BoundedTrait<T>::positive_minimum } -> std::same_as<T>;
		};

		template<>
		struct BoundedTrait<i8>
		{
			static constexpr const i8 maximum = std::numeric_limits<i8>::max();
			static constexpr const i8 minimum = std::numeric_limits<i8>::lowest();
			static constexpr const i8 positive_minimum = std::numeric_limits<i8>::min();
		};
	};
};
