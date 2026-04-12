#pragma once
// MIT
// Allosker - 2025
// ===================================================
// Mostly for Graphics Matrix functions, defines some utility functions to create matrices
// ===================================================

#include "mpml/matrices/matrix4.hpp"

#include "mpml/utilities/angle.hpp"

#include "mpml/quaternions/quaternions.hpp"

#include "mpml/vectors/vectors.hpp"


namespace mpml
{

	// 2D transforms

	template<typename T>
	[[nodiscard]] constexpr Matrix3<T> translate(const Matrix3<T>& mat, const Vector2<T>& vec) noexcept
	{
		Matrix3<T> trans_mat{ Identity3<T> };

		trans_mat[0][2] = vec.x;
		trans_mat[1][2] = vec.y;

		return mat * trans_mat;
	}

	template<typename T>
	[[nodiscard]] constexpr Matrix3<T> scale(const Matrix3<T>& mat, const Vector2<T>& vec) noexcept
	{
		Matrix3<T> trans_mat{ Identity3<T> };

		trans_mat[0][0] = vec.x;
		trans_mat[1][1] = vec.y;

		return mat * trans_mat;
	}

	template<typename T>
	[[nodiscard]] constexpr Matrix3<T> scale(const Matrix3<T>& mat, const T& scalar) noexcept
	{
		return scale(mat, Vector2<T>{scalar, scalar});
	}


	template<typename T>
	[[nodiscard]] constexpr Matrix3<T> rotate(const Matrix3<T>& mat, Angle<> theta) noexcept
	{
		Matrix3<T> rot_mat{ Identity3<T> };

		T cos{ std::cos(theta.asRadians()) };
		T sin{ std::sin(theta.asRadians()) };

		rot_mat[0][0] = cos;
		rot_mat[0][1] = -sin;
		rot_mat[1][0] = sin;
		rot_mat[1][1] = cos;

		return mat * rot_mat;
	}


	template<typename T>
	[[nodiscard]] constexpr Matrix3<T> view(const Vector2<T>& center, Angle<> theta) noexcept
	{
		Matrix3<T> view_mat{ Identity3<T> };

		T cos{ std::cos(theta.asRadians()) };
		T sin{ std::sin(theta.asRadians()) };

		view_mat[0][0] = cos;
		view_mat[0][1] = sin;
		view_mat[0][2] = -(center.x * cos) - (center.y * sin);
		view_mat[1][0] = -sin;
		view_mat[1][1] = cos;
		view_mat[1][2] = center.x * sin - center.y * cos;

		return view_mat;
	}

	template<typename T, typename U>
	[[nodiscard]] constexpr Matrix3<T> orthographic_projection(const U& width, const U& height, bool flip_y=true)
	{
		Matrix3<T> ort_mat{ Identity3<T> };

		if(!flip_y)
		{
			ort_mat[0][0] = static_cast<U>(2) / width;
			ort_mat[1][1] = static_cast<U>(2) / height;
		}
		else
		{
			ort_mat[0][0] = static_cast<U>(2) / width;
			ort_mat[0][2] = -static_cast<T>(1);
			ort_mat[1][1] = -(static_cast<U>(2) / height);
			ort_mat[1][2] = static_cast<T>(1);
		}

		return ort_mat;
	}


	// 3D tranforms

	template<typename T>
	[[nodiscard]] constexpr Matrix4<T> translate(const Matrix4<T>& mat, const Vector3<T>& vec) noexcept
	{
		Matrix4<T> new_mat{ Identity4<float> };

		new_mat.m = vec.x;
		new_mat.n = vec.y;
		new_mat.o = vec.z;

		return mat * new_mat;
	}

	template<typename T>
	[[nodiscard]] constexpr Matrix4<T> scale(const Matrix4<T>& mat, const Vector3<T>& vec) noexcept
	{
		Matrix4<T> new_mat{ Identity4<float> };

		new_mat.a = vec.x;
		new_mat.f = vec.y;
		new_mat.k = vec.z;

		return mat * new_mat;
	}

	template<typename T>
	[[nodiscard]] constexpr Matrix4<T> scale(const Matrix4<T>& mat, const T& scalar) noexcept
	{
		return scale(mat, Vector3<T>{ scalar, scalar, scalar });
	}

	template<typename T, typename U>
	[[nodiscard]] constexpr Matrix4<T> perspective(const Angle<>& fov, const U& width, const U& height, const T& near, const T& far)
	{
		const T rad = fov.asRadians();
		const T h = std::cos(static_cast<T>(0.5) * rad) / std::sin(static_cast<T>(0.5) * rad);
		const T w = h * height / width;

		return Matrix4<T>
		{
			w, 0, 0, 0,
				0, h, 0, 0,
				0, 0, far / (near - far), -static_cast<T>(1),
				0, 0, -(far * near) / (far - near), 0,
		};
	}

	// Make a trasnpsoe for that, it doesn't work
	template<typename T>
	[[nodiscard]] constexpr Matrix4<T> ortho2D(T width, T height, T near, T far)
	{
		return Matrix4<T>
		{
			static_cast<T>(2) / width, 0, 0, -1,
				0, -static_cast<T>(2) / height, 0, 1,
				0, 0, -static_cast<T>(2) / (far - near), -(far + near) / (far - near),
				0, 0, 0, static_cast<T>(1)
		};
	}

	template<typename T>
	[[nodiscard]] constexpr Matrix4<T> ortho(T width, T height, T near, T far)
	{
		const T right{ width / static_cast<T>(2) };
		const T left{ -right };
		const T top{ height / static_cast<T>(2) };
		const T bottom{ -top };

		return Matrix4<T>
		{
			static_cast<T>(2) / (right - left), 0, 0, 0,
				0, static_cast<T>(2) / (top - bottom), 0, 0,
				0, 0, -static_cast<T>(2) / (far - near), 0,
				-((right + left) / (right - left)), -((top + bottom) / (top - bottom)), -(far + near) / (far - near), static_cast<T>(1)
		};
	}

	template<typename T>
	[[nodiscard]] constexpr Matrix4<T> lookAt(const Vector3<T>& eye, const Vector3<T>& center, const Vector3<T>& up) noexcept
	{
		const Vector3<T> f{ Vector3<T>{center - eye}.normal() };
		const Vector3<T> s{ Vector3<T>{f.cross(up)}.normal() };
		const Vector3<T> u{ s.cross(f) };

		return Matrix4<T>
		{
			s.x, u.x, -f.x, 0,
			s.y, u.y, -f.y, 0,
			s.z, u.z, -f.z, 0,
			-(s.dot(eye)), -(u.dot(eye)), f.dot(eye), 1
		};
	}

	template<typename T>
	[[nodiscard]] constexpr Matrix4<T> lookAt(const Vector3<T>& camPos, const Vector3<T>& camForward, const Vector3<T>& camUp, const Vector3<T>& camSide) noexcept
	{
		return Matrix4<T>
		{
			camSide.x, camUp.x, -camForward.x, 0,
			camSide.y, camUp.y, -camForward.y, 0,
			camSide.z, camUp.z, -camForward.z, 0,
			-(camSide.dot(camPos)), -(camUp.dot(camPos)), camForward.dot(camPos), 1
		};
	}


}