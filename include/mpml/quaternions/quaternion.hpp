#pragma once
// MIT
// Allosker - 2025
// ===================================================
// Defines quaternions - acts as a four-tuple of complex numbers, hence its place here.
// ===================================================


#include <array>
#include <cmath>

#include "mpml/utilities/types/angle.hpp"

#include "mpml/vectors/vector3.hpp"

namespace mpml
{


template<typename T>
class Quaternion
{
public:

	// Initialization
	constexpr Quaternion() noexcept = default;

	constexpr Quaternion(const T& s, const T& x, const T& y, const T& z) noexcept;

	constexpr Quaternion(const T& s, const Vector3<T>& v) noexcept;

	constexpr Quaternion(const Quaternion<T>& q) noexcept;

	constexpr Quaternion<T>& operator=(const Quaternion<T>& q) noexcept;

	template<typename U>
	constexpr Quaternion(const Quaternion<U>& q) noexcept;


	// Operations
	[[nodiscard]] constexpr T dot(const Quaternion<T>& q) const noexcept;
	[[nodiscard]] constexpr T cross(const Quaternion<T>& q) const noexcept;

	[[nodiscard]] constexpr Quaternion<T> conjugate() const noexcept;
	[[nodiscard]] constexpr T length() const noexcept;
	[[nodiscard]] constexpr T length_squared() const noexcept;

	[[nodiscard]] constexpr Quaternion<T> normal() const noexcept;
	[[nodiscard]] constexpr Quaternion<T> inverse() const noexcept;

	[[nodiscard]] constexpr Quaternion<T> rotate(Angle angle, const Vector3<T>& axis) const noexcept;
	[[nodiscard]] constexpr Quaternion<T> rotate(Angle angle) const noexcept;


	// Data Related

	[[nodiscard]] constexpr T* data_ptr() noexcept;
	[[nodiscard]] constexpr const T* data_ptr() const noexcept;

	[[nodiscard]] constexpr T& operator[](size_t index);
	[[nodiscard]] constexpr const T& operator[](size_t index) const;


	// Member Overloads

	[[nodiscard]] constexpr Quaternion<T>& operator*=(const Quaternion<T>& q) noexcept;
	
	[[nodiscard]] constexpr Quaternion<T>& operator*=(const T& scalar) noexcept;
	[[nodiscard]] constexpr Quaternion<T>& operator/=(const T& scalar) noexcept;

	[[nodiscard]] constexpr auto operator<=>(const Quaternion<T>&) const noexcept = default;


// Class Members

	T s{};
	T x{};
	T y{};
	T z{};
	
	static constexpr size_t size{ 4 };

};



// Class Definition 



// Initialization
template<typename T>
constexpr inline Quaternion<T>::Quaternion(const T& s_, const T& x_, const T& y_, const T& z_) noexcept
	: s{ s_ }, x{ x_ }, y{ y_ }, z{ z_ }
{
}

template<typename T>
inline constexpr Quaternion<T>::Quaternion(const T& s_, const Vector3<T>& v) noexcept
	: s{ s_ }, x{ v.x }, y{ v.y }, z{ v.z }
{
}


template<typename T>
constexpr inline Quaternion<T>::Quaternion(const Quaternion<T>& q) noexcept
	: s{ q.s }, x{ q.x }, y{ q.y }, z{ q.z }
{
}

template<typename T>
constexpr inline Quaternion<T>& Quaternion<T>::operator=(const Quaternion<T>& q) noexcept
{
	if (this == &q)
		return *this;

	s = q.s;
	x = q.x;
	y = q.y;
	z = q.z;

	return *this;
}

template<typename T>
template<typename U>
constexpr Quaternion<T>::Quaternion(const Quaternion<U>& q) noexcept
	: s{ static_cast<T>(q.s) }, x{ static_cast<T>(q.x) }, y{ static_cast<T>(q.y) }, z{ static_cast<T>(q.z) }
{
}


// Operations
template<typename T>
inline constexpr T Quaternion<T>::dot(const Quaternion<T>& q) const noexcept
{
	return T{ s * q.s + x * q.x + y * q.y + z * q.z };
}

template<typename T>
inline constexpr T Quaternion<T>::cross(const Quaternion<T>& q) const noexcept
{
	return T{y* q.z - q.y * z + z * q.x - q.z * x + x * q.y - q.x * y};
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
	const Vector3<T> n_axis{ axis.normal() };

	const T s{ static_cast<T>(std::sin(angle.asRadians() / 2.)) };
	return Quaternion<T>{ static_cast<T>(std::cos(angle.asRadians() / 2.)), n_axis.x * s, n_axis.y * s, n_axis.z * s};
}

template<typename T>
inline constexpr Quaternion<T> Quaternion<T>::rotate(Angle angle) const noexcept
{
	const Vector3<T> n_axis = Vector3<T>{ x,y,z }.normal();

	const T s{ static_cast<T>(std::sin(angle.asRadians() / 2.)) };
	return Quaternion<T>{ static_cast<T>(std::cos(angle.asRadians() / 2.)), n_axis.x * s, n_axis.y * s, n_axis.z * s };
}


// Data Related
template<typename T>
inline constexpr T* Quaternion<T>::data_ptr() noexcept
{
	return &s;
}

template<typename T>
inline constexpr const T* Quaternion<T>::data_ptr() const noexcept
{
	return &s;
}

template<typename T>
inline constexpr T& Quaternion<T>::operator[](size_t index)
{
	if (index >= size)
		throw std::out_of_range("index is out of range in Quaternion");
	return *(&s + index);
}

template<typename T>
inline constexpr const T& Quaternion<T>::operator[](size_t index) const
{
	if (index >= size)
		throw std::out_of_range("index is out of range in Quaternion");
	return *(&s + index);
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