#pragma once // trigo.hpp
// MIT
// Allosker - 2026
// ===================================================
// Define some of the trigonometric functions in order to give them a bigger span
// ===================================================

#include <cstdint>
#include <cmath>

namespace mpml::func
{

	template<std::uint32_t SPAN=4, typename T>
	constexpr T cos(const T& x) noexcept
	{	
		T n{};
		
		for (std::int32_t k{0}; k < SPAN; k++)
			n += (static_cast<T>(alt_sign(k)) * std::pow(x, static_cast<T>(2) * static_cast<T>(k))) / fac(static_cast<T>(2) * static_cast<T>(k));

		return n;
	}

}