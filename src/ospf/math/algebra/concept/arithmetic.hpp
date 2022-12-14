#pragma once

#include <ospf/basic_definition.hpp>
#include <ospf/literal_constant.hpp>
#include <concepts>
#include <compare>

namespace ospf
{
	inline namespace math
	{
		template<typename T>
			requires std::copyable<T>
				&& std::three_way_comparable<T>
				&& requires
				{
					{ static_cast<T>(0) } -> std::same_as<T>;
					{ static_cast<T>(1) } -> std::same_as<T>;
				}
		struct Arithmetic
		{
			static constexpr const T zero = static_cast<T>(0);
			static constexpr const T one = static_cast<T>(1);
		};

		template<>
		struct Arithmetic<i8>
		{
			static constexpr const i8 zero = 0_i8;
			static constexpr const i8 one = 1_i8;
		};
	};
};
