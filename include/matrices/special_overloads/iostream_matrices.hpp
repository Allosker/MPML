#pragma once
// MIT
// Allosker - 2025
// ===================================================
// Defines some overloads for the 'iostream' standard library.
// ===================================================

#include <iostream>

#include "matrices/matrix.hpp"

template<typename T>
std::ostream& operator<<(std::ostream& out, const mpml::Matrix2<T>& mat)
{
	out << "\nMatrix2:" << "\na:\t" << mat.a << "\nb:\t" << mat.b << "\nc:\t" << mat.c << "\nd:\t" << mat.d;
	return out;
}