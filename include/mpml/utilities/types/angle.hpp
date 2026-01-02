#pragma once
// MIT
// Allosker - 2025
// ===================================================
// Defines a utility class for angles as well as a bunch of conversions
// ===================================================

#include "utilities/numbers.hpp"

namespace mpml
{
	
	
	struct Angle
	{ 
		static constexpr Angle fromDegrees(float degrees) noexcept
		{
			return degrees * constants::PI_F / 180.f;
		}


		static constexpr Angle fromRadians(float radians) noexcept
		{
			return radians;
		}


		constexpr float asDegrees() const noexcept
		{
			return angle * 180.f / constants::PI_F;
		}

		constexpr float asRadians() const noexcept
		{
			return angle;
		}


	private:

		constexpr Angle(float deg)
			: angle{ deg }
		{
		}

		// For convenience, the angle is stored in radians
		float angle;
	};


	constexpr Angle operator""_rad(long double degrees)
	{
		return Angle::fromDegrees(static_cast<float>(degrees));
	}

	constexpr Angle operator""_deg(long double radians)
	{
		return Angle::fromRadians(static_cast<float>(radians));
	}


}