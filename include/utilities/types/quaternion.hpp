#pragma once
// MIT
// Allosker - 2025
// ===================================================
// Defines quaternions - acts as a four-tuple of complex numbers, hence its place here.
// ===================================================


#include <array>
#include <cmath>

#include "utilities/types/angle.hpp"

namespace mpml
{


template<typename T>
class Quaternion
{
public:

	// Initialization


	// Operations
	[[nodiscard]] constexpr Quaternion<T>& dot(const Quaternion<T>& q) const noexcept;
	[[nodiscard]] constexpr Quaternion<T>& cross(const Quaternion<T>& q) const noexcept;

	[[nodiscard]] constexpr Quaternion<T> conjugate() const noexcept;
	[[nodiscard]] constexpr T length() const noexcept;
	[[nodiscard]] constexpr T length_squared() const noexcept;

	[[nodiscard]] constexpr Quaternion<T> normal() const noexcept;
	[[nodiscard]] constexpr Quaternion<T> inverse() const noexcept;

	[[nodiscard]] constexpr Quaternion<T> rotate(Angle angle) const noexcept;


	// Data Related

	constexpr T* data_ptr() const noexcept;

	// Member Overloads


// Class Members

	union
	{
		struct { T s, x, y, z; };
		struct { T a, bi, cj, dk; };

		std::array<T, 4> data;
	};
	

};


// Operations
template<typename T>
inline constexpr Quaternion<T>& Quaternion<T>::dot(const Quaternion<T>& q) const noexcept
{
	return Quaternion<T>{ q1.s* q2.s + q1.x * q2.x + q1.y * q2.y + q1.z * q2.z };
}

template<typename T>
inline constexpr Quaternion<T>& Quaternion<T>::cross(const Quaternion<T>& q) const noexcept
{
	return Quaternion<T>{q1.y * q2.z - q2.y * q1.z + q1.z * q2.x - q2.z * q1.x + q1.x * q2.y - q2.x * q1.y}
}

template<typename T>
inline constexpr Quaternion<T> Quaternion<T>::conjugate() const noexcept
{
	return Quaternion<T>{s, -x, -y, -z};
}

template<typename T>
inline constexpr T Quaternion<T>::length() const noexcept
{
	T len_sqd{ length_squared() };

	if (len_sqd == T{})
		return T{};

	return T{ std::sqrt(len_sqd) };
}

template<typename T>
inline constexpr T Quaternion<T>::length_squared() const noexcept
{
	return T{ *this * conjugate() };
}

template<typename T>
inline constexpr Quaternion<T> Quaternion<T>::normal() const noexcept
{
	T len{ length() };

	if (len == T{})
		return T{};

	return Quaternion<T>{ *this / len };
}

template<typename T>
inline constexpr Quaternion<T> Quaternion<T>::inverse() const noexcept
{
	T len{ length_squared() };

	if (len == T{})
		return T{};

	return Quaternion<T>{ conjugate() / len };
}

template<typename T>
inline constexpr Quaternion<T> Quaternion<T>::rotate(Angle angle) const noexcept
{
	T s{ std::sin(angle.radians() / 2) };
	return Quaternion<T>{ std::cos(angle.radians() / 2), x * s, y * s, z * s};
}


// Data Related
template<typename T>
inline constexpr T* Quaternion<T>::data_ptr() const noexcept
{
	return &data[0];
}


// Overloads
template<typename T>
inline constexpr Quaternion<T> operator+(const Quaternion<T>& q1, const Quaternion<T>& q2) noexcept
{
	return Quaternion<T>{ q1.s + q2.s, q1.x + q2.x, q1.y + q2.y, q1.z + q2.z};
}

template<typename T>
inline constexpr Quaternion<T> operator-(const Quaternion<T>& q1, const Quaternion<T>& q2) noexcept
{
	return Quaternion<T>{ q1.s - q2.s, q1.x - q2.x, q1.y - q2.y, q1.z - q2.z};
}

template<typename T>
inline constexpr Quaternion<T> operator*(const Quaternion<T>& q1, const Quaternion<T>& q2) noexcept
{
	return Quaternion<T>
	{
		q1.s * q2.s - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z,
		q1.s * q2.x + q2.s * q1.x + q1.y * q2.z - q2.y * q1.z,
		q1.s * q2.y + q2.s * q1.y + q1.z * q2.x - q2.z * q1.x,
		q1.s * q2.z + q2.s * q1.z + q1.x * q2.y - q2.x * q1.y
	};
}


template<typename T>
inline constexpr Quaternion<T> operator*(const T& scalar, const Quaternion<T>& q1) noexcept
{
	return Quaternion<T>{ q1.s * scalar, q1.x * scalar, q1.y * scalar, q1.z * scalar};
}

template<typename T>
inline constexpr Quaternion<T> operator*(const T& scalar, const Quaternion<T>& q1) noexcept
{
	return Quaternion<T>{ q1.s / scalar, q1.x / scalar, q1.y / scalar, q1.z / scalar};
}



} // mpml