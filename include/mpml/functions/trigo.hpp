#pragma once // trigo.hpp
// MIT
// Allosker - 2026
// ===================================================
// Define some of the trigonometric functions in order to give them a bigger span
// ===================================================

#include <cstdint>
#include <cmath>

#include "mpml/functions/basic.hpp"
#include "mpml/utilities/angle.hpp"

namespace mpml::func
{

	template<typename T, std::size_t SPAN=4>
	constexpr T cos(const Angle<T>& x) noexcept
	{	
		T n{};
		
		for (std::int32_t k{0}; k < SPAN; k++)
		{
			const auto coef{static_cast<T>(2) * static_cast<T>(k)};
			n += (static_cast<T>(alt_sign(k)) * std::pow(x.asRadians(), coef)) / fact(coef);
		}

		return n;
	}

	template<typename T, std::size_t SPAN=4>
	constexpr T sin(const Angle<T>& x) noexcept
	{	
		T n{};
		
		for (std::int32_t k{0}; k < SPAN; k++)
		{
			const auto coef{ static_cast<T>(2) * static_cast<T>(k) + static_cast<T>(1) };
			n += (static_cast<T>(alt_sign(k)) * std::pow(x.asRadians(), coef)) / fact(coef);
		}

		return n;
	}

	// FIX THIS
	template<typename T, std::size_t SPAN=15>
	constexpr T tan(const Angle<T>& x) noexcept
	{
		T temp{};

		for (std::size_t n{1}; n <= SPAN; n++)
		{
			std::size_t mult{static_cast<std::size_t>(2) * n};
			T coef{std::pow(static_cast<T>(2), mult)};
			temp += 
			((alt_sign(n - 1) * coef * (coef - 1) * bernoulli<T>(mult)) /
			fact(mult)) * 
			std::pow(x.asRadians(), mult - 1);
		}

		return temp;
	}


	
}