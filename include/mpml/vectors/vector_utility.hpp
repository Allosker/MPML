#pragma once
// MIT
// Allosker - 2025
// ===================================================
// Defines some utility functions for all the types MPML provides
// ===================================================

#include "mpml/vectors/vectors.hpp"

#include "mpml/utilities/types/angle.hpp"

namespace mpml
{
	// Vectors
	
	// Vector2
	template<typename T>
	[[nodiscard]] constexpr Vector2<T> abs(const Vector2<T>& vec) noexcept
	{
		return Vector2<T>{std::abs(vec.x), std::abs(vec.y)};
	}


	template<typename T>
	[[nodiscard]] constexpr Vector2<T> min(const Vector2<T>& a, const Vector2<T>& b) noexcept
	{
		return Vector2<T>{((a.x < b.x) ? a.x : b.x), ((a.y < b.y ? a.y : b.y)) };
	}

	template<typename T>
	[[nodiscard]] constexpr Vector2<T> max(const Vector2<T>& a, const Vector2<T>& b) noexcept
	{
		return Vector2<T>{((a.x > b.x) ? a.x : b.x), ((a.y > b.y ? a.y : b.y)) };
	}

	template<typename T>
	[[nodiscard]] constexpr Vector2<T> average(const Vector2<T>& a, const Vector2<T>& b) noexcept
	{
		return Vector2<T>{ (a.x + b.x) / 2, (a.y + b.y) / 2};
	}


	template<typename T>
	[[nodiscard]] constexpr Vector2<T> floor(const Vector2<T>& vec) noexcept
	{
		return { std::floor(vec.x), std::floor(vec.y) };
	}

	template<typename T>
	[[nodiscard]] constexpr Vector2<T> ceil(const Vector2<T>& vec) noexcept
	{
		return { std::ceil(vec.x), std::ceil(vec.y) };
	}


	// Vector 3
	template<typename T>
	[[nodiscard]] constexpr Vector3<T> abs(const Vector3<T>& vec) noexcept
	{
		return Vector3<T>{std::abs(vec.x), std::abs(vec.y), std::abs(vec.z)};
	}


	template<typename T>
	[[nodiscard]] constexpr Vector3<T> min(const Vector3<T>& a, const Vector3<T>& b) noexcept
	{
		return Vector3<T>{((a.x < b.x) ? a.x : b.x), ((a.y < b.y ? a.y : b.y)), ((a.z < b.z ? a.z : b.z)) };
	}

	template<typename T>
	[[nodiscard]] constexpr Vector3<T> max(const Vector3<T>& a, const Vector3<T>& b) noexcept
	{
		return Vector3<T>{((a.x > b.x) ? a.x : b.x), ((a.y > b.y ? a.y : b.y)), ((a.z > b.z ? a.z : b.z)) };
	}

	template<typename T>
	[[nodiscard]] constexpr Vector3<T> average(const Vector3<T>& a, const Vector3<T>& b) noexcept
	{
		return Vector3<T>{ (a.x + b.x) / 2, (a.y + b.y) / 2, (a.z + b.z) / 2};
	}


	template<typename T>
	[[nodiscard]] constexpr Vector3<T> floor(const Vector3<T>& vec) noexcept
	{
		return { std::floor(vec.x), std::floor(vec.y), std::floor(vec.z) };
	}

	template<typename T>
	[[nodiscard]] constexpr Vector3<T> ceil(const Vector3<T>& vec) noexcept
	{
		return { std::ceil(vec.x), std::ceil(vec.y), std::ceil(vec.z) };
	}


	// Vector 4
	template<typename T>
	[[nodiscard]] constexpr Vector4<T> abs(const Vector4<T>& vec) noexcept
	{
		return Vector4<T>{std::abs(vec.x), std::abs(vec.y), std::abs(vec.z), std::abs(vec.w)};
	}


	template<typename T>
	[[nodiscard]] constexpr Vector4<T> min(const Vector4<T>& a, const Vector4<T>& b) noexcept
	{
		return Vector4<T>{((a.x < b.x) ? a.x : b.x), ((a.y < b.y ? a.y : b.y)), ((a.z < b.z ? a.z : b.z)), ((a.w < b.w ? a.w : b.w))};
	}

	template<typename T>
	[[nodiscard]] Vector4<T> max(const Vector4<T>& a, const Vector4<T>& b) noexcept
	{
		return Vector4<T>{((a.x > b.x) ? a.x : b.x), ((a.y > b.y ? a.y : b.y)), ((a.z > b.z ? a.z : b.z)), ((a.w > b.w ? a.w : b.w)) };
	}

	template<typename T>
	[[nodiscard]] constexpr Vector4<T> average(const Vector4<T>& a, const Vector4<T>& b) noexcept
	{
		return Vector4<T>{ (a.x + b.x) / 2, (a.y + b.y) / 2, (a.z + b.z) / 2, (a.w + b.w) / 2};
	}


	template<typename T>
	[[nodiscard]] constexpr Vector4<T> floor(const Vector4<T>& vec) noexcept
	{
		return { std::floor(vec.x), std::floor(vec.y), std::floor(vec.z), std::floor(vec.w) };
	}

	template<typename T>
	[[nodiscard]] constexpr Vector4<T> ceil(const Vector4<T>& vec) noexcept
	{
		return { std::ceil(vec.x), std::ceil(vec.y), std::ceil(vec.z), std::ceil(vec.w) };
	}


} // mpml