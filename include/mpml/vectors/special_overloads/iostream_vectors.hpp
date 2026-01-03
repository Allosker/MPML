#pragma once 
// MIT
// Allosker - 2025
// ===================================================
// Defines some overloads for the 'iostream' standard library.
// ===================================================

#include <iostream>

#include "mpml/vectors/vectors.hpp"


template<typename T>
std::ostream& operator<<(std::ostream& out, const mpml::Vector2<T>& vec)
{
	out << "\nVector 2:" << "\nx:\t" << vec[0] << "\ny:\t" << vec[1];
	return out; 
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const mpml::Vector3<T>& vec)
{
	out << "\nVector 3:" << "\nx:\t" << vec[0] << "\ny:\t" << vec[1] << "\nz:\t" << vec[2];
	return out;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const mpml::Vector4<T>& vec)
{
	out << "\nVector 3:" << "\nx:\t" << vec[0] << "\ny:\t" << vec[1] << "\nz:\t" << vec[2] << "\nw:\t" << vec[3];
	return out;
}