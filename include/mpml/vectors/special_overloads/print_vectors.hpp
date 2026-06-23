#pragma once 
// MIT
// Allosker - 2025
// ===================================================
// Defines some overloads for the 'iostream' standard library.
// ===================================================

#include <iostream>
#include <format>
#include <print>

#include "mpml/vectors/vectors.hpp"


template <typename T>
struct std::formatter<mpml::Vector2<T>> 
{
	constexpr auto parse(std::format_parse_context& ctx) {
		return ctx.begin(); // no custom format specifiers
	}

	auto format(const mpml::Vector2<T>& vec, std::format_context& ctx) const {
		return std::format_to(ctx.out(), "({}, {})", vec[0], vec[1]);
	}
};

template <typename T>
struct std::formatter<mpml::Vector3<T>> 
{
	constexpr auto parse(std::format_parse_context& ctx) {
		return ctx.begin(); // no custom format specifiers
	}

	auto format(const mpml::Vector3<T>& vec, std::format_context& ctx) const {
		return std::format_to(ctx.out(), "({}, {}, {})", vec[0], vec[1], vec[2]);
	}
};

template <typename T>
struct std::formatter<mpml::Vector4<T>> 
{
	constexpr auto parse(std::format_parse_context& ctx) {
		return ctx.begin(); // no custom format specifiers
	}

	auto format(const mpml::Vector4<T>& vec, std::format_context& ctx) const {
		return std::format_to(ctx.out(), "({}, {}, {}, {})", vec[0], vec[1], vec[2], vec[3]);
	}
};



template<typename T>
std::ostream& operator<<(std::ostream& out, const mpml::Vector2<T>& vec)
{
	out << std::format("{}", vec);
	return out; 
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const mpml::Vector3<T>& vec)
{
	out << std::format("{}", vec);
	return out;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const mpml::Vector4<T>& vec)
{
	out << std::format("{}", vec);
	return out;
}