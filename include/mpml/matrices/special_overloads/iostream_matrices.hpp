#pragma once
// MIT
// Allosker - 2025
// ===================================================
// Defines some overloads for the 'iostream' standard library.
// ===================================================

#include <iostream>

#include "matrices/matrix.hpp"

namespace mpml
{
	static bool print_linear{ false };


	template<typename T>
	std::ostream& operator<<(std::ostream& out, const Matrix2<T>& mat)
	{
		out << "\nMatrix2:";

		if (print_linear)
			out << "\na:\t" << mat.a << "\nb:\t" << mat.b << "\nc:\t" << mat.c << "\nd:\t" << mat.d;
		else
			for (size_t i{}; i < 2; i++)
			{
				out << "\n|";

				for (size_t j{}; j < 2; j++)
					out << '\t' << mat[i * 2 + j];

				out << "\t|";
			}
		return out;
	}

	template<typename T>
	std::ostream& operator<<(std::ostream& out, const Matrix3<T>& mat)
	{
		out << "\nMatrix3:";

		if (print_linear)
		{
			out << "\na:\t" << mat.a << "\nb:\t" << mat.b << "\nc:\t" << mat.c;
			out << "\nd:\t" << mat.d << "\ne:\t" << mat.e << "\nf:\t" << mat.f;
			out << "\ng:\t" << mat.g << "\nh:\t" << mat.h << "\ni:\t" << mat.i;
		}
		else
			for (size_t i{}; i < 3; i++)
			{
				out << "\n|";

				for (size_t j{}; j < 3; j++)
					out << '\t' << mat[i * 3 + j];

				out << "\t|";
			}

		return out;
	}

	template<typename T>
	std::ostream& operator<<(std::ostream& out, const Matrix4<T>& mat)
	{
		out << "\nMatrix4:";

		if (print_linear)
		{
			out << "\na:\t" << mat.a << "\nb:\t" << mat.b << "\nc:\t" << mat.c << "\nd:\t" << mat.d;
			out << "\ne:\t" << mat.e << "\nf:\t" << mat.f << "\ng:\t" << mat.g << "\nh:\t" << mat.h;
			out << "\ni:\t" << mat.i << "\nj:\t" << mat.j << "\nk:\t" << mat.k << "\nl:\t" << mat.l;
			out << "\nm:\t" << mat.m << "\nn:\t" << mat.n << "\no:\t" << mat.o << "\np:\t" << mat.p;
		}
		else
			for (size_t i{}; i < 4; i++)
			{
				out << "\n|";

				for (size_t j{}; j < 4; j++)
					out << '\t' << mat[i * 4 + j];

				out << "\t|";
			}

		return out;
	}


} // mpml
