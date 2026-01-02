#pragma once
// MIT
// Allosker - 2025
// ===================================================
// Defines quaternions - acts as a four-tuple of complex numbers, hence its place here.
// ===================================================


#include <array>
#include <cmath>

#include "utilities/types/angle.hpp"

#include "vectors/vector3.hpp"

namespace mpml
{


template<typename T>
class Quaternion
{
public:

	// Initialization
	constexpr Quaternion() noexcept;

	constexpr Quaternion(const T& s, const T& x, const T& y, const T& z) noexcept;
	constexpr Quaternion(T&& s, T&& x, T&& y, T&& z) noexcept;

	constexpr Quaternion(const T& s, const Vector3<T>& v) noexcept;
	constexpr Quaternion(T&& s, Vector3<T>&& v) noexcept;

	constexpr Quaternion(const Quaternion<T>& q) noexcept;
	constexpr Quaternion(Quaternion<T>&& q) noexcept;

	constexpr Quaternion<T>& operator=(const Quaternion<T>& q) noexcept;
	constexpr Quaternion<T>& operator=(Quaternion<T>&& q) noexcept;


	// Operations
	[[nodiscard]] constexpr Quaternion<T>& dot(const Quaternion<T>& q) const noexcept;
	[[nodiscard]] constexpr Quaternion<T>& cross(const Quaternion<T>& q) const noexcept;

	[[nodiscard]] constexpr Quaternion<T> conjugate() const noexcept;
	[[nodiscard]] constexpr T length() const noexcept;
	[[nodiscard]] constexpr T length_squared() const noexcept;

	[[nodiscard]] constexpr Quaternion<T> normal() const noexcept;
	[[nodiscard]] constexpr Quaternion<T> inverse() const noexcept;

	[[nodiscard]] constexpr Quaternion<T> rotate(Angle angle, const Vector3<T>& axis) const noexcept;
	[[nodiscard]] constexpr Quaternion<T> rotate(Angle angle) const noexcept;


	// Data Related

	[[nodiscard]] constexpr T* data_ptr() const noexcept;

	// Member Overloads

	constexpr Quaternion<T>& operator*=(const Quaternion<T>& q) noexcept;
	
	constexpr Quaternion<T>& operator*=(const T& scalar) noexcept;
	constexpr Quaternion<T>& operator/=(const T& scalar) noexcept;


// Class Members

	union
	{
		struct { T s, x, y, z; };
		struct { T a, bi, cj, dk; };

		std::array<T, 4> data;
	};
	

};



// Class Definition 



template<typename T>
inline constexpr Quaternion<T>::Quaternion() noexcept
	: data{ T{}, T{}, T{}, T{} }
{
}

// Initialization
template<typename T>
constexpr inline Quaternion<T>::Quaternion(const T& s, const T& x, const T& y, const T& z) noexcept
	: data{s,x,y,z}
{
}

template<typename T>
constexpr inline Quaternion<T>::Quaternion(T&& s, T&& x, T&& y, T&& z) noexcept
	: data{ std::move(s), std::move(x), std::move(y), std::move(z)}
{
}

template<typename T>
inline constexpr Quaternion<T>::Quaternion(const T& s, const Vector3<T>& v) noexcept
	: data{s, v.x, v.y, v.z}
{
}

template<typename T>
inline constexpr Quaternion<T>::Quaternion(T&& s, Vector3<T>&& v) noexcept
	: data{ std::move(s), std::move(v.x), std::move(v.y), std::move(v.z) }
{
}


template<typename T>
constexpr inline Quaternion<T>::Quaternion(const Quaternion<T>& q) noexcept
	: data{q.s, q.x, q.y, q.z}
{
}

template<typename T>
constexpr inline Quaternion<T>::Quaternion(Quaternion<T>&& q) noexcept
	: data{ std::move(q.s), std::move(q.x), std::move(q.y), std::move(q.z)}
{
}


template<typename T>
constexpr inline Quaternion<T>& Quaternion<T>::operator=(const Quaternion<T>& q) noexcept
{
	if (this == &q)
		return *this;

	data = q.data;

	return *this;
}

template<typename T>
constexpr inline Quaternion<T>& Quaternion<T>::operator=(Quaternion<T>&& q) noexcept
{
	if (this == &q)
		return *this;

	data = std::move(q.data);

	return *this;
}


// Operations
template<typename T>
inline constexpr Quaternion<T>& Quaternion<T>::dot(const Quaternion<T>& q) const noexcept
{
	return Quaternion<T>{ s * q.s + x * q.x + y * q.y + z * q.z };
}

template<typename T>
inline constexpr Quaternion<T>& Quaternion<T>::cross(const Quaternion<T>& q) const noexcept
{
	return Quaternion<T>{y* q.z - q.y * z + z * q.x - q.z * x + x * q.y - q.x * y};
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
	return T{ s * s + x * x + y * y + z * z };
}

template<typename T>
inline constexpr Quaternion<T> Quaternion<T>::normal() const noexcept
{
	T len{ length() };

	if (len == T{})
		return Quaternion<T>{};

	return Quaternion<T>{ *this / len };
}

template<typename T>
inline constexpr Quaternion<T> Quaternion<T>::inverse() const noexcept
{
	T len{ length_squared() };

	if (len == T{})
		return Quaternion<T>{};

	return Quaternion<T>{ conjugate() / len };
}

template<typename T>
inline constexpr Quaternion<T> Quaternion<T>::rotate(Angle angle, const Vector3<T>& axis) const noexcept
{
	Vector3<T> n_axis{ axis.normal() };

	T s{ static_cast<T>(std::sin(angle.asRadians() / 2.)) };
	return Quaternion<T>{ static_cast<T>(std::cos(angle.asRadians() / 2.)), n_axis.x * s, n_axis.y * s, n_axis.z * s};
}

template<typename T>
inline constexpr Quaternion<T> Quaternion<T>::rotate(Angle angle) const noexcept
{
	Vector3<T> n_axis = Vector3<T>{ x,y,z }.normal();

	T s{ static_cast<T>(std::sin(angle.asRadians() / 2.)) };
	return Quaternion<T>{ static_cast<T>(std::cos(angle.asRadians() / 2.)), n_axis.x * s, n_axis.y * s, n_axis.z * s };
}


// Data Related
template<typename T>
inline constexpr T* Quaternion<T>::data_ptr() const noexcept
{
	return data.data();
}


// Member Overloads
template<typename T>
inline constexpr Quaternion<T>& Quaternion<T>::operator*=(const Quaternion<T>& q) noexcept
{
	*this = *this * q;

	return *this;
}

template<typename T>
inline constexpr Quaternion<T>& Quaternion<T>::operator*=(const T& scalar) noexcept
{
	*this = *this * scalar;

	return *this;
}

template<typename T>
inline constexpr Quaternion<T>& Quaternion<T>::operator/=(const T& scalar) noexcept
{
	*this = *this / scalar;

	return *this;
}


// Overloads
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
inline constexpr Quaternion<T> operator*(const Quaternion<T>& q1, const T& scalar) noexcept
{
	return Quaternion<T>{ q1.s * scalar, q1.x * scalar, q1.y * scalar, q1.z * scalar};
}

template<typename T>
inline constexpr Quaternion<T> operator/(const Quaternion<T>& q1, const T& scalar) noexcept
{
	return Quaternion<T>{ q1.s / scalar, q1.x / scalar, q1.y / scalar, q1.z / scalar};
}



} // mpml