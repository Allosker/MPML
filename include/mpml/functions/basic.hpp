#pragma once // base.hpp
// MIT
// Allosker - 2025
// ===================================================
// Define some basic functions for most mathematical operations
// ===================================================

#include <cstdint>

namespace mpml::func
{

	template<typename T> 
	constexpr T fac(const T& x)
	{
		return (x > 0) ? x * fac(x - 1) : 1;
	}

}