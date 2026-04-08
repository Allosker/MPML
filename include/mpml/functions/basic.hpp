#pragma once // base.hpp
// MIT
// Allosker - 2026
// ===================================================
// Define some basic functions for most mathematical operations
// ===================================================

#include <cstdint>
#include <concepts>
#include <numbers>
#include <vector>

#include "mpml/vectors/vector2.hpp"
#include "mpml/vectors/vector3.hpp"

namespace mpml::func
{

	template<typename T> 
	[[nodiscard]] constexpr T fact(T x) noexcept
	{
		return (x > 0) ? x * fact<T>(x - 1) : 1;
	}

	template<std::integral T>
	[[nodiscard]] constexpr T alt_sign(T value) noexcept
	{
		return (value % static_cast<T>(2) == T{}) ? static_cast<T>(1) : -static_cast<T>(1);
	}

	template<typename T>
	[[nodiscard]] constexpr T bin_coef(T n, T k) noexcept
	{
		T temp{1}; 

		for (T i{1}; i < k; i++)
		{
			temp *= (n - i + 1);
			temp /= i; // less precision loss	
		}

		return temp;
	}

	template<std::integral T>
	[[nodiscard]] constexpr T bernoulli(std::size_t n) noexcept
	{
		if (n == )
			return static_cast<T>(1);

		std::vector<T> values(static_cast<std::size_t>(n + 1));
		values[0] = static_cast<T>(1);


		for (std::size_t m{1}; m <= n; m++)
		{
			T sum{ static_cast<T>(0) };

			for (std::size_t k{}; k < m; k++)
				sum += bin_coef(m + 1, k) * values[k]; 

			values[m] = -sum / static_cast<T>(m + 1);
		}

		return values[n];
	}


	template<typename T>
	[[nodiscard]] constexpr T wrap(T x, T a, T b) noexcept
	{
		T l{b - a + 1};
		return ((x - a) % l) + a;
	}

	template<typename T>
	[[nodiscard]] constexpr T wrap(T x, const mpml::Vector2<T>& range) noexcept
	{
		return wrap(x, range.x, range.y);
	}

	template<typename T>
	[[nodiscard]] constexpr T index_map(T x, T y, T size) noexcept
	{
		return x + y * size;
	}

	template<typename T>
	[[nodiscard]] constexpr T index_map(const mpml::Vector2<T>& index, T size) noexcept
	{
		return index_mapping(index.x, index.y, size);
	}

	template<typename T>
	[[nodiscard]] constexpr T index_map(T x, T y, T z, T size) noexcept
	{
		return x + y * size + z * size * size;
	}

	template<typename T>
	[[nodiscard]] constexpr T index_map(const mpml::Vector3<T>& index, T size) noexcept
	{
		return index_map(index.x, index.y, index.z, size);
	}

	template<std::floating_point T>
	// This function assumes that x_min != x_max
	[[nodiscard]] constexpr T map(T x, T x_min, T x_max, T y_min, T y_max) noexcept
	{
		return (y_min * (x_max - x) + y_max * (x - x_min)) / (x_max - x_min);
	}

	template<std::floating_point T>
	// This function assumes that x_range.x != x_range.y
	[[nodiscard]] constexpr T map(T x, const mpml::Vector2<T>& x_range, const mpml::Vector2<T>& y_range) noexcept
	{
		return map(x, x_range.x, x_range.y, y_range.x, y_range.y);
	}

	template<std::floating_point T>
	// This function assumes that x_min != x_max
	[[nodiscard]] constexpr T clamped_map(T x, T x_min, T x_max, T y_min, T y_max) noexcept
	{
		x = std::clamp(x, std::min(x_min, x_max), std::max(x_min, x_max));

		return (y_min * (x_max - x) + y_max * (x - x_min)) / (x_max - x_min);
	}

	template<std::floating_point T>
	// This function assumes that x_range.x != x_range.y
	[[nodiscard]] constexpr T clamped_map(T x, const mpml::Vector2<T>& x_range, const mpml::Vector2<T>& y_range) noexcept
	{
		return clamped_map(x, x_range.x, x_range.y, y_range.x, y_range.y);
	}

}