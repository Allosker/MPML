#pragma once
// MIT
// Allosker - 2026
// ===================================================
// Defines some overloads for the 'iostream'/'print' standard library.
// ===================================================

#include <iostream>
#include <format>
#include <print>

#include "quaternions/quaternions.hpp"


template <typename T>
struct std::formatter<mpml::Quaternion<T>>
{
	constexpr auto parse(std::format_parse_context& ctx) {
		return ctx.begin(); // no custom format specifiers
	}

	auto format(const mpml::Quaternion<T>& q, std::format_context& ctx) const {
		return std::format_to(ctx.out(), "v4({}, {}, {}, {})", q[0], q[1], q[2], q[3]);
	}
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const mpml::Quaternion<T>& q)
{
	out << std::format("{}", q);
	return out;
}