#pragma once
// MIT
// Allosker - 2025
// ===================================================
// Mostly for Graphics Matrix functions, defines some utility functions to create matrices
// ===================================================

#include "mpml/matrices/matrix4.hpp"

#include "mpml/vectors/vectors.hpp"


namespace mpml
{
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
	[[nodiscard]] constexpr Matrix4<T> scale(const Matrix4<T>& mat, const T& scalar) noexcept
	{
		Matrix4<T> new_mat{ Identity4<float> };

		new_mat.a = scalar;
		new_mat.f = scalar;
		new_mat.k = scalar;

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

	template<typename T, typename U>
	[[nodiscard]] constexpr Matrix4<T> perspective(const Angle& fov, const U& width, const U& height, const T& near, const T& far)
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

	template<typename T, typename U>
	[[nodiscard]] constexpr Matrix4<T> orthographic_projection(const U& width, const U& height, const T& near, const T& far)
	{
		const T right{ static_cast<T>(width / static_cast<U>(2)) };
		const T left{ -right };
		const T top{ static_cast<T>(height / static_cast<U>(2)) };
		const T bottom{ -top };

		return Matrix4<T>
		{
			static_cast<T>(2) / (right - left), 0, 0, 0,
				0, static_cast<T>(2) / (top - bottom), 0, 0,
				0, 0, -static_cast<T>(1) / (far - near), 0,
				-((right + left) / (right - left)), -((top + bottom) / (top - bottom)), near / (far - near), static_cast<T>(1)
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