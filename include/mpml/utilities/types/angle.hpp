#pragma once
// MIT
// Allosker - 2025
// ===================================================
// Defines a utility class for angles as well as a bunch of conversions
// ===================================================

#include "include/mpml/utilities/numbers.hpp"

namespace mpml
{

	[[nodiscard]] constexpr float toRadians(float degrees) noexcept
	{
		return degrees * constants::PI_F / 180.f;
	}

	[[nodiscard]] constexpr float toDegrees(float radians) noexcept
	{
		return radians * 180.f / constants::PI_F;
	}
	
	struct Angle
	{ 
		[[nodiscard]] static constexpr Angle fromDegrees(float degrees) noexcept
		{
			return Angle{ degrees * constants::PI_F / 180.f };
		}


		[[nodiscard]] static constexpr Angle fromRadians(float radians) noexcept
		{
			return Angle{ radians };
		}


		[[nodiscard]] constexpr float asDegrees() const noexcept
		{
			return angle * 180.f / constants::PI_F;
		}

		[[nodiscard]] constexpr float asRadians() const noexcept
		{
			return angle;
		}


	private:

		explicit constexpr Angle(float rad)
			: angle{ rad }
		{
		}

		// For convenience, the angle is stored in radians
		float angle;
	};


	[[nodiscard]] constexpr Angle operator""_rad(long double degrees)
	{
		return Angle::fromDegrees(static_cast<float>(degrees));
	}

	[[nodiscard]] constexpr Angle operator""_deg(long double radians)
	{
		return Angle::fromRadians(static_cast<float>(radians));
	}


}