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

	template<typename T>
	[[nodiscard]] constexpr Matrix4<T> perspective(const T& width, const T& height, const T& near, const T& far, const T& fov, bool right_handed=false)
	{
		if constexpr (near < 0 || far < near)
			throw std::runtime_error("ERROR::MATH::PERSPECTIVE_MATRIX::Far/Near planes is/are too low");
		if constexpr (width == 0 || height == 0)
			throw std::runtime_error("ERROR::MATH::DIVISION_BY_ZERO");


		const T f{ 1 / (std::tan(fov / 2)) };
		
		const T a{ width / height };


		if constexpr (!right_handed)
			return Matrix4<T>
			{
				(f / a), 0, 0, 0,
				0, f, 0, 0,
				0, 0, (far / (far - near)), -((near * far) / (far - near)),
				0, 0, 1, 0
			};
		else
			return Matrix4<T>
			{
				(f / a), 0, 0, 0,
				0, f, 0, 0,
				0, 0, ((far + near) / (near - far)), -((2 * far * near) / (near - far)),
				0, 0, -1, 0
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