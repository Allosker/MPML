#pragma once
// MIT
// Allosker - 2025
// ===================================================
// Defines some overload for Quaternions as well as rotation utilities
// ===================================================

#include "mpml/quaternions/quaternion.hpp"

#include "mpml/matrices/matrix3.hpp"
#include "mpml/matrices/matrix4.hpp"

#include "mpml/utilities/types/angle.hpp"

namespace mpml
{

	template<typename T>
	[[nodiscard]] constexpr Matrix3<T> rotation_matrix(const Quaternion<T>& q) noexcept
	{
		return Matrix3<T>
		{
			1 - 2 * (q.y * q.y + q.z * q.z), 2 * (q.x * q.y - q.a * q.z), 2 * (q.x * q.z + q.a * q.y),
			2 * (q.x * q.y + q.a * q.z), 1 - 2 * (q.x * q.x + q.z * q.z), 2 * (q.y * q.z - q.a * q.x),
			2 * (q.x * q.z - q.a * q.y), 2 * (q.y * q.z + q.a * q.x), 1 - 2 * (q.x * q.x + q.y * q.y)
		};
	}

	template<typename T>
	[[nodiscard]] constexpr Quaternion<T> rotation_as_quaternion(Angle angle, const Vector3<T>& vector, const Vector3<T>& axis) noexcept
	{
		Quaternion<T> rotation_q{ 0, axis };
		rotation_q = rotation_q.rotate(angle);
		
		const Quaternion<T> rotating_q{ 0, vector };

		const Quaternion<T> rotated_q{ rotation_q * rotating_q * rotation_q.conjugate() };


		return rotated_q;
	}

	template<typename T>
	[[nodiscard]] constexpr Vector3<T> rotation_as_vector(Angle angle, const Vector3<T>& vector, const Vector3<T>& axis) noexcept
	{
		const Quaternion<T> rotated{ rotation_as_quaternion<T>(angle, vector, axis) };

		return Vector3<T>{ rotated.x, rotated.y, rotated.z };
	}

	template<typename T> 
	[[nodiscard]] constexpr Matrix4<T> rotate(Angle angle, const Vector3<T>& axis) noexcept
	{
		return rotation_matrix<T>(Quaternion<T>{ 0, axis }.rotate(angle));
	}

	template<typename T>
	[[nodiscard]] constexpr Matrix4<T> rotate(const Matrix4<T>& mat, Angle angle, const Vector3<T>& axis) noexcept
	{
		return rotation_matrix<T>(Quaternion<T>{ 0, axis }.rotate(angle));
	}

}