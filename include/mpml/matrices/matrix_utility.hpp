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
		Matrix4<T> new_mat{ mat };

		new_mat.m += vec.x;
		new_mat.n += vec.y;
		new_mat.o += vec.z;

		return new_mat;
	}

	template<typename T>
	[[nodiscard]] constexpr Matrix4<T> scale(const Matrix4<T>& mat, const T& scalar) noexcept
	{
		Matrix4<T> new_mat{ mat };

		new_mat.a += scalar;
		new_mat.f += scalar;
		new_mat.k += scalar;

		return new_mat;
	}

	template<typename T, typename U>
	[[nodiscard]] constexpr Matrix4<T> perspective(const Angle& fov, const U width, const U height, const T& near, const T& far, bool right_handed = false)
	{
		if (near < 0 || far < near)
			throw std::runtime_error("ERROR::MATH::PERSPECTIVE_MATRIX::Far/Near planes is/are too low");
		if (width == 0 || height == 0)
			throw std::runtime_error("ERROR::MATH::DIVISION_BY_ZERO");


		const T ratio{ static_cast<T>(width) / static_cast<T>(height) };

		const T t{ std::tan(fov.asRadians() / static_cast<T>(2)) };

		if (right_handed)
			return Matrix4<T>
		{
			static_cast<T>(1) / (ratio * t), 0, 0, 0,
				0, static_cast<T>(1) / (t), 0, 0,
				0, 0, -(far + near) / (far - near), -static_cast<T>(1),
				0, 0, -(static_cast<T>(2) * far * near) / (far - near), static_cast<T>(1)
		};
		else
			throw std::runtime_error("ERROR::LEFT_HANDED_PERSPECTIVE_MATRIX::Matrix not defined for now");
	}

	template<typename T>
	[[nodiscard]] constexpr Matrix4<T> lookAt(const Vector3<T>& eye, const Vector3<T>& center, const Vector3<T>& up) noexcept
	{
		const Vector3<T> f{ Vector3<T>{center - eye}.normal() };
		const Vector3<T> s{ Vector3<T>{f.cross(up)}.normal() };
		const Vector3<T> u{ s.cross(f) };

		return Matrix4<T>
		{
			s.x, s.y, s.z, -(s.dot(eye)),
			u.x, u.y, u.z, -(u.dot(eye)),
			-f.x, -f.y, -f.z, f.dot(eye),
			0, 0, 0, 1
		};
	}

	template<typename T>
	[[nodiscard]] constexpr Matrix4<T> lookAt(const Vector3<T>& camPos, const Vector3<T>& camForward, const Vector3<T>& camUp, const Vector3<T>& camSide) noexcept
	{
		return Matrix4<T>
		{
			camSide.x, camSide.y, camSide.z, -(camSide.dot(camPos)),
			camUp.x, camUp.y, camUp.z, -(camUp.dot(camPos)),
			-camForward.x, -camForward.y, -camForward.z, camForward.dot(camPos),
			0, 0, 0, 1
		};
	}


}