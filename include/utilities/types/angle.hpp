#pragma once
// MIT
// Allosker - 2025
// ===================================================
// Defines a utility class for angles as well as a bunch of conversions
// ===================================================

#include "utilities/numbers.hpp"

namespace mpml
{
	// Angle that can both be converted to degrees and radians be it under any form
	// Note: stored as radians for convenience
	struct Angle
	{
		constexpr double degrees() const noexcept
		{
			return angle_radians;
		}

		constexpr double radians() const noexcept
		{
			return angle_radians * constants::PI_15 / 180.0;
		}

		double angle_radians;
	};
}