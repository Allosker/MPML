#pragma once
// MIT
// Allosker - 2025
// ===================================================
// Defines a 2D 4x4 matrix and all its function/math related operations.
// ===================================================


#include <array>
#include <utility>
#include <algorithm>
#include <optional>

#include "vectors/vector3.hpp"
#include "vectors/vector4.hpp"
#include "matrices/matrix3.hpp"


namespace mpml
{


	template<typename T>
	class Matrix4
	{
	public:

		// Initialization

		constexpr Matrix4(const Matrix4&) noexcept = default;
		constexpr Matrix4& operator=(const Matrix4&) noexcept = default;

		constexpr Matrix4(Matrix4&&) noexcept = default;
		constexpr Matrix4& operator=(Matrix4&&) noexcept = default;


		constexpr Matrix4(const Matrix3<T>& matrix) noexcept;

		constexpr Matrix4(const Vector4<T>& vec1, const Vector4<T>& vec2, const Vector4<T>& vec3, const Vector4<T>& vec4) noexcept;

		constexpr Matrix4(
			const T& a = {}, const T& b = {}, const T& c = {}, const T& d = {}, 
			const T& e = {}, const T& f = {}, const T& g = {}, const T& h = {},
			const T& i = {}, const T& j = {}, const T& k = {}, const T& l = {},
			const T& m = {}, const T& n = {}, const T& o = {}, const T& p = {}
		) noexcept;

		template<typename U>
		constexpr Matrix4(const Matrix4<U>& mat) noexcept;

		~Matrix4() = default;

		
		// Special Operations



		// Operations

		[[nodiscard]] constexpr T det() const noexcept;
		// In case of an incorrect index, the first entry will be returned 
		[[nodiscard]] constexpr Matrix3<T> minor(const size_t& index) const;

		[[nodiscard]] constexpr T cofactor(const size_t& index) const noexcept;
		[[nodiscard]] constexpr Matrix4 cofactor_matrix() const noexcept;

		[[nodiscard]] constexpr Matrix4 adj() const noexcept;

		[[nodiscard]] constexpr std::optional<Matrix4<T>> inverse() const;
		[[nodiscard]] constexpr Matrix4 transpose() const noexcept;

		[[nodiscard]] constexpr Matrix4 pow(size_t pm = 2) const noexcept;


		// Data related

		[[nodiscard]] constexpr T* data_ptr() noexcept;
		[[nodiscard]] constexpr const T* data_ptr() const noexcept;

		[[nodiscard]] constexpr Vector4<T>& operator[](const size_t& index);
		[[nodiscard]] constexpr const Vector4<T>& operator[](const size_t& index) const;


		// Overloads

		constexpr Matrix4& operator+=(const Matrix4& mat) noexcept;
		constexpr Matrix4& operator-=(const Matrix4& mat) noexcept;

		constexpr Matrix4& operator*=(const Matrix4& mat) noexcept;
		constexpr Matrix4& operator/=(const Matrix4& mat);


		constexpr Matrix4& operator*=(const T& k) noexcept;
		constexpr Matrix4& operator/=(const T& k);

		[[nodiscard]] constexpr Matrix4 operator-() const noexcept;


		// Class Members

		union
		{
			struct
			{
				T a, b, c, d;
				T e, f, g, h;
				T i, j, k, l;
				T m, n, o, p;
			};

			std::array<T, 16> data{};
		};


	// Common Types

		static const Matrix4 Identity;

		static const Matrix4 AntiDiagonalIdentity;

	};


	// Common Types Def

	template<typename T>
	inline constexpr Matrix4<T> Matrix4<T>::Identity 
	{
		T{1}, T{}, T{}, T{},
		T{}, T{1}, T{}, T{},
		T{}, T{}, T{1}, T{},
		T{}, T{}, T{}, T{1}
	};

	template<typename T>
	inline constexpr Matrix4<T> Matrix4<T>::AntiDiagonalIdentity
	{
		T{}, T{}, T{}, T{1},
		T{}, T{}, T{1}, T{},
		T{}, T{1}, T{}, T{},
		T{1}, T{}, T{}, T{}
	};
	

	// Class definition


	// Initialization
	template<typename T>
	inline constexpr Matrix4<T>::Matrix4(const Matrix3<T>& matrix) noexcept
	{
		data[0x0] = matrix[0][0];
		data[0x1] = matrix[0][1];
		data[0x2] = matrix[0][2];
		data[0x3] = T{};

		data[0x4] = matrix[1][0];
		data[0x5] = matrix[1][1];
		data[0x6] = matrix[1][2];
		data[0x7] = T{};

		data[0x8] = matrix[2][0];
		data[0x9] = matrix[2][1];
		data[0xA] = matrix[2][2];
		data[0xB] = T{};

		data[0xC] = T{};
		data[0xD] = T{};
		data[0xE] = T{};
		data[0xF] = static_cast<T>(1);
	}

	template<typename T>
	inline constexpr Matrix4<T>::Matrix4(const Vector4<T>& vec1, const Vector4<T>& vec2, const Vector4<T>& vec3, const Vector4<T>& vec4) noexcept
	{
		data[0x0] = vec1[0];
		data[0x1] = vec1[1];
		data[0x2] = vec1[2];
		data[0x3] = vec1[3];

		data[0x4] = vec2[0];
		data[0x5] = vec2[1];
		data[0x6] = vec2[2];
		data[0x7] = vec2[3];

		data[0x8] = vec3[0];
		data[0x9] = vec3[1];
		data[0xA] = vec3[2];
		data[0xB] = vec3[3];

		data[0xC] = vec4[0];
		data[0xD] = vec4[1];
		data[0xE] = vec4[2];
		data[0xF] = vec4[3];
	}

	template<typename T>
	inline constexpr Matrix4<T>::Matrix4(
		const T& a, const T& b, const T& c, const T& d, 
		const T& e, const T& f, const T& g, const T& h, 
		const T& i, const T& j, const T& k, const T& l,
		const T& m, const T& n, const T& o, const T& p
	) noexcept
	{
		data[0x0] = a;
		data[0x1] = b;
		data[0x2] = c;
		data[0x3] = d;

		data[0x4] = e;
		data[0x5] = f;
		data[0x6] = g;
		data[0x7] = h;

		data[0x8] = i;
		data[0x9] = j;
		data[0xA] = k;
		data[0xB] = l;

		data[0xC] = m;
		data[0xD] = n;
		data[0xE] = o;
		data[0xF] = p;
	}

	template<typename T>
	template<typename U>
	inline constexpr Matrix4<T>::Matrix4(const Matrix4<U>& mat) noexcept
	{
		std::transform(mat.data.begin(), mat.data.end(), data.begin(), [](const T& x) { return static_cast<T>(x); });
	}


	// Operations
	template<typename T>
	inline constexpr T Matrix4<T>::det() const noexcept
	{
		return T{ a * minor(0).det() 
			    - b * minor(1).det()
				+ c * minor(2).det()
			    - d * minor(3).det()
		};
	}

	template<typename T>
	inline constexpr Matrix3<T> Matrix4<T>::minor(const size_t& index) const
	{
		switch (index)
		{
		case 0:
			return Matrix3<T>
			{
				f, g, h,
				j, k, l,
				n, o, p
			};
			break;

		case 1:
			return Matrix3<T>
			{
				e, g, h,
				i, k, l,
				m, o, p
			};
			break;

		case 2:
			return Matrix3<T>
			{
				e, f, h,
				i, j, l,
				m, n, p
			};
			break;

		case 3:
			return Matrix3<T>
			{
				e, f, g,
				i, j, k,
				m, n, o
			};
			break;

		case 4:
			return Matrix3<T>
			{
				b, c, d,
				j, k, l,
				n, o, p
			};
			break;

		case 5:
			return Matrix3<T>
			{
				a, c, d,
				i, k, l,
				m, o, p
			};
			break;

		case 6:
			return Matrix3<T>
			{
				a, b, d,
				i, j, l,
				m, n, p
			};
			break;

		case 7:
			return Matrix3<T>
			{
				a, b, c,
				i, j, k,
				m, n, o,
			};
			break;

		case 8:
			return Matrix3<T>
			{
				b, c, d,
				f, g, h,
				n, o, p
			};
			break;

		case 9:
			return Matrix3<T>
			{
				a, c, d,
				e, g, h,
				m, o, p
			};
			break;

		case 10:
			return Matrix3<T>
			{
				a, b, d,
				e, f, h,
				m, n, p
			};
			break;

		case 11:
			return Matrix3<T>
			{
				a, b, c,
				e, f, g,
				m, n, o,
			};
			break;

		case 12:
			return Matrix3<T>
			{
				b, c, d,
				f, g, h,
				j, k, l,
			};
			break;

		case 13:
			return Matrix3<T>
			{
				a, c, d,
				e, g, h,
				i, k, l,
			};
			break;

		case 14:
			return Matrix3<T>
			{
				a, b, d,
				e, f, h,
				i, j, l,
			};
			break;

		case 15:
			return Matrix3<T>
			{
				a, b, c,
				e, f, g,
				i, j, k,
			};
			break;

		default:
			throw std::out_of_range("ERROR::Matrix3::FUNCTION_MINOR::INDEX::Index is out of range");
			break;
		}
	}

	template<typename T>
	inline constexpr T Matrix4<T>::cofactor(const size_t& index) const noexcept
	{
		T c{ (((index / 4 + index % 4) % 2) ? -1 : 1) * minor(index).det() };
		return c;
	}

	template<typename T>
	inline constexpr Matrix4<T> Matrix4<T>::cofactor_matrix() const noexcept
	{
		return Matrix4<T>{
			cofactor(0), cofactor(1), cofactor(2), cofactor(3), 
			cofactor(4), cofactor(5), cofactor(6), cofactor(7), 
			cofactor(8), cofactor(9), cofactor(10), cofactor(11),
			cofactor(12), cofactor(13), cofactor(14), cofactor(15)
		};
	}

	template<typename T>
	inline constexpr Matrix4<T> Matrix4<T>::adj() const noexcept
	{
		return Matrix4<T>{ cofactor_matrix().transpose() };
	}

	template<typename T>
	inline constexpr std::optional<Matrix4<T>> Matrix4<T>::inverse() const
	{
		T determinant{ det() };

		if (determinant == T{})
			return std::nullopt;

		return std::optional<Matrix4<T>>{ adj() / determinant };
	}

	template<typename T>
	inline constexpr Matrix4<T> Matrix4<T>::transpose() const noexcept
	{
		return Matrix4<T>{
				 a, e, i, m, 
				 b, f, j, n,
				 c, g, k, o,
				 d, h, l, p
		};
	}

	template<typename T>
	inline constexpr Matrix4<T> Matrix4<T>::pow(size_t pm) const noexcept
	{
		if (pm == 0)
			return Matrix4<T>::Identity;

		Matrix4<T> mat{ *this };

		for (size_t i{}; i < pm - 1; i++)
		{
			mat *= *this;
		}

		return mat;
	}


	// Data Related
	template<typename T>
	inline constexpr T* Matrix4<T>::data_ptr() noexcept
	{
		return data.data();
	}

	template<typename T>
	inline constexpr const T* Matrix4<T>::data_ptr() const noexcept
	{
		return data.data();
	}

	template<typename T>
	inline constexpr Vector4<T>& Matrix4<T>::operator[](const size_t& index)
	{
		switch (index)
		{
		case 0:
			return Vector4<T>{ data[0], data[1], data[2], data[3] };
			break;

		case 1:
			return Vector4<T>{ data[4], data[5], data[6], data[7] };
			break;

		case 2:
			return Vector4<T>{ data[8], data[9], data[10], data[11] };
			break;

		case 3:
			return Vector4<T>{ data[12], data[13], data[14], data[15] };
			break;

		default:
			std::out_of_range("Index out of range");
			break;
		}
	}

	template<typename T>
	inline constexpr const Vector4<T>& Matrix4<T>::operator[](const size_t& index) const
	{
		switch (index)
		{
		case 0:
			return Vector4<T>{ data[0], data[1], data[2], data[3] };
			break;

		case 1:
			return Vector4<T>{ data[4], data[5], data[6], data[7] };
			break;

		case 2:
			return Vector4<T>{ data[8], data[9], data[10], data[11] };
			break;

		case 3:
			return Vector4<T>{ data[12], data[13], data[14], data[15] };
			break;

		default:
			std::out_of_range("Index out of range");
			break;
		}
	}


	// Member Overloads
	template<typename T>
	inline constexpr Matrix4<T>& Matrix4<T>::operator+=(const Matrix4<T>& mat) noexcept
	{
		*this = *this + mat;
		return *this;
	}

	template<typename T>
	inline constexpr Matrix4<T>& Matrix4<T>::operator-=(const Matrix4<T>& mat) noexcept
	{
		*this = *this - mat;
		return *this;
	}

	template<typename T>
	inline constexpr Matrix4<T>& Matrix4<T>::operator*=(const Matrix4<T>& mat) noexcept
	{
		*this = *this * mat;

		return *this;
	}

	template<typename T>
	inline constexpr Matrix4<T>& Matrix4<T>::operator/=(const Matrix4<T>& mat)
	{
		std::optional<Matrix4<T>> temp{ *this / mat };

		if (!temp)
			throw std::runtime_error("ERROR::MATRIX::OPERATOR/::Division by zero");
		else
			*this = std::move(*temp);

		return *this;
	}

	template<typename T>
	inline constexpr Matrix4<T>& Matrix4<T>::operator*=(const T& k) noexcept
	{
		*this = *this * k;

		return *this;
	}

	template<typename T>
	inline constexpr Matrix4<T>& Matrix4<T>::operator/=(const T& k)
	{
		*this = *this / k;

		return *this;
	}

	template<typename T>
	inline constexpr Matrix4<T> Matrix4<T>::operator-() const noexcept
	{
		return Matrix4<T>{ -a, -b, -c, -d, -e, -f, -g, -h, -i, -j, -k, -l, -m, -n, -o, -p };
	}


	// Overloads
	template<typename T>
	inline constexpr Matrix4<T> operator*(const Matrix4<T>& mat, const T& x) noexcept
	{
		return Matrix4<T>
		{
			mat.a * x,
			mat.b * x,
			mat.c * x,
			mat.d * x,
			mat.e * x,
			mat.f * x,
			mat.g * x,
			mat.h * x,
			mat.i * x,
			mat.j * x,
			mat.k * x,
			mat.l * x,
			mat.m * x,
			mat.n * x,
			mat.o * x,
			mat.p * x
		};
	}

	template<typename T>
	inline constexpr Matrix4<T> operator/(const Matrix4<T>& mat, const T& x) noexcept
	{
		return Matrix4<T>
		{
			mat.a / x,
			mat.b / x,
			mat.c / x,
			mat.d / x,
			mat.e / x,
			mat.f / x,
			mat.g / x,
			mat.h / x,
			mat.i / x,
			mat.j / x,
			mat.k / x,
			mat.l / x,
			mat.m / x,
			mat.n / x,
			mat.o / x,
			mat.p / x
		};
	}


	template<typename T>
	inline constexpr Matrix4<T> operator+(const Matrix4<T>& mat1, const Matrix4<T>& mat2) noexcept
	{
		return Matrix4<T>
		{
			mat1.a + mat2.a,
			mat1.b + mat2.b,
			mat1.c + mat2.c,
			mat1.d + mat2.d,
			mat1.e + mat2.e,
			mat1.f + mat2.f,
			mat1.g + mat2.g,
			mat1.h + mat2.h,
			mat1.i + mat2.i,
			mat1.j + mat2.j,
			mat1.k + mat2.k,
			mat1.l + mat2.l,
			mat1.m + mat2.m,
			mat1.n + mat2.n,
			mat1.o + mat2.o,
			mat1.p + mat2.p
		};
	}

	template<typename T>
	inline constexpr Matrix4<T> operator-(const Matrix4<T>& mat1, const Matrix4<T>& mat2) noexcept
	{
		return Matrix4<T>
		{
			mat1.a - mat2.a,
			mat1.b - mat2.b,
			mat1.c - mat2.c,
			mat1.d - mat2.d,
			mat1.e - mat2.e,
			mat1.f - mat2.f,
			mat1.g - mat2.g,
			mat1.h - mat2.h,
			mat1.i - mat2.i,
			mat1.j - mat2.j,
			mat1.k - mat2.k,
			mat1.l - mat2.l,
			mat1.m - mat2.m,
			mat1.n - mat2.n,
			mat1.o - mat2.o,
			mat1.p - mat2.p
		};
	}

	template<typename T>
	inline constexpr Matrix4<T> operator*(const Matrix4<T>& mat1, const Matrix4<T>& mat2) noexcept
	{
		return Matrix4<T>
		{
			mat1.a * mat2.a + mat1.b * mat2.e + mat1.c * mat2.i + mat1.d * mat2.m,
			mat1.a * mat2.b + mat1.b * mat2.f + mat1.c * mat2.j + mat1.d * mat2.n,
			mat1.a * mat2.c + mat1.b * mat2.g + mat1.c * mat2.k + mat1.d * mat2.o,
			mat1.a * mat2.d + mat1.b * mat2.h + mat1.c * mat2.l + mat1.d * mat2.p,
																			   
			mat1.e * mat2.a + mat1.f * mat2.e + mat1.g * mat2.i + mat1.h * mat2.m,
			mat1.e * mat2.b + mat1.f * mat2.f + mat1.g * mat2.j + mat1.h * mat2.n,
			mat1.e * mat2.c + mat1.f * mat2.g + mat1.g * mat2.k + mat1.h * mat2.o,
			mat1.e * mat2.d + mat1.f * mat2.h + mat1.g * mat2.l + mat1.h * mat2.p,
																			   
			mat1.i * mat2.a + mat1.j * mat2.e + mat1.k * mat2.i + mat1.l * mat2.m,
			mat1.i * mat2.b + mat1.j * mat2.f + mat1.k * mat2.j + mat1.l * mat2.n,
			mat1.i * mat2.c + mat1.j * mat2.g + mat1.k * mat2.k + mat1.l * mat2.o,
			mat1.i * mat2.d + mat1.j * mat2.h + mat1.k * mat2.l + mat1.l * mat2.p,
																			   
			mat1.m * mat2.a + mat1.n * mat2.e + mat1.o * mat2.i + mat1.p * mat2.m,
			mat1.m * mat2.b + mat1.n * mat2.f + mat1.o * mat2.j + mat1.p * mat2.n,
			mat1.m * mat2.c + mat1.n * mat2.g + mat1.o * mat2.k + mat1.p * mat2.o,
			mat1.m * mat2.d + mat1.n * mat2.h + mat1.o * mat2.l + mat1.p * mat2.p
		};

	}

	template<typename T>
	inline constexpr std::optional<Matrix4<T>> operator/(const Matrix4<T>& mat1, const Matrix4<T>& mat2) noexcept
	{
		Matrix4<T> mat_r;

		std::optional<Matrix4<T>> inver{ mat2.inverse() };

		if (inver)
		{
			mat_r = mat1 * (*inver);
			return std::optional<Matrix4<T>>{ std::move(mat_r) };
		}

		return std::nullopt;
	}


	template<typename T>
	inline constexpr Vector4<T> operator*(const Matrix4<T>& mat, const Vector4<T>& vec) noexcept
	{
		return Vector4<T>
		{
			mat.a * vec.x + mat.b * vec.y + mat.c * vec.z + mat.d * vec.w,
			mat.e * vec.x + mat.f * vec.y + mat.g * vec.z + mat.h * vec.w,
			mat.i * vec.x + mat.j * vec.y + mat.k * vec.z + mat.l * vec.w,
			mat.m * vec.x + mat.n * vec.y + mat.o * vec.z + mat.p * vec.w
		};
	}

	template<typename T>
	inline constexpr Vector4<T> operator*(const Matrix4<T>& mat, const Vector3<T>& vec) noexcept
	{
		return Vector4<T>
		{
			mat * Vector4<T>{vec}
		};
	}



} // mpml