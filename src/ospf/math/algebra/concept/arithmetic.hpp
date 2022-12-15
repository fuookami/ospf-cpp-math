#pragma once

#include <ospf/basic_definition.hpp>
#include <ospf/literal_constant.hpp>
#include <ospf/math/ospf_math_api.hpp>
#include <concepts>
#include <compare>

namespace ospf
{
	inline namespace math
	{
		template<typename T>
			requires std::copyable<T>
				&& (std::three_way_comparable<T> || std::totally_ordered<T>)
				&& requires
				{
					{ static_cast<T>(0) } -> std::same_as<T>;
					{ static_cast<T>(1) } -> std::same_as<T>;
				}
		struct ArithmeticTrait {};

		template<typename T>
		concept Arithmetic = std::copyable<T> 
			&& (std::three_way_comparable<T> || std::totally_ordered<T>)
			&& requires
			{
				{ ArithmeticTrait<T>::zero } -> std::same_as<T>;
				{ ArithmeticTrait<T>::one } -> std::same_as<T>;
			};

		template<>
		struct ArithmeticTrait<i8>
		{
			static constexpr const i8 zero = 0_i8;
			static constexpr const i8 one = 1_i8;
		};

		template<>
		struct ArithmeticTrait<u8>
		{
			static constexpr const u8 zero = 0_u8;
			static constexpr const u8 one = 1_u8;
		};

		template<>
		struct ArithmeticTrait<i16>
		{
			static constexpr const i16 zero = 0_i16;
			static constexpr const i16 one = 1_i16;
		};

		template<>
		struct ArithmeticTrait<u16>
		{
			static constexpr const u16 zero = 0_u16;
			static constexpr const u16 one = 1_u16;
		};

		template<>
		struct ArithmeticTrait<i32>
		{
			static constexpr const i32 zero = 0_i32;
			static constexpr const u32 one = 1_i32;
		};

		template<>
		struct ArithmeticTrait<u32>
		{
			static constexpr const u32 zero = 0_u32;
			static constexpr const u32 one = 1_u32;
		};

		template<>
		struct ArithmeticTrait<i64>
		{
			static constexpr const i64 zero = 0_i64;
			static constexpr const i64 one = 1_i64;
		};

		template<>
		struct ArithmeticTrait<u64>
		{
			static constexpr const u64 zero = 0_u64;
			static constexpr const u64 one = 1_u64;
		};

		template<>
		struct ArithmeticTrait<i128>
		{
			static constexpr const i128 zero = i128{ 0_i64 };
			static constexpr const i128 one = i128{ 1_i64 };
		};

		template<>
		struct ArithmeticTrait<u128>
		{
			static constexpr const u128 zero = u128{ 0_u64 };
			static constexpr const u128 one = u128{ 1_u64 };
		};

		template<>
		struct ArithmeticTrait<i256>
		{
			static constexpr const i256 zero = i256{ 0_i64 };
			static constexpr const i256 one = i256{ 1_i64 };
		};

		template<>
		struct ArithmeticTrait<u256>
		{
			static constexpr const u256 zero = u256{ 0_u64 };
			static constexpr const u256 one = u256{ 1_u64 };
		};

		template<>
		struct ArithmeticTrait<i512>
		{
			static constexpr const i512 zero = i512{ 0_i64 };
			static constexpr const i512 one = i512{ 1_i64 };
		};

		template<>
		struct ArithmeticTrait<u512>
		{
			static constexpr const u512 zero = u512{ 0_u64 };
			static constexpr const u512 one = u512{ 1_u64 };
		};

		template<>
		struct ArithmeticTrait<i1024>
		{
			static constexpr const i1024 zero = i1024{ 0_i64 };
			static constexpr const i1024 one = i1024{ 1_i64 };
		};

		template<>
		struct ArithmeticTrait<u1024>
		{
			static constexpr const u1024 zero = u1024{ 0_u64 };
			static constexpr const u1024 one = u1024{ 1_u64 };
		};

		template<u64 bits>
		struct ArithmeticTrait<uintx<bits>>
		{
			static constexpr const uintx<bits> zero = uintx<bints>{ 0_u64 };
			static constexpr const uintx<bits> one = uintx<bints>{ 1_u64 };
		};

		template<u64 bits>
		struct ArithmeticTrait<intx<bits>>
		{
			static constexpr const intx<bits> zero = intx<bints>{ 0_i64 };
			static constexpr const intx<bits> one = intx<bints>{ 1_i64 };
		};

		template<>
		struct ArithmeticTrait<bigint>
		{
			OSPF_MATH_API static const bigint zero;
			OSPF_MATH_API static const bigint one;
		};

		template<>
		struct ArithmeticTrait<f32>
		{
			static constexpr const f32 zero = 0._f32;
			static constexpr const f32 one = 1._f32;
		};

		template<>
		struct ArithmeticTrait<f64>
		{
			static constexpr const f64 zero = 0._f64;
			static constexpr const f64 one = 1._f64;
		};

		template<>
		struct ArithmeticTrait<f128>
		{
			OSPF_MATH_API static const f128 zero;
			OSPF_MATH_API static const f128 one;
		};

		template<>
		struct ArithmeticTrait<f256>
		{
			OSPF_MATH_API static const f256 zero;
			OSPF_MATH_API static const f256 one;
		};

		template<>
		struct ArithmeticTrait<f512>
		{
			OSPF_MATH_API static const f512 zero;
			OSPF_MATH_API static const f512 one;
		};

		template<>
		struct ArithmeticTrait<dec50>
		{
			OSPF_MATH_API static const dec50 zero;
			OSPF_MATH_API static const dec50 one;
		};

		template<>
		struct ArithmeticTrait<dec50>
		{
			OSPF_MATH_API static const dec100 zero;
			OSPF_MATH_API static const dec100 one;
		};

		template<u64 digits>
		struct ArithmeticTrait<dec<digits>>
		{
			static const dec<digits> zero;
			static const dec<digits> one;
		};
	};
};

template<ospf::u64 digits>
const ospf::dec<digits> ospf::ArithmeticTrait<ospf::dec<digits>>::zero = ospf::dec<digits>{ 0._f64 };
template<ospf::u64 digits>
const ospf::dec<digits> ospf::ArithmeticTrait<ospf::dec<digits>>::one = ospf::dec<digits>{ 1._f64 };
