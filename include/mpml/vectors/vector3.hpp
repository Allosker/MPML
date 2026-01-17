#pragma once
// MIT
// Allosker - 2025
// ===================================================
// Defines a 3D vector and the basic functions it possesses
// Although this class is small in size, it still has move/copy constructors defined as the types of its components could be of larger sizes (e.g. complex numbers)
// 
// Note:
//	This class acts as the foundation of all 3D based tensors.
// ===================================================


// Dependencies
#include <array>
#include <cmath>
#include <utility>
#include <algorithm>
#include <stdexcept> // for: std::out_of_range()

#include "mpml/utilities/types/angle.hpp"
#include "mpml/vectors/vector2.hpp"


namespace mpml
{


	template<typename T>
	class Vector2;

	template<typename T>
	class Vector3
	{
	public:
		// Initialization
	
		constexpr Vector3() noexcept;
		// Performs a copy of values to all components
		constexpr Vector3(const T& values) noexcept;

		constexpr Vector3(const Vector3&) noexcept = default;
		constexpr Vector3& operator=(const Vector3&) noexcept = default;

		constexpr Vector3(Vector3&&) noexcept = default;
		constexpr Vector3& operator=(Vector3&&) noexcept = default;

		constexpr Vector3(const T& x_, const T& y_, const T& z_) noexcept;
		constexpr Vector3(T&& x_, T&& y_, T&& z_) noexcept;

		constexpr Vector3(const Vector2<T>& vec2, const T& scalar) noexcept;
		constexpr Vector3(Vector2<T>&& vec2, T&& scalar) noexcept;


		// Operations

		[[nodiscard]] constexpr T dot(const Vector3<T>& vec) const noexcept;
		[[nodiscard]] constexpr Vector3<T> cross(const Vector3<T>& vec) const noexcept;

		[[nodiscard]] constexpr T distance(const Vector3<T>& vec) const noexcept;
		[[nodiscard]] constexpr T distance_squared(const Vector3<T>& vec) const noexcept;

		[[nodiscard]] constexpr Angle angle(const Vector3<T>& vec) const noexcept;
		[[nodiscard]] constexpr Vector3<T> project(const Vector3<T>& vec) const noexcept;
		[[nodiscard]] constexpr Vector3<T> reflect(const Vector3<T>& vec) const noexcept;
		[[nodiscard]] constexpr Vector3<T> reject(const Vector3<T>& vec) const noexcept;


		[[nodiscard]] constexpr T length() const noexcept;
		[[nodiscard]] constexpr T length_squared() const noexcept;

		[[nodiscard]] constexpr Vector3<T> normal() const noexcept;


		// Data related

		[[nodiscard]] constexpr T* data_ptr() noexcept;
		[[nodiscard]] constexpr const T* data_ptr() const noexcept;

		[[nodiscard]] constexpr T& operator[](size_t index);
		[[nodiscard]] constexpr const T& operator[](size_t index) const;


		// Overloads

		constexpr Vector3<T>& operator+=(const Vector3<T>& vec) noexcept;
		constexpr Vector3<T>& operator-=(const Vector3<T>& vec) noexcept;

		constexpr Vector3<T>& operator+=(const T& scalar) noexcept;
		constexpr Vector3<T>& operator-=(const T& scalar) noexcept;
		constexpr Vector3<T>& operator*=(const T& scalar) noexcept;
		constexpr Vector3<T>& operator/=(const T& scalar) noexcept;

		[[nodiscard]] constexpr Vector3<T> operator-() const noexcept;
		constexpr bool operator==(const Vector3<T>& vec) const noexcept;

		// Class members

		union
		{
			struct { T x, y, z; };
			struct { T r, g, b; };
			struct { T h, s, v; };

			std::array<T, 3> data;
		};


	};
	// Common Types
	template<typename T>
	inline constexpr Vector3<T> Xaxis3{ 1,0,0 };

	template<typename T>
	inline constexpr Vector3<T> Yaxis3{ 0,1,0 };

	template<typename T>
	inline constexpr Vector3<T> Zaxis3{ 0,0,1 };



	// Class Definition



	// Intialization

	template<typename T>
	inline constexpr Vector3<T>::Vector3() noexcept
		: data{ T{}, T{}, T{} }
	{
	}

	template<typename T>
	inline constexpr Vector3<T>::Vector3(const T& values) noexcept
		: data{values, values, values}
	{
	}

	template<typename T>
	inline constexpr Vector3<T>::Vector3(const T& x_, const T& y_, const T& z_) noexcept
		: data{x_, y_, z_}
	{
	}

	template<typename T>
	inline constexpr Vector3<T>::Vector3(T&& x_, T&& y_, T&& z_) noexcept
		: data{ std::move(x_), std::move(y_), std::move(z_)}
	{
	}

	template<typename T>
	inline constexpr Vector3<T>::Vector3(const Vector2<T>& vec2, const T& scalar) noexcept
		: data{ vec2.x, vec2.y, scalar }
	{
	}

	template<typename T>
	inline constexpr Vector3<T>::Vector3(Vector2<T>&& vec2, T&& scalar) noexcept
		: data{ std::move(vec2.x), std::move(vec2.y), std::move(scalar) }
	{
	}




	// Operations

	template<typename T>
	inline constexpr T Vector3<T>::dot(const Vector3<T>& vec) const noexcept
	{
		return T{x * vec.x + y * vec.y + z * vec.z};
	}

	template<typename T>
	inline constexpr Vector3<T> Vector3<T>::cross(const Vector3<T>& vec) const noexcept
	{
		return Vector3<T>{ 
			y * vec.z - z * vec.y,
			z * vec.x - x * vec.z,
			x * vec.y - y * vec.x
		};
	}

	template<typename T>
	inline constexpr T Vector3<T>::distance(const Vector3<T>& vec) const noexcept
	{
		return T{ Vector3<T>{*this - vec}.length() };
	}

	template<typename T>
	inline constexpr T Vector3<T>::distance_squared(const Vector3<T>& vec) const noexcept
	{
		return T{ Vector3<T>{*this - vec}.length_squared() };
	}

	template<typename T>
	inline constexpr Angle Vector3<T>::angle(const Vector3<T>& vec) const noexcept
	{
		return static_cast<Angle>(T{std::acos(dot(vec) / T{length() *  vec.length()})});
	}

	template<typename T>
	inline constexpr Vector3<T> Vector3<T>::project(const Vector3<T>& vec) const noexcept
	{
		Vector3<T> norm{ vec.normal() };
		return Vector3<T>{ dot(norm) * norm };
	}

	template<typename T>
	inline constexpr Vector3<T> Vector3<T>::reflect(const Vector3<T>& vec) const noexcept
	{
		return Vector3<T>{ *this - static_cast<T>(2) * project(vec)};
	}

	template<typename T>
	inline constexpr Vector3<T> Vector3<T>::reject(const Vector3<T>& vec) const noexcept
	{
		return Vector3<T>{*this - project(vec)};
	}

	template<typename T>
	inline constexpr T Vector3<T>::length() const noexcept
	{
		T lengthSquared{ x * x + y * y + z * z };

		if (lengthSquared == T{})
			return T{};
		return T{ std::sqrt(lengthSquared) };
	}

	template<typename T>
	inline constexpr T Vector3<T>::length_squared() const noexcept
	{
		return T{ x * x + y * y + z * z };
	}

	template<typename T>
	inline constexpr Vector3<T> Vector3<T>::normal() const noexcept
	{
		T len{ length() };
	
		if (len == T{})
			return T{};
		return Vector3<T>{ x / len, y / len, z / len};
	}


	// Data related
	template<typename T>
	inline constexpr T* Vector3<T>::data_ptr() noexcept
	{
		return data.data();
	}

	template<typename T>
	inline constexpr const T* Vector3<T>::data_ptr() const noexcept
	{
		return data.data();
	}

	template<typename T>
	inline constexpr T& Vector3<T>::operator[](size_t index)
	{
		if (index >= data.size())
			throw std::out_of_range("index is out of range in vector3");
		return data[index];
	}

	template<typename T>
	inline constexpr const T& Vector3<T>::operator[](size_t index) const
	{
		if (index >= data.size())
			throw std::out_of_range("index is out of range in vector3");
		return data[index];
	}

	// Member Overloads
	template<typename T>
	inline constexpr Vector3<T>& Vector3<T>::operator+=(const Vector3<T>& vec) noexcept
	{
		*this = *this + vec;
		return *this;
	}

	template<typename T>
	inline constexpr Vector3<T>& Vector3<T>::operator-=(const Vector3<T>& vec) noexcept
	{
		*this = *this - vec;
		return *this;
	}


	template<typename T>
	inline constexpr Vector3<T>& Vector3<T>::operator+=(const T& scalar) noexcept
	{
		*this = *this + scalar;
		return *this;
	}

	template<typename T>
	inline constexpr Vector3<T>& Vector3<T>::operator-=(const T& scalar) noexcept
	{
		*this = *this - scalar;
		return *this;
	}

	template<typename T>
	inline constexpr Vector3<T>& Vector3<T>::operator*=(const T& scalar) noexcept
	{
		*this = *this * scalar;
		return *this;
	}

	template<typename T>
	inline constexpr Vector3<T>& Vector3<T>::operator/=(const T& scalar) noexcept
	{
		*this = *this / scalar;
		return *this;
	}

	template<typename T>
	inline constexpr Vector3<T> Vector3<T>::operator-() const noexcept
	{
		return Vector3<T>{-x, -y};
	}

	template<typename T>
	inline constexpr bool Vector3<T>::operator==(const Vector3<T>& vec) const noexcept
	{
		return (x == vec.x && y == vec.y && z == vec.z);
	}


	// Overloads
	template<typename T>
	inline constexpr Vector3<T> operator+(const Vector3<T>& a, const Vector3<T>& b) noexcept
	{
		return Vector3<T>{a.x + b.x, a.y + b.y, a.z + b.z};
	}

	template<typename T>
	inline constexpr Vector3<T> operator-(const Vector3<T>& a, const Vector3<T>& b) noexcept
	{
		return Vector3<T>{a.x - b.x, a.y - b.y, a.z - b.z};
	}


	template<typename T>
	inline constexpr Vector3<T> operator*(const Vector3<T>& a, const T& k) noexcept
	{
		return Vector3<T>{a.x * k, a.y * k, a.z * k};
	}

	template<typename T>
	inline constexpr Vector3<T> operator/(const Vector3<T>& a, const T& k) noexcept
	{
		return Vector3<T>{a.x / k, a.y / k, a.z / k};
	}

	template<typename T>
	inline constexpr Vector3<T> operator+(const Vector3<T>& a, const T& k) noexcept
	{
		return Vector3<T>{a.x + k, a.y + k, a.z + k};
	}

	template<typename T>
	inline constexpr Vector3<T> operator-(const Vector3<T>& a, const T& k) noexcept
	{
		return Vector3<T>{a.x - k, a.y - k, a.z - k};
	}


	template<typename T>
	inline constexpr Vector3<T> operator*(const T& k, const Vector3<T>& a) noexcept
	{
		return Vector3<T>{ a.x * k, a.y * k, a.z * k};
	}

	template<typename T>
	inline constexpr Vector3<T> operator/(const T& k, const Vector3<T>& a) noexcept
	{
		return Vector3<T>{ k / a.x, k / a.y, k / a.z };
	}

	template<typename T>
	inline constexpr Vector3<T> operator+(const T& k, const Vector3<T>& a) noexcept
	{
		return Vector3<T>{a.x + k, a.y + k, a.z + k };
	}

	template<typename T>
	inline constexpr Vector3<T> operator-(const T& k, const Vector3<T>& a) noexcept
	{
		return Vector3<T>{k - a.x, k - a.y, k - a.z };
	}



} // mpml 