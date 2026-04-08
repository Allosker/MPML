#pragma once
// MIT
// Allosker - 2026
// ===================================================
// Defines a utility class for angles as well as a bunch of conversions
// ===================================================

#include <numbers>

namespace mpml
{
	
	template <typename T = float>
	[[nodiscard]] static constexpr T toRadians(T deg) noexcept
	{
		return deg * std::numbers::pi_v<T> / static_cast<T>(180.f);
	}

	template <typename T = float>
	[[nodiscard]] static constexpr T toDegrees(T rad) noexcept
	{
		return rad * static_cast<T>(180) / std::numbers::pi_v<T>;
	}


	template <typename T = float>
	struct Angle
	{ 
		[[nodiscard]] static constexpr Angle fromDegrees(T deg) noexcept
		{
			return Angle{ deg * std::numbers::pi_v<T> / static_cast<T>(180) };
		}

		[[nodiscard]] static constexpr Angle fromRadians(T rad) noexcept
		{
			return Angle{ rad };
		}


		[[nodiscard]] constexpr T asDegrees() const noexcept
		{
			return angle_rad * static_cast<T>(180) / std::numbers::pi_v<T>;
		}

		[[nodiscard]] constexpr T asRadians() const noexcept
		{
			return angle_rad;
		}


	private:

		explicit constexpr Angle(T angle)
			: angle_rad{ angle }
		{
		}

		T angle_rad;
	};


} // mpml

namespace mpml_literals
{
	[[nodiscard]] constexpr mpml::Angle<> operator""_rad(long double rad)
	{
		return mpml::Angle<>::fromRadians(static_cast<double>(rad));
	}

	[[nodiscard]] constexpr mpml::Angle<> operator""_deg(long double deg)
	{
		return mpml::Angle<>::fromDegrees(static_cast<double>(deg));
	}
}