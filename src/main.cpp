#include "mpml.hpp"

// TODO: 
/*
	- Implement rotations for vector after implmenting angles

*/

using namespace mpml;
int main()
{
	Matrix2<float> m1{ 1,2,3,4 };

	Matrix2<float> m2{ 5,6,7,8 };

	Matrix2<float> m3{ m1 };

	std::cout << m1.pow(6);

	return 0;
}