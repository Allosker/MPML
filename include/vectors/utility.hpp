#pragma once
// MIT
// Allosker - 2025
// ===================================================
// Defines some utility functions for all the types MPML provides
// ===================================================

#include "vector2.hpp"
#include "vector3.hpp"

namespace mpml
{
	// Vectors
	
		// Vector 2
		template<typename T>
		constexpr Vector2<T> abs(const Vector2<T>& vec) noexcept
		{
			return Vector2<T>{std::abs(vec.x), std::abs(vec.y)};
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

		template<typename T>
		constexpr Vector2<T> average(const Vector2<T>& a, const Vector2<T>& b) noexcept
		{
			return Vector2<T>{ (a.x + b.x) / 2, (a.y + b.y) / 2};
		}

		// Vector 3
		template<typename T>
		constexpr Vector3<T> abs(const Vector3<T>& vec) noexcept
		{
			return Vector3<T>{std::abs(vec.x), std::abs(vec.y), std::abs(vec.z)};
		}


		template<typename T>
		constexpr Vector3<T> min(const Vector3<T>& a, const Vector3<T>& b) noexcept
		{
			return Vector3<T>{((a.x < b.x) ? a.x : b.x), ((a.y < b.y ? a.y : b.y)), ((a.z < b.z ? a.z : b.z)) };
		}

		template<typename T>
		constexpr Vector3<T> max(const Vector3<T>& a, const Vector3<T>& b) noexcept
		{
			return Vector3<T>{((a.x > b.x) ? a.x : b.x), ((a.y > b.y ? a.y : b.y)), ((a.z > b.z ? a.z : b.z)) };
		}

		template<typename T>
		constexpr Vector3<T> average(const Vector3<T>& a, const Vector3<T>& b) noexcept
		{
			return Vector3<T>{ (a.x + b.x) / 2, (a.y + b.y) / 2, (a.z + b.z) / 2};
		}

}