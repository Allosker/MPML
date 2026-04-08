#pragma once
// MIT
// Allosker - 2025
// ===================================================
// Defines some overloads for the 'iostream' standard library.
// ===================================================

#include <iostream>
#include <format>
#include <print>

#include "mpml/matrices/matrix.hpp"

#ifndef NO_MATRIX_LINEAR_PRINTING
#	define MATRIX_LINEAR_PRINTING "\n"
#else
#	define MATRIX_LINEAR_PRINTING " "
#endif


template <typename T>
struct std::formatter<mpml::Matrix2<T>> 
{
	constexpr auto parse(std::format_parse_context& ctx) {
		return ctx.begin(); // no custom format specifiers
	}

	auto format(const mpml::Matrix2<T>& m, std::format_context& ctx) const {
		return std::format_to(ctx.out(), "[{}, {}]" MATRIX_LINEAR_PRINTING "[{}, {}]", 
		m[0][0], m[0][1],
		 m[1][0], m[1][1]);
	}
};

template <typename T>
struct std::formatter<mpml::Matrix3<T>> 
{
	constexpr auto parse(std::format_parse_context& ctx) {
		return ctx.begin(); // no custom format specifiers
	}

	auto format(const mpml::Matrix3<T>& m, std::format_context& ctx) const {
		return std::format_to(ctx.out(), "[{}, {}, {}]" MATRIX_LINEAR_PRINTING "[{}, {}, {}]" MATRIX_LINEAR_PRINTING "[{}, {}, {}]",
		 m[0][0], m[0][1], m[0][2], 
		 m[1][0], m[1][1], m[1][2], 
		 m[2][0], m[2][1], m[2][2]);
	}
};

template <typename T>
struct std::formatter<mpml::Matrix4<T>> 
{
	constexpr auto parse(std::format_parse_context& ctx) {
		return ctx.begin(); // no custom format specifiers
	}

	auto format(const mpml::Matrix4<T>& m, std::format_context& ctx) const {
		return std::format_to(ctx.out(), "[{}, {}, {}, {}]" MATRIX_LINEAR_PRINTING "[{}, {}, {}, {}]" MATRIX_LINEAR_PRINTING "[{}, {}, {}, {}]" MATRIX_LINEAR_PRINTING "[{}, {}, {}, {}]",
		 m[0][0], m[0][1], m[0][2], m[0][3],
		 m[1][0], m[1][1], m[1][2], m[1][3],
		 m[2][0], m[2][1], m[2][2], m[2][3]);
	}
};



template<typename T>
std::ostream& operator<<(std::ostream& out, const mpml::Matrix2<T>& mat)
{
	out << std::format("{}", mat);
	return out;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const mpml::Matrix3<T>& mat)
{
	out << std::format("{}", mat);
	return out;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const mpml::Matrix4<T>& mat)
{
	out << std::format("{}", mat);
	return out;
}


