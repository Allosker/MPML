#pragma once
// MIT
// Allosker - 2025
// ===================================================
// Defines some utility functions for vectors of all dimensions.
// ===================================================

#include "vector2.hpp"
#include "vector3.hpp"

namespace mpml
{

	template<typename T>
	constexpr Vector2<T> abs(const Vector2<T>& vec) noexcept
	{
		return Vector2<T>{std::abs(x), std::abs(y)};
	}


	template<typename T>
	constexpr Vector2<T> min(const Vector2<T>& a, const Vector2<T>& b) noexcept
	{
		return Vector2<T>{((a.x < b.x) ? a.x : b.x), ((a.y < b.y ? a.y : b.y)) };
	}

	template<typename T>
	constexpr Vector2<T> max(const Vector2<T>& a, const Vector2<T>& b) noexcept
	{
		return Vector2<T>{((a.x > b.x) ? a.x : b.x), ((a.y > b.y ? a.y : b.y)) };
	}




}