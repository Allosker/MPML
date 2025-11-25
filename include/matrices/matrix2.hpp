#pragma once


#include <array>
#include <xutility>
#include <optional>

#include "vectors/vector2.hpp"

#include "utilities/data_types/data_orga.hpp"

namespace mpml
{


template<typename T, Option data_placement=Option::Row>
class Matrix2
{
public:

	// Initialization

	constexpr Matrix2(const std::array<Vector2<T>, 2>& vectors) noexcept;
	constexpr Matrix2(std::array<Vector2<T>, 2>&& vectors) noexcept;

	constexpr Matrix2(const std::array<T, 4>& elems) noexcept;
	constexpr Matrix2(std::array<T, 4>&& elems) noexcept;

	constexpr Matrix2(const T& a = {}, const T& b = {}, const T& c = {}, const T& d = {}) noexcept;


	~Matrix2() = default;


	// Operations

	[[nodiscard]] constexpr T det() const noexcept;
	// In case of an incorrect index, the first entry will be returned 
	[[nodiscard]] constexpr T minor(size_t index) const noexcept;

	[[nodiscard]] constexpr T cofactor(size_t index) const noexcept;
	[[nodiscard]] constexpr Matrix2<T, data_placement> cofactor_matrix() const noexcept;

	[[nodiscard]] constexpr Matrix2<T, data_placement> adj() const noexcept;

	[[nodiscard]] constexpr std::optional < Matrix2<T, data_placement>> inverse() const;
	[[nodiscard]] constexpr Matrix2<T, data_placement> transpose() const noexcept;


	// Data related

	[[nodiscard]] constexpr const T* data_ptr() const noexcept;

		// Overload [] and [][] (create proxy class row)

// Class Members

	union
	{
		T a, b;
		T c, d;

		std::array<T, 4> data;
	};

};



// Class definition



// Initialization
template<typename T, Option data_placement>
inline constexpr Matrix2<T, data_placement>::Matrix2(const std::array<Vector2<T>, 2>& vectors) noexcept
{
	if constexpr (data_placement == Option::Column)
		data = { vectors[0].x, vectors[1].x, 
				vectors[0].y, vectors[1].y };
	else
		data = { vectors[0].x, vectors[0].y, 
				vectors[1].x, vectors[1].y };
}

template<typename T, Option data_placement>
inline constexpr Matrix2<T, data_placement>::Matrix2(std::array<Vector2<T>, 2>&& vectors) noexcept
{
	if constexpr (data_placement == Option::Column)
		data = { std::move(vectors[0].x), std::move(vectors[1].x),
				std::move(vectors[0].y), std::move(vectors[1].y) };
	else
		data = { std::move(vectors[0].x), std::move(vectors[0].y),
				std::move(vectors[1].x), std::move(vectors[1].y) };
}

template<typename T, Option data_placement>
constexpr Matrix2<T, data_placement>::Matrix2(const std::array<T, 4>& elems) noexcept
	: data{elems}
{
	// TODO: row major etc
}

template<typename T, Option data_placement>
constexpr Matrix2<T, data_placement>::Matrix2(std::array<T, 4>&& elems) noexcept
	: data{ std::move(elems) }
{
}

template<typename T, Option data_placement>
inline constexpr Matrix2<T, data_placement>::Matrix2(const T& a, const T& b, const T& c, const T& d) noexcept
{
	if constexpr (data_placement == Option::Column)
		data = { a, c,
				b, d };
	else
		data = { a, b, 
				c, d };
}


// Operations
template<typename T, Option data_placement>
inline constexpr T Matrix2<T, data_placement>::det() const noexcept
{
	return T{ a * d - b * c };
}

template<typename T, Option data_placement>
inline constexpr T Matrix2<T, data_placement>::minor(size_t index) const noexcept
{
		if constexpr (index == 0)
			return data[3];
		else constexpr if (index == 1)
			return data[2];
		else constexpr if (index == 2)
			return data[1];
		else
			return data[0];
}

template<typename T, Option data_placement>
inline constexpr T Matrix2<T, data_placement>::cofactor(size_t index) const noexcept
{
	T c{ ((index % 2) ? -1 : 1) * minor(index) };
	return c;
}

template<typename T, Option data_placement>
inline constexpr Matrix2<T, data_placement> Matrix2<T, data_placement>::cofactor_matrix() const noexcept
{
	return Matrix2<T, data_placement>{cofactor(0), cofactor(1), cofactor(2), cofactor(3)};
}

template<typename T, Option data_placement>
inline constexpr Matrix2<T, data_placement> Matrix2<T, data_placement>::adj() const noexcept
{
	return Matrix2<T, data_placement>{ cofactor_matrix().transpose() };
}

template<typename T, Option data_placement>
inline constexpr std::optional<Matrix2<T, data_placement>> Matrix2<T, data_placement>::inverse() const
{
	T determinant{ det() };

	if (determinant == T{})
		return std::nullopt;

	return std::optional < Matrix2<T, data_placement>>{  adj() * 1 / determinant };
}

template<typename T, Option data_placement>
inline constexpr Matrix2<T, data_placement> Matrix2<T, data_placement>::transpose() const noexcept
{
	if constexpr(data_placement == Option::Column)
		return Matrix2<T, data_placement>{a, b, 
										  c, d};
	else
		return Matrix2<T, data_placement>{a, c, 
										  b, d};
}


// Data related
template<typename T, Option data_placement>
inline constexpr const T* Matrix2<T, data_placement>::data_ptr() const noexcept
{
	return &data[0];
}






// Overloads

template<typename T, Option data_placement>
inline constexpr Matrix2<T, data_placement> operator*(const Matrix2<T, data_placement>& mat, const T& k) noexcept
{
	Matrix2<T, data_placement> mat_r{ mat };

	mat_r.a *= k;
	mat_r.b *= k;
	mat_r.c *= k;
	mat_r.d *= k;

	return mat_r;
}


} // mpml