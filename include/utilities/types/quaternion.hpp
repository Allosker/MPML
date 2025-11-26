#pragma once
// MIT
// Allosker - 2025
// ===================================================
// Defines quaternions - acts as a four-tuple of complex numbers, hence its place here.
// ===================================================


#include <array>

namespace mpml
{


template<typename T>
class Quaternion
{
public:

	// Initialization


	// Operations

	// Data Related

	constexpr T* data_ptr() const noexcept;

	// Overloads


// Class Members

	union
	{
		struct { T w, x, y, z; };
		struct { T a, bi, cj, dk; };

		std::array<T, 4> data;
	};
	

};



// Data Related
template<typename T>
inline constexpr T* Quaternion<T>::data_ptr() const noexcept
{
	return &data[0];
}



} // mpml