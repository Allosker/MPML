#pragma once
// MIT
// Allosker - 2025
// ===================================================
// Defines a 3D vector and the basic functions it possesses
// Although this class is small in size, it still has move/copy constructors defined as the types of its components could be of larger sizes (e.g. complex numbers)
// 
// Note:
//	This class acts as the foundation of all 4D based tensors.
//  Also bear in mind that this class behaves like a 3D vector, with for only change the integration of a 4th component: w.
//  However, this component does not participate in any operation and is as such merely here for convenience.
// ===================================================


// Dependencies
#include <array>
#include <utility>
#include <algorithm>
#include <stdexcept> // for: std::out_of_range()

#include "mpml/utilities/types/angle.hpp"
#include "mpml/vectors/vector3.hpp"


namespace mpml
{

	template<typename T>
	class Vector3;

	template<typename T>
	class Vector4
	{
	public:
		// Initialization


		constexpr Vector4() noexcept;
		// Performs a copy of values to all components
		constexpr Vector4(const T& values) noexcept;

		constexpr Vector4(const Vector4&) noexcept = default;
		constexpr Vector4& operator=(const Vector4&) noexcept = default;

		constexpr Vector4(const T& x_, const T& y_, const T& z_, const T& w_ = static_cast<T>(1)) noexcept;

		constexpr Vector4(const Vector2<T>& vec2_1, const Vector2<T>& vec2_2) noexcept;

		constexpr Vector4(const Vector3<T>& vec3, const T& scalar = static_cast<T>(1)) noexcept;

		template<typename U>
		constexpr Vector4(const Vector4<U>& vec) noexcept;


		// Operations

		[[nodiscard]] constexpr T dot(const Vector4<T>& vec) const noexcept;
		[[nodiscard]] constexpr Vector4<T> cross(const Vector4<T>& vec) const noexcept;

		[[nodiscard]] constexpr T distance(const Vector4<T>& vec) const noexcept;
		[[nodiscard]] constexpr T distance_squared(const Vector4<T>& vec) const noexcept;

		[[nodiscard]] constexpr Angle angle(const Vector4<T>& vec) const noexcept;
		[[nodiscard]] constexpr Vector4<T> project(const Vector4<T>& vec) const noexcept;
		[[nodiscard]] constexpr Vector4<T> reflect(const Vector4<T>& vec) const noexcept;
		[[nodiscard]] constexpr Vector4<T> reject(const Vector4<T>& vec) const noexcept;


		[[nodiscard]] constexpr T length() const noexcept;
		[[nodiscard]] constexpr T length_squared() const noexcept;

		[[nodiscard]] constexpr Vector4<T> normal() const noexcept;


		// Data related

		[[nodiscard]] constexpr T* data_ptr() noexcept;
		[[nodiscard]] constexpr const T* data_ptr() const noexcept;

		[[nodiscard]] constexpr T& operator[](size_t index);
		[[nodiscard]] constexpr const T& operator[](size_t index) const;


		// Overloads

		constexpr Vector4<T>& operator+=(const Vector4<T>& vec) noexcept;
		constexpr Vector4<T>& operator-=(const Vector4<T>& vec) noexcept;

		constexpr Vector4<T>& operator+=(const T& scalar) noexcept;
		constexpr Vector4<T>& operator-=(const T& scalar) noexcept;
		constexpr Vector4<T>& operator*=(const T& scalar) noexcept;
		constexpr Vector4<T>& operator/=(const T& scalar) noexcept;

		[[nodiscard]] constexpr Vector4<T> operator-() const noexcept;

		[[nodiscard]] constexpr bool operator==(const Vector4<T>& vec) const noexcept;


	// Class members

		union
		{
			struct { T x, y, z, w; };
			struct { T r, g, b, a; };
			struct { T u, v, h, t; };

			std::array<T, 4> data;
		};


	};
	// Common Types
	template<typename T>
	inline constexpr Vector4<T> Xaxis4{ 1,0,0,0 };

	template<typename T>
	inline constexpr Vector4<T> Yaxis4{ 0,1,0,0 };

	template<typename T>
	inline constexpr Vector4<T> Zaxis4{ 0,0,1,0 };

	template<typename T>
	inline constexpr Vector4<T> Waxis4{ 0,0,0,1 };



	// Class Definition



	// Intialization
	template<typename T>
	inline constexpr Vector4<T>::Vector4() noexcept
		: data{ T{}, T{}, T{}, T{} }
	{
	}

	template<typename T>
	inline constexpr Vector4<T>::Vector4(const T& values) noexcept
		: data{ values, values, values, values }
	{
	}

	template<typename T>
	inline constexpr Vector4<T>::Vector4(const T& x_, const T& y_, const T& z_, const T& w_) noexcept
		: x{x_}, y{y_}, z{z_}, w{w_}
	{
	}

	template<typename T>
	inline constexpr Vector4<T>::Vector4(const Vector2<T>& vec2_1, const Vector2<T>& vec2_2) noexcept
		: x{vec2_1.x}, y{vec2_1.y}, z{vec2_2.x}, w{vec2_2.y}
	{
	}

	template<typename T>
	inline constexpr Vector4<T>::Vector4(const Vector3<T>& vec3, const T& scalar) noexcept
		: data{ vec3.x, vec3.y, vec3.z, scalar }
	{
	}

	template<typename T>
	template<typename U>
	inline constexpr Vector4<T>::Vector4(const Vector4<U>& vec) noexcept
		: x{static_cast<T>(vec.x)}, y{ static_cast<T>(vec.y) }, z{ static_cast<T>(vec.z) }, w{ static_cast<T>(vec.w) }
	{
	}


	// Operations
	template<typename T>
	inline constexpr T Vector4<T>::dot(const Vector4<T>& vec) const noexcept
	{
		return T{ x * vec.x + y * vec.y + z * vec.z };
	}

	template<typename T>
	inline constexpr Vector4<T> Vector4<T>::cross(const Vector4<T>& vec) const noexcept
	{
		return Vector4<T>{
			y * vec.z - z * vec.y,
			z * vec.x - x * vec.z,
			x * vec.y - y * vec.x
		};
	}

	template<typename T>
	inline constexpr T Vector4<T>::distance(const Vector4<T>& vec) const noexcept
	{
		return T{ Vector4<T>{*this - vec}.length() };
	}

	template<typename T>
	inline constexpr T Vector4<T>::distance_squared(const Vector4<T>& vec) const noexcept
	{
		return T{ Vector4<T>{*this - vec}.length_squared() };
	}

	template<typename T>
	inline constexpr Angle Vector4<T>::angle(const Vector4<T>& vec) const noexcept
	{
		return static_cast<Angle>(T{ std::acos(dot(vec) / T{length() * vec.length()}) });
	}

	template<typename T>
	inline constexpr Vector4<T> Vector4<T>::project(const Vector4<T>& vec) const noexcept
	{
		Vector4<T> norm{ vec.normal() };
		return Vector4<T>{ dot(norm)* norm };
	}

	template<typename T>
	inline constexpr Vector4<T> Vector4<T>::reflect(const Vector4<T>& vec) const noexcept
	{
		return Vector4<T>{ *this - static_cast<T>(2) * project(vec)};
	}

	template<typename T>
	inline constexpr Vector4<T> Vector4<T>::reject(const Vector4<T>& vec) const noexcept
	{
		return Vector4<T>{*this - project(vec)};
	}

	template<typename T>
	inline constexpr T Vector4<T>::length() const noexcept
	{
		T lengthSquared{ x * x + y * y + z * z };

		if (lengthSquared == T{})
			return T{};
		return T{ std::sqrt(lengthSquared) };
	}

	template<typename T>
	inline constexpr T Vector4<T>::length_squared() const noexcept
	{
		return T{ x * x + y * y + z * z };
	}

	template<typename T>
	inline constexpr Vector4<T> Vector4<T>::normal() const noexcept
	{
		T len{ length() };

		if (len == T{})
			return T{};
		return Vector4<T>{ x / len, y / len, z / len };
	}


	// Data related
	template<typename T>
	inline constexpr T* Vector4<T>::data_ptr() noexcept
	{
		return data.data();
	}

	template<typename T>
	inline constexpr const T* Vector4<T>::data_ptr() const noexcept
	{
		return data.data();
	}

	template<typename T>
	inline constexpr T& Vector4<T>::operator[](size_t index)
	{
		if (index >= data.size())
			throw std::out_of_range("index is out of range in Vector4");
		return data[index];
	}

	template<typename T>
	inline constexpr const T& Vector4<T>::operator[](size_t index) const
	{
		if (index >= data.size())
			throw std::out_of_range("index is out of range in Vector4");
		return data[index];
	}

	// Member Overloads
	template<typename T>
	inline constexpr Vector4<T>& Vector4<T>::operator+=(const Vector4<T>& vec) noexcept
	{
		*this = *this + vec;
		return *this;
	}

	template<typename T>
	inline constexpr Vector4<T>& Vector4<T>::operator-=(const Vector4<T>& vec) noexcept
	{
		*this = *this - vec;
		return *this;
	}


	template<typename T>
	inline constexpr Vector4<T>& Vector4<T>::operator+=(const T& scalar) noexcept
	{
		*this = *this + scalar;
		return *this;
	}

	template<typename T>
	inline constexpr Vector4<T>& Vector4<T>::operator-=(const T& scalar) noexcept
	{
		*this = *this - scalar;
		return *this;
	}

	template<typename T>
	inline constexpr Vector4<T>& Vector4<T>::operator*=(const T& scalar) noexcept
	{
		*this = *this * scalar;
		return *this;
	}

	template<typename T>
	inline constexpr Vector4<T>& Vector4<T>::operator/=(const T& scalar) noexcept
	{
		*this = *this / scalar;
		return *this;
	}

	template<typename T>
	inline constexpr Vector4<T> Vector4<T>::operator-() const noexcept
	{
		return Vector4<T>{-x, -y};
	}

	template<typename T>
	inline constexpr bool Vector4<T>::operator==(const Vector4<T>& vec) const noexcept
	{
		return (x == vec.x && y == vec.y && z == vec.z);
	}


	// Overloads
	template<typename T>
	inline constexpr Vector4<T> operator+(const Vector4<T>& a, const Vector4<T>& b) noexcept
	{
		return Vector4<T>{a.x + b.x, a.y + b.y, a.z + b.z};
	}

	template<typename T>
	inline constexpr Vector4<T> operator-(const Vector4<T>& a, const Vector4<T>& b) noexcept
	{
		return Vector4<T>{a.x - b.x, a.y - b.y, a.z - b.z};
	}


	template<typename T>
	inline constexpr Vector4<T> operator*(const Vector4<T>& a, const T& k) noexcept
	{
		return Vector4<T>{a.x* k, a.y* k, a.z* k};
	}

	template<typename T>
	inline constexpr Vector4<T> operator/(const Vector4<T>& a, const T& k) noexcept
	{
		return Vector4<T>{a.x / k, a.y / k, a.z / k};
	}

	template<typename T>
	inline constexpr Vector4<T> operator+(const Vector4<T>& a, const T& k) noexcept
	{
		return Vector4<T>{a.x + k, a.y + k, a.z + k};
	}

	template<typename T>
	inline constexpr Vector4<T> operator-(const Vector4<T>& a, const T& k) noexcept
	{
		return Vector4<T>{a.x - k, a.y - k, a.z - k};
	}


	template<typename T>
	inline constexpr Vector4<T> operator*(const T& k, const Vector4<T>& a) noexcept
	{
		return Vector4<T>{ a.x* k, a.y* k, a.z* k};
	}

	template<typename T>
	inline constexpr Vector4<T> operator/(const T& k, const Vector4<T>& a) noexcept
	{
		return Vector4<T>{ k / a.x, k / a.y, k / a.z };
	}

	template<typename T>
	inline constexpr Vector4<T> operator+(const T& k, const Vector4<T>& a) noexcept
	{
		return Vector4<T>{a.x + k, a.y + k, a.z + k };
	}

	template<typename T>
	inline constexpr Vector4<T> operator-(const T& k, const Vector4<T>& a) noexcept
	{
		return Vector4<T>{k - a.x, k - a.y, k - a.z };
	}



} // mpml 