#pragma once
// MIT
// Allosker - 2025
// ===================================================
// Defines a 2D 3x3 matrix and all its function/math related operations.
// ===================================================


#include <array>
#include <utility>
#include <algorithm>
#include <optional>

#include "mpml/vectors/vector3.hpp"
#include "mpml/matrices/matrix2.hpp"


namespace mpml
{


	template<typename T>
	class Matrix3
	{
	public:

		// Initialization

		constexpr Matrix3(const Matrix3<T>& matrix) noexcept;
		constexpr Matrix3(Matrix3<T>&& matrix) noexcept;

		constexpr Matrix3<T>& operator=(const Matrix3<T>& matrix) noexcept;
		constexpr Matrix3<T>& operator=(Matrix3<T>&& matrix) noexcept;

		constexpr Matrix3(const Vector3<T>& vec1, const Vector3<T>& vec2, const Vector3<T>& vec3) noexcept;

		constexpr Matrix3(const std::array<T, 9>& elems) noexcept;
		constexpr Matrix3(std::array<T, 9>&& elems) noexcept;

		constexpr Matrix3(
			const T& a = {}, const T& b = {}, const T& c = {},
			const T& d = {}, const T& e = {}, const T& f = {},
			const T& g = {}, const T& h = {}, const T& i = {}
		) noexcept;


		~Matrix3() = default;


		// Operations

		[[nodiscard]] constexpr T det() const noexcept;
		[[nodiscard]] constexpr Matrix2<T> minor(const size_t& index) const;

		[[nodiscard]] constexpr T cofactor(const size_t& index) const noexcept;
		[[nodiscard]] constexpr Matrix3<T> cofactor_matrix() const noexcept;

		[[nodiscard]] constexpr Matrix3<T> adj() const noexcept;

		[[nodiscard]] constexpr std::optional<Matrix3<T>> inverse() const;
		[[nodiscard]] constexpr Matrix3<T> transpose() const noexcept;

		[[nodiscard]] constexpr Matrix3<T> pow(size_t pm = 2) const noexcept;


		// Data related

		[[nodiscard]] constexpr T* data_ptr() noexcept;
		[[nodiscard]] constexpr const T* data_ptr() const noexcept;
		

		[[nodiscard]] constexpr Vector3<T>& operator[](const size_t& index);
		[[nodiscard]] constexpr const Vector3<T>& operator[](const size_t& index) const;


		// Overloads

		constexpr Matrix3<T>& operator+=(const Matrix3<T>& mat) noexcept;
		constexpr Matrix3<T>& operator-=(const Matrix3<T>& mat) noexcept;

		constexpr Matrix3<T>& operator*=(const Matrix3<T>& mat) noexcept;
		constexpr Matrix3<T>& operator/=(const Matrix3<T>& mat);


		constexpr Matrix3<T>& operator*=(const T& k) noexcept;
		constexpr Matrix3<T>& operator/=(const T& k) noexcept;

		[[nodiscard]] constexpr Matrix3<T> operator-() const noexcept;


		// Class Members

		union
		{
			struct
			{
				T a, b, c;
				T d, e, f;
				T g, h, i;
			};

			struct
			{
				Vector3<T> col0;
				Vector3<T> col1;
				Vector3<T> col2;
			};

			std::array<T, 9> data{};
		};


	};
	// Common Types
	template<typename T>
	inline constexpr static Matrix3<T> Identity3
	{
		T{1}, T{}, T{},
		T{}, T{1}, T{},
		T{}, T{}, T{1}
	};

	template<typename T>
	inline constexpr Matrix3<T> AntiDiagonal_Identity3
	{
		T{}, T{}, T{1},
		T{}, T{1}, T{},
		T{1}, T{}, T{}
	};



	// Class definition


	// Initialization
	template<typename T>
	inline constexpr Matrix3<T>::Matrix3(const Matrix3<T>& matrix) noexcept
		: data{ matrix.data }
	{
	}

	template<typename T>
	inline constexpr Matrix3<T>::Matrix3(Matrix3<T>&& matrix) noexcept
		: data{ std::move(matrix.data) }
	{
	}

	template<typename T>
	inline constexpr Matrix3<T>& Matrix3<T>::operator=(const Matrix3<T>& matrix) noexcept
	{
		if (this == &matrix)
			return *this;

		data = matrix.data;

		return *this;
	}

	template<typename T>
	inline constexpr Matrix3<T>& Matrix3<T>::operator=(Matrix3<T>&& matrix) noexcept
	{
		if (this == &matrix)
			return *this;

		data = std::move(matrix.data);

		return *this;
	}


	template<typename T>
	inline constexpr Matrix3<T>::Matrix3(const Vector3<T>& vec1, const Vector3<T>& vec2, const Vector3<T>& vec3) noexcept
	{
		data = { vec1.x, vec1.y, vec1.z,
				 vec2.x, vec2.y, vec2.z,
				 vec3.x, vec3.y, vec3.z
		};
	}

	template<typename T>
	inline constexpr Matrix3<T>::Matrix3(const std::array<T, 9>& elems) noexcept
		: data{ elems }
	{
	}

	template<typename T>
	inline constexpr Matrix3<T>::Matrix3(std::array<T, 9>&& elems) noexcept
		: data{ std::move(elems) }
	{
	}

	template<typename T>
	inline constexpr Matrix3<T>::Matrix3(const T& a, const T& b, const T& c, const T& d, const T& e, const T& f, const T& g, const T& h, const T& i) noexcept
	{
		data = { a, b, c,
				 d, e, f,
				 g, h, i
		};
	}


	// Operations
	template<typename T>
	inline constexpr T Matrix3<T>::det() const noexcept
	{
		return T{ a * (e * i - f * h) - 
				  b * (d * i - f * g) + 
				  c * (d * h - e * g) 
		};
	}

	template<typename T>
	inline constexpr Matrix2<T> Matrix3<T>::minor(const size_t& index) const
	{
		switch (index)
		{
		case 0:
			return Matrix2<T>
			{
				e, f,
				h, i
			};
			break;

		case 1:
			return Matrix2<T>
			{
				d, f,
				g, i
			};
			break;

		case 2:
			return Matrix2<T>
			{
				d, e,
				g, h
			};
			break;

		case 3:
			return Matrix2<T>
			{
				b, c,
				h, i
			};
			break;


		case 4:
			return Matrix2<T>
			{
				a, c,
				g, i
			};
			break;

		case 5:
			return Matrix2<T>
			{
				a, b,
				g, h
			};
			break;

		case 6:
			return Matrix2<T>
			{
				b, c,
				e, f
			};
			break;

		case 7:
			return Matrix2<T>
			{
				a, c,
				d, f
			};
			break;

		case 8:
			return Matrix2<T>
			{
				a, b,
				d, e
			};
			break;

		default:
			throw std::length_error("ERROR::MATRIX2::FUNCTION_MINOR::INDEX::Index is out of range");
			break;
		}
	}

	template<typename T>
	inline constexpr T Matrix3<T>::cofactor(const size_t& index) const noexcept
	{
		T c{ (((index / 3 + index % 3) % 2) ? -1 : 1) * minor(index).det() };
		return c;
	}

	template<typename T>
	inline constexpr Matrix3<T> Matrix3<T>::cofactor_matrix() const noexcept
	{
		return Matrix3<T>{
			cofactor(0), cofactor(1), cofactor(2), 
			cofactor(3), cofactor(4), cofactor(5),
			cofactor(6), cofactor(7), cofactor(8)
		};
	}

	template<typename T>
	inline constexpr Matrix3<T> Matrix3<T>::adj() const noexcept
	{
		return Matrix3<T>{ cofactor_matrix().transpose() };
	}

	template<typename T>
	inline constexpr std::optional<Matrix3<T>> Matrix3<T>::inverse() const
	{
		T determinant{ det() };

		if (determinant == T{})
			return std::nullopt;

		return std::optional<Matrix3<T>>{ adj() / determinant };
	}

	template<typename T>
	inline constexpr Matrix3<T> Matrix3<T>::transpose() const noexcept
	{
		return Matrix3<T>{
			a, d, g,
			b, e, h,
			c, f, i
		};
	}

	template<typename T>
	inline constexpr Matrix3<T> Matrix3<T>::pow(size_t pm) const noexcept
	{
		if (pm == 0)
			return Identity3;

		Matrix3<T> mat{ *this };

		for (size_t i{}; i < pm - 1; i++)
		{
			mat *= *this;
		}

		return mat;
	}

	// Data related
	template<typename T>
	inline constexpr T* Matrix3<T>::data_ptr() noexcept
	{
		return data.data();
	}

	template<typename T>
	inline constexpr const T* Matrix3<T>::data_ptr() const noexcept
	{
		return data.data();
	}

	template<typename T>
	inline constexpr Vector3<T>& Matrix3<T>::operator[](const size_t& index)
	{
		switch (index)
		{
		case 0:
			return col0;
			break;

		case 1:
			return col1;
			break;

		case 2:
			return col2;
			break;

		default:
			std::out_of_range("Index out of range");
			break;
		}
	}

	template<typename T>
	inline constexpr const Vector3<T>& Matrix3<T>::operator[](const size_t& index) const
	{
		switch (index)
		{
		case 0:
			return col0;
			break;

		case 1:
			return col1;
			break;

		case 2:
			return col2;
			break;

		default:
			std::out_of_range("Index out of range");
			break;
		}
	}


	// Member Overloads
	template<typename T>
	inline constexpr Matrix3<T>& Matrix3<T>::operator+=(const Matrix3<T>& mat) noexcept
	{
		*this = *this + mat;
		return *this;
	}

	template<typename T>
	inline constexpr Matrix3<T>& Matrix3<T>::operator-=(const Matrix3<T>& mat) noexcept
	{
		*this = *this - mat;
		return *this;
	}

	template<typename T>
	inline constexpr Matrix3<T>& Matrix3<T>::operator*=(const Matrix3<T>& mat) noexcept
	{
		*this = *this * mat;

		return *this;
	}

	template<typename T>
	inline constexpr Matrix3<T>& Matrix3<T>::operator/=(const Matrix3<T>& mat)
	{
		std::optional<Matrix3<T>> temp{ *this / mat };

		if (!temp)
			throw std::runtime_error("ERROR::MATRIX::OPERATOR/::Division by zero");
		else
			*this = std::move(*temp);

		return *this;
	}

	template<typename T>
	inline constexpr Matrix3<T>& Matrix3<T>::operator*=(const T& k) noexcept
	{
		a *= k;
		b *= k;
		c *= k;
		d *= k;
		e *= k;
		f *= k;
		g *= k;
		h *= k;
		i *= k;

		return *this;
	}

	template<typename T>
	inline constexpr Matrix3<T>& Matrix3<T>::operator/=(const T& k) noexcept
	{
		a /= k;
		b /= k;
		c /= k;
		d /= k;
		e /= k;
		f /= k;
		g /= k;
		h /= k;
		i /= k;

		return *this;
	}

	template<typename T>
	inline constexpr Matrix3<T> Matrix3<T>::operator-() const noexcept
	{
		return Matrix3<T>{ -a, -b, -c, -d, -e, -f, -g, -h, -i };
	}


	// Overloads
	template<typename T>
	inline constexpr Matrix3<T> operator*(const Matrix3<T>& mat, const T& k) noexcept
	{
		Matrix3<T> mat_r{ mat };

		mat_r.a *= k;
		mat_r.b *= k;
		mat_r.c *= k;
		mat_r.d *= k;
		mat_r.e *= k;
		mat_r.f *= k;
		mat_r.g *= k;
		mat_r.h *= k;
		mat_r.i *= k;

		return mat_r;
	}

	template<typename T>
	inline constexpr Matrix3<T> operator/(const Matrix3<T>& mat, const T& k) noexcept
	{
		Matrix3<T> mat_r{ mat };

		mat_r.a /= k;
		mat_r.b /= k;
		mat_r.c /= k;
		mat_r.d /= k;
		mat_r.e /= k;
		mat_r.f /= k;
		mat_r.g /= k;
		mat_r.h /= k;
		mat_r.i /= k;

		return mat_r;
	}


	template<typename T>
	inline constexpr Matrix3<T> operator+(const Matrix3<T>& mat1, const Matrix3<T>& mat2) noexcept
	{
		Matrix3<T> mat_r;

		mat_r.a = mat1.a + mat2.a;
		mat_r.b = mat1.b + mat2.b;
		mat_r.c = mat1.c + mat2.c;
		mat_r.d = mat1.d + mat2.d;
		mat_r.e = mat1.e + mat2.e;
		mat_r.f = mat1.f + mat2.f;
		mat_r.g = mat1.g + mat2.g;
		mat_r.h = mat1.h + mat2.h;
		mat_r.i = mat1.i + mat2.i;

		return mat_r;
	}

	template<typename T>
	inline constexpr Matrix3<T> operator-(const Matrix3<T>& mat1, const Matrix3<T>& mat2) noexcept
	{
		Matrix3<T> mat_r;

		mat_r.a = mat1.a - mat2.a;
		mat_r.b = mat1.b - mat2.b;
		mat_r.c = mat1.c - mat2.c;
		mat_r.d = mat1.d - mat2.d;
		mat_r.e = mat1.e - mat2.e;
		mat_r.f = mat1.f - mat2.f;
		mat_r.g = mat1.g - mat2.g;
		mat_r.h = mat1.h - mat2.h;
		mat_r.i = mat1.i - mat2.i;

		return mat_r;
	}

	template<typename T>
	inline constexpr Matrix3<T> operator*(const Matrix3<T>& mat1, const Matrix3<T>& mat2) noexcept
	{
		Matrix3<T> mat_r;

		mat_r.a = mat1.a * mat2.a + mat1.b * mat2.d + mat1.c * mat2.g;
		mat_r.b = mat1.a * mat2.b + mat1.b * mat2.e + mat1.c * mat2.h;
		mat_r.c = mat1.a * mat2.c + mat1.b * mat2.f + mat1.c * mat2.i;

		mat_r.d = mat1.d * mat2.a + mat1.e * mat2.d + mat1.f * mat2.g;
		mat_r.e = mat1.d * mat2.b + mat1.e * mat2.e + mat1.f * mat2.h;
		mat_r.f = mat1.d * mat2.c + mat1.e * mat2.f + mat1.f * mat2.i;

		mat_r.g = mat1.g * mat2.a + mat1.h * mat2.d + mat1.i * mat2.g;
		mat_r.h	= mat1.g * mat2.b + mat1.h * mat2.e + mat1.i * mat2.h;
		mat_r.i	= mat1.g * mat2.c + mat1.h * mat2.f + mat1.i * mat2.i;
			
		return mat_r;
	}

	template<typename T>
	inline constexpr std::optional<Matrix3<T>> operator/(const Matrix3<T>& mat1, const Matrix3<T>& mat2) noexcept
	{
		Matrix3<T> mat_r;

		std::optional<Matrix3<T>> inver{ mat2.inverse() };

		if (inver)
		{
			mat_r = mat1 * (*inver);
			return std::optional<Matrix3<T>>{ std::move(mat_r) };
		}

		return std::nullopt;
	}

	template<typename T>
	inline constexpr Vector3<T> operator*(const Matrix3<T>& mat, const Vector3<T>& vec) noexcept
	{
		return Vector3<T>
		{
			mat.a * vec.x + mat.b * vec.y + mat.c * vec.z,
			mat.e * vec.x + mat.f * vec.y + mat.g * vec.z,
			mat.h * vec.x + mat.i * vec.y + mat.j * vec.z
		};
	}



} // mpml