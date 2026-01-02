#pragma once
// MIT
// Allosker - 2025
// ===================================================
// Defines a 2D vector and the basic functions it possesses
// Although this class is small in size, it still has move/copy constructors defined as the types of its components could be of larger sizes (e.g. complex numbers)
// Note:
//	This class acts as the foundation of all 2D based tensors.
// ===================================================


// Dependencies
#include <array>
#include <cmath>
#include <xutility>
#include <stdexcept> // for: std::out_of_range()

#include "utilities/types/angle.hpp"


namespace mpml
	// Main Namespace
{


	template<typename T>
	class Vector2
	{
	public:

		// Initialization

		constexpr Vector2() noexcept;
		// Performs a copy of values to all components
		constexpr Vector2(const T& values) noexcept;

		constexpr Vector2(const T& x_, const T& y_) noexcept;
		constexpr Vector2(T&& x_, T&& y_) noexcept;




		~Vector2() = default;
	

		// Operations

		[[nodiscard]] constexpr T dot(const Vector2<T>& vec) const noexcept;

		[[nodiscard]] constexpr T distance(const Vector2<T>& vec) const noexcept;
		[[nodiscard]] constexpr T distance_squared(const Vector2<T>& vec) const noexcept;

		[[nodiscard]] constexpr Angle angle(const Vector2<T>& vec) const noexcept;
		[[nodiscard]] constexpr Vector2<T> project(const Vector2<T>& vec) const noexcept;
		[[nodiscard]] constexpr Vector2<T> reflect(const Vector2<T>& vec) const noexcept;
		[[nodiscard]] constexpr Vector2<T> reject(const Vector2<T>& vec) const noexcept;


		[[nodiscard]] constexpr Vector2<T> perpendicular() const noexcept;
		[[nodiscard]] constexpr Vector2<T> rotate(Angle angle) const noexcept;

		[[nodiscard]] constexpr T length() const noexcept;
		[[nodiscard]] constexpr T length_squared() const noexcept;

		[[nodiscard]] constexpr Vector2<T> normal() const noexcept;




		// Data related

		[[nodiscard]] constexpr const T* data_ptr() const noexcept;
	
		[[nodiscard]] constexpr T& operator[](size_t index);
		[[nodiscard]] constexpr const T& operator[](size_t index) const;


		// Overloads

		constexpr Vector2<T>& operator+=(const Vector2<T>& vec) noexcept;
		constexpr Vector2<T>& operator-=(const Vector2<T>& vec) noexcept;

		constexpr Vector2<T>& operator+=(const T& scalar) noexcept;
		constexpr Vector2<T>& operator-=(const T& scalar) noexcept;
		constexpr Vector2<T>& operator*=(const T& scalar) noexcept;
		constexpr Vector2<T>& operator/=(const T& scalar) noexcept;

		[[nodiscard]] constexpr Vector2<T> operator-() const noexcept;
		[[nodiscard]] constexpr bool operator!() const noexcept;
		constexpr bool operator==(const Vector2<T>& vec) const noexcept;

	
	// Class members

		union
		{
			struct { T x, y; };
			struct { T r, g; };
			struct { T u, v; };

			std::array<T, 2> data;
		};


	};
	// Common Types
	template<typename T>
	constexpr static Vector2 Xaxis2{ 1,0 };

	template<typename T>
	constexpr static Vector2 Yaxis2{ 0,1 };



	// Class definition


	// Initialization
	template<typename T>
	inline constexpr Vector2<T>::Vector2() noexcept
		: data{ T{},T{} }
	{
	}

	template<typename T>
	inline constexpr Vector2<T>::Vector2(const T& values) noexcept
		: data{values, values}
	{
	}

	template<typename T>
	inline constexpr Vector2<T>::Vector2(const T& x_, const T& y_) noexcept
		: data{x_, y_}
	{
	}

	template<typename T>
	inline constexpr Vector2<T>::Vector2(T&& x_, T&& y_) noexcept
		: data{ std::move(x_), std::move(y_) }
	{
	}


	// Operations
	template<typename T>
	inline constexpr T Vector2<T>::dot(const Vector2<T>& vec) const noexcept
	{
		return T{x * vec.x + y * vec.y};
	}

	template<typename T>
	inline constexpr T Vector2<T>::distance(const Vector2<T>& vec) const noexcept
	{
		return Vector2<T>{*this - vec}.length();
	}

	template<typename T>
	inline constexpr T Vector2<T>::distance_squared(const Vector2<T>& vec) const noexcept
	{
		return Vector2<T>{*this - vec}.length_squared();
	}

	template<typename T>
	inline constexpr Angle Vector2<T>::angle(const Vector2<T>& vec) const noexcept
	{
		return static_cast<Angle>(std::acos(dot(vec) / T{length() * vec.length()}));
	}

	template<typename T>
	inline constexpr Vector2<T> Vector2<T>::project(const Vector2<T>& vec) const noexcept
	{
		Vector2<T> norm{ vec.normal() };
		return Vector2<T>{ dot(norm) * norm };
	}

	template<typename T>
	inline constexpr Vector2<T> Vector2<T>::reflect(const Vector2<T>& vec) const noexcept
	{
		return Vector2<T>{*this - (T)2 * project(vec) };
	}

	template<typename T>
	inline constexpr Vector2<T> Vector2<T>::reject(const Vector2<T>& vec) const noexcept
	{
		return Vector2<T>{*this - project(vec)};
	}


	template<typename T>
	inline constexpr Vector2<T> Vector2<T>::perpendicular() const noexcept
	{
		return Vector2<T>{-y, x};
	}

	template<typename T>
	inline constexpr Vector2<T> Vector2<T>::rotate(Angle angle) const noexcept
	{
		return Vector2<T>{ x * std::cos(angle.angle) + y * -std::sin(angle.angle), x * std::sin(angle.angle) + y * std::cos(angle.angle)};
	}

	template<typename T>
	inline constexpr T Vector2<T>::length() const noexcept
	{
		T lengthSquared{ x * x + y * y }; 

		if (lengthSquared == T{})
			return T{};
		return T{ std::sqrt(lengthSquared) };
	}

	template<typename T>
	inline constexpr T Vector2<T>::length_squared() const noexcept
	{
		return T{x * x + y * y};
	}

	template<typename T>
	inline constexpr Vector2<T> Vector2<T>::normal() const noexcept
	{
		T len{ length() }; 
		if (len == T{})
			return Vector2<T>{};
		return Vector2<T>{x / len, y / len};
	}


	// Data related
	template<typename T>
	inline constexpr const T* Vector2<T>::data_ptr() const noexcept
	{
		return data.data();
	}

	template<typename T>
	inline constexpr T& Vector2<T>::operator[](size_t index)
	{
		if (index >= data.size())
			throw std::out_of_range("index is out of range in vector2");
		return data[index];
	}

	template<typename T>
	inline constexpr const T& Vector2<T>::operator[](size_t index) const
	{
		if (index >= data.size())
			throw std::out_of_range("index is out of range in vector2");
		return data[index];
	}


	// Member overloads
	template<typename T>
	inline constexpr Vector2<T>& Vector2<T>::operator+=(const Vector2<T>& vec) noexcept
	{
		*this = *this + vec;
		return *this;
	}

	template<typename T>
	inline constexpr Vector2<T>& Vector2<T>::operator-=(const Vector2<T>& vec) noexcept
	{
		*this = *this - vec;
		return *this;
	}

	template<typename T>
	inline constexpr Vector2<T>& Vector2<T>::operator+=(const T& scalar) noexcept
	{
		*this = *this + scalar;
		return *this;
	}

	template<typename T>
	inline constexpr Vector2<T>& Vector2<T>::operator-=(const T& scalar) noexcept
	{
		*this = *this - scalar;
		return *this;
	}

	template<typename T>
	inline constexpr Vector2<T>& Vector2<T>::operator*=(const T& scalar) noexcept
	{
		*this = *this * scalar;
		return *this;
	}
 
	template<typename T>
	inline constexpr Vector2<T>& Vector2<T>::operator/=(const T& scalar) noexcept
	{
		*this = *this / scalar;
		return *this;
	}


	template<typename T>
	constexpr Vector2<T> Vector2<T>::operator-() const noexcept
	{
		return Vector2<T>{-x, -y};
	}

	template<typename T>
	constexpr bool Vector2<T>::operator!() const noexcept
	{
		return (x == 0 && y == 0);
	}

	template<typename T>
	inline constexpr bool Vector2<T>::operator==(const Vector2<T>& vec) const noexcept
	{
		return (x == vec.x && y == vec.y);
	}


	// Overloads
	template<typename T>
	inline constexpr Vector2<T> operator+(const Vector2<T>& a, const Vector2<T>& b) noexcept
	{
		return Vector2<T>{a.x + b.x, a.y + b.y};
	}

	template<typename T>
	inline constexpr Vector2<T> operator-(const Vector2<T>& a, const Vector2<T>& b) noexcept
	{
		return Vector2<T>{a.x - b.x, a.y - b.y};
	}


	template<typename T>
	inline constexpr Vector2<T> operator+(const Vector2<T>& a, const T& k) noexcept
	{
		return Vector2<T>{a.x + k, a.y + k };
	}

	template<typename T>
	inline constexpr Vector2<T> operator-(const Vector2<T>& a, const T& k) noexcept
	{
		return Vector2<T>{a.x - k, a.y - k };
	}

	template<typename T>
	inline constexpr Vector2<T> operator*(const Vector2<T>& a, const T& k) noexcept
	{
		return Vector2<T>{ a.x * k, a.y * k};
	}

	template<typename T>
	inline constexpr Vector2<T> operator/(const Vector2<T>& a, const T& k) noexcept
	{
		return Vector2<T>{a.x / k, a.y / k };
	}


	template<typename T>
	inline constexpr Vector2<T> operator+(const T& k, const Vector2<T>& a) noexcept
	{
		return Vector2<T>{a.x + k, a.y + k };
	}

	template<typename T>
	inline constexpr Vector2<T> operator-(const T& k, const Vector2<T>& a) noexcept
	{
		return Vector2<T>{k - a.x, k - a.y };
	}

	template<typename T>
	inline constexpr Vector2<T> operator*(const T& k, const Vector2<T>& a) noexcept
	{
		return Vector2<T>{ a.x * k, a.y * k};
	}

	template<typename T>
	inline constexpr Vector2<T> operator/(const T& k, const Vector2<T>& a) noexcept
	{
		return Vector2<T>{ k / a.x , k / a.y };
	}

	

} // mpml