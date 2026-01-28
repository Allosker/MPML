#pragma once // trigo.hpp
// MIT
// Allosker - 2025
// ===================================================
// Define some of the trigonometric functions in order to give them a bigger span
// ===================================================

#include <cstdint>
#include <cmath>

namespace mpml::func
{

	template<typename T, std::uint64_t SPAN>
	constexpr T cos(const T& x) noexcept
	{
		long long n{};
		
		for (int i = 0; i < SPAN; i++)
			n += (((i % 2 == 0) ? 1 : -1) / fac(2 * i + 1)) * std::pow(x, 2 * i + 1);

		return n;
	}

}