#include "mpml.hpp"

// TODO: 
/*
	- Implement rotations for vector after implmenting angles

*/

using namespace mpml;
int main()
{
	Matrix3<float> mat1{ 
		1,2,3,
		4,9,6,
		7,8,9 
	};
	Matrix3<float> mat2{ 
		10,11,12,
		13,14,15,
		16,17,18
	};

	Matrix4<float> m
	{
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16
	};

	Matrix4<float> m2
	{
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16
	};

	Vector4<float> v
	{
		1,2,3
	};

	std::cout << Matrix4<float>{ m2 * mat::translate{v} };

	return 0;
}