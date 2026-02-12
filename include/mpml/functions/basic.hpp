#pragma once // base.hpp
// MIT
// Allosker - 2026
// ===================================================
// Define some basic functions for most mathematical operations
// ===================================================

#include <cstdint>
#include <concepts>

namespace mpml::func
{

	template<typename T> 
	[[nodiscard]] constexpr T fac(const T& x) noexcept
	{
		return (x > 0) ? x * fac<T>(x - 1) : 1;
	}

	template<std::integral T>
	[[nodiscard]] constexpr T alt_sign(T value) noexcept
	{
		return (value % static_cast<T>(2) == T{}) ? static_cast<T>(1) : -static_cast<T>(1);
	}

}