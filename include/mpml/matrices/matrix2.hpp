#pragma once
// MIT
// Allosker - 2025
// ===================================================
// Defines a 2D 2x2 matrix and all its function/math related operations.
// ===================================================


#include <array>
#include <xutility>
#include <optional>
#include <stdexcept>

#include "mpml/vectors/vector2.hpp"


namespace mpml
{


template<typename T>
class Matrix2
{
public:

	// Initialization

	constexpr Matrix2(const Matrix2<T>& matrix) noexcept;
	constexpr Matrix2(Matrix2<T>&& matrix) noexcept;

	constexpr Matrix2<T>& operator=(const Matrix2<T>& matrix) noexcept;
	constexpr Matrix2<T>& operator=(Matrix2<T>&& matrix) noexcept;

	constexpr Matrix2(const Vector2<T>& vec1, const Vector2<T>& vec2) noexcept;

	constexpr Matrix2(const std::array<T, 4>& elems) noexcept;
	constexpr Matrix2(std::array<T, 4>&& elems) noexcept;

	constexpr Matrix2(const T& a = {}, const T& b = {}, const T& c = {}, const T& d = {}) noexcept;


	~Matrix2() = default;


	// Operations

	[[nodiscard]] constexpr T det() const noexcept;
	[[nodiscard]] constexpr T minor(size_t index) const;

	[[nodiscard]] constexpr T cofactor(const size_t& index) const noexcept;
	[[nodiscard]] constexpr Matrix2<T> cofactor_matrix() const noexcept;

	[[nodiscard]] constexpr Matrix2<T> adj() const noexcept;

	[[nodiscard]] constexpr std::optional < Matrix2<T>> inverse() const;
	[[nodiscard]] constexpr Matrix2<T> transpose() const noexcept;

	[[nodiscard]] constexpr Matrix2<T> pow(size_t pm = 2) const noexcept;


	// Data related

	[[nodiscard]] constexpr const T* data_ptr() const noexcept;

	[[nodiscard]] constexpr Vector2<T>& operator[](const size_t& index);
	[[nodiscard]] constexpr const Vector2<T>& operator[](const size_t& index) const;


	// Overloads

	constexpr Matrix2<T>& operator+=(const Matrix2<T>& mat) noexcept;
	constexpr Matrix2<T>& operator-=(const Matrix2<T>& mat) noexcept;

	constexpr Matrix2<T>& operator*=(const Matrix2<T>& mat) noexcept;
	constexpr Matrix2<T>& operator/=(const Matrix2<T>& mat);


	constexpr Matrix2<T>& operator*=(const T& k) noexcept;
	constexpr Matrix2<T>& operator/=(const T& k) noexcept;

	[[nodiscard]] constexpr Matrix2<T> operator-() const noexcept;


// Class Members

	union
	{
		struct 
		{ 
			T a, b;
			T c, d;
		};

		struct
		{
			Vector2<T> col0;
			Vector2<T> col1;
		};
		
		std::array<T, 4> data{};
	};


};
// Common Types
template<typename T>
inline constexpr Matrix2<T> Identity2
{
	T{1}, T{},
	T{}, T{1}
};

template<typename T>
inline constexpr Matrix2<T> AntiDiagonal_Identity2
{
	T{}, T{1},
	T{1}, T{}
};



// Class definition


// Initialization
template<typename T>
inline constexpr Matrix2<T>::Matrix2(const Matrix2<T>& matrix) noexcept
	: data{ matrix.data }
{
}

template<typename T>
inline constexpr Matrix2<T>::Matrix2(Matrix2<T>&& matrix) noexcept
	: data{ std::move(matrix.data) }
{
}

template<typename T>
inline constexpr Matrix2<T>& Matrix2<T>::operator=(const Matrix2<T>& matrix) noexcept
{
	if (this == &matrix)
		return *this;
	
	data = matrix.data;

	return *this;
}

template<typename T>
inline constexpr Matrix2<T>& Matrix2<T>::operator=(Matrix2<T>&& matrix) noexcept
{
	if (this == &matrix)
		return *this;

	data = std::move(matrix.data);

	return *this;
}


template<typename T>
inline constexpr Matrix2<T>::Matrix2(const Vector2<T>& vec1, const Vector2<T>& vec2) noexcept
{
	data = { vec1.x, vec1.y,
			vec2.x, vec2.y };
}

template<typename T>
constexpr Matrix2<T>::Matrix2(const std::array<T, 4>& elems) noexcept
	: data{elems}
{
}

template<typename T>
constexpr Matrix2<T>::Matrix2(std::array<T, 4>&& elems) noexcept
	: data{ std::move(elems) }
{
}

template<typename T>
inline constexpr Matrix2<T>::Matrix2(const T& a, const T& b, const T& c, const T& d) noexcept
{
	data = { a, b, 
			c, d };
}


// Operations
template<typename T>
inline constexpr T Matrix2<T>::det() const noexcept
{
	return T{ a * d - b * c };
}

template<typename T>
inline constexpr T Matrix2<T>::minor(size_t index) const
{
	if (index == 0)
		return data[3];
	else if (index == 1)
		return data[2];
	else if (index == 2)
		return data[1];
	else if (index == 3)
		return data[0];
	else
		throw std::length_error("ERROR:MATRIX2::FUNCTION_MINOR::INDEX::Index is out of range");
}

template<typename T>
inline constexpr T Matrix2<T>::cofactor(const size_t& index) const noexcept
{
	T c{ (((index / 2 + index % 2) % 2) ? -1 : 1) * minor(index)};
	return c;
}

template<typename T>
inline constexpr Matrix2<T> Matrix2<T>::cofactor_matrix() const noexcept
{
	return Matrix2<T>{cofactor(0), cofactor(1), cofactor(2), cofactor(3)};
}

template<typename T>
inline constexpr Matrix2<T> Matrix2<T>::adj() const noexcept
{
	return Matrix2<T>{ cofactor_matrix().transpose() };
}

template<typename T>
inline constexpr std::optional<Matrix2<T>> Matrix2<T>::inverse() const
{
	T determinant{ det() };

	if (determinant == T{})
		return std::nullopt;

	return std::optional<Matrix2<T>>{ adj() / determinant };
}

template<typename T>
inline constexpr Matrix2<T> Matrix2<T>::transpose() const noexcept
{
	return Matrix2<T>{a, c,
					  b, d};
}

template<typename T>
inline constexpr Matrix2<T> Matrix2<T>::pow(size_t pm) const noexcept
{
	if (pm == 0)
		return Identity2;

	Matrix2<T> mat{ *this };

	for (size_t i{}; i < pm-1; i++)
	{
		mat *= *this;
	}

	return mat;
}


// Data related
template<typename T>
inline constexpr const T* Matrix2<T>::data_ptr() const noexcept
{
	return data.data();
}

template<typename T>
inline constexpr Vector2<T>& Matrix2<T>::operator[](const size_t& index)
{
	switch (index)
	{
	case 0:
		return col0;
		break;

	case 1:
		return col1;
		break;

	default:
		std::out_of_range("Index out of range");
		break;
	}
}

template<typename T>
inline constexpr const Vector2<T>& Matrix2<T>::operator[](const size_t& index) const
{
	switch (index)
	{
	case 0:
		return col0;
		break;

	case 1:
		return col1;
		break;

	default:
		std::out_of_range("Index out of range");
		break;
	}
}


// Member Overloads
template<typename T>
inline constexpr Matrix2<T>& Matrix2<T>::operator+=(const Matrix2<T>& mat) noexcept
{
	*this = *this + mat;
	return *this;
}

template<typename T>
inline constexpr Matrix2<T>& Matrix2<T>::operator-=(const Matrix2<T>& mat) noexcept
{
	*this = *this - mat;
	return *this;
}

template<typename T>
inline constexpr Matrix2<T>& Matrix2<T>::operator*=(const Matrix2<T>& mat) noexcept
{
	*this = *this * mat;

	return *this;
}

template<typename T>
inline constexpr Matrix2<T>& Matrix2<T>::operator/=(const Matrix2<T>& mat)
{
	std::optional<Matrix2<T>> temp{ *this / mat };

	if (!temp)
		throw std::runtime_error("ERROR::MATRIX::OPERATOR/::Division by zero");
	else
		*this = std::move(*temp);
	
	return *this;
}

template<typename T>
inline constexpr Matrix2<T>& Matrix2<T>::operator*=(const T& k) noexcept
{
	a *= k;
	b *= k;
	c *= k;
	d *= k;

	return *this;
}

template<typename T>
inline constexpr Matrix2<T>& Matrix2<T>::operator/=(const T& k) noexcept
{
	a /= k;
	b /= k;
	c /= k;
	d /= k;

	return *this;
}

template<typename T>
inline constexpr Matrix2<T> Matrix2<T>::operator-() const noexcept
{
	return Matrix2<T>{ -a, -b, -c, -d };
}


// Overloads
template<typename T>
inline constexpr Matrix2<T> operator*(const Matrix2<T>& mat, const T& k) noexcept
{
	Matrix2<T> mat_r{ mat };

	mat_r.a *= k;
	mat_r.b *= k;
	mat_r.c *= k;
	mat_r.d *= k;

	return mat_r;
}

template<typename T>
inline constexpr Matrix2<T> operator/(const Matrix2<T>& mat, const T& k) noexcept
{
	Matrix2<T> mat_r{ mat };

	mat_r.a /= k;
	mat_r.b /= k;
	mat_r.c /= k;
	mat_r.d /= k;

	return mat_r;
}


template<typename T>
inline constexpr Matrix2<T> operator+(const Matrix2<T>& mat1, const Matrix2<T>& mat2) noexcept
{
	Matrix2<T> mat_r;

	mat_r.a = mat1.a + mat2.a;
	mat_r.b = mat1.b + mat2.b;
	mat_r.c = mat1.c + mat2.c;
	mat_r.d = mat1.d + mat2.d;

	return mat_r;
}

template<typename T>
inline constexpr Matrix2<T> operator-(const Matrix2<T>& mat1, const Matrix2<T>& mat2) noexcept
{
	Matrix2<T> mat_r;

	mat_r.a = mat1.a - mat2.a;
	mat_r.b = mat1.b - mat2.b;
	mat_r.c = mat1.c - mat2.c;
	mat_r.d = mat1.d - mat2.d;

	return mat_r;
}

template<typename T>
inline constexpr Matrix2<T> operator*(const Matrix2<T>& mat1, const Matrix2<T>& mat2) noexcept
{
	Matrix2<T> mat_r;

	mat_r.a = mat1.a * mat2.a + mat1.b * mat2.c;
	mat_r.b = mat1.a * mat2.b + mat1.b * mat2.d;
	mat_r.c = mat1.c * mat2.a + mat1.d * mat2.c;
	mat_r.d = mat1.c * mat2.b + mat1.d * mat2.d;

	return mat_r;
}

template<typename T>
inline constexpr std::optional<Matrix2<T>> operator/(const Matrix2<T>& mat1, const Matrix2<T>& mat2) noexcept
{
	Matrix2<T> mat_r;

	std::optional<Matrix2<T>> inver{ mat2.inverse() };

	if (inver)
	{
		mat_r = mat1 * (*inver);
		return std::optional<Matrix2<T>>{ std::move(mat_r) };
	}
	
	return std::nullopt;
}


template<typename T>
inline constexpr Vector2<T> operator*(const Matrix2<T>& mat, const Vector2<T>& vec) noexcept
{
	return Vector2<T>{ vec.x * mat.a + vec.y * mat.c, vec.x * mat.b + vec.y * mat.d };
}



} // mpml