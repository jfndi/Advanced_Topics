//
// Project: absc++14_functor
// Filename: abs_functor.cpp
// Creator: Jean-Fran�ois Ndi
// Creation Date: 11-1-2024 @ 9:18 AM
//
#include <iostream>
#include <complex>

#include "../include/c++1_print_compiler.hpp"

using namespace std;

namespace book
{
	template <typename T>
	struct abs_functor
	{
		typedef T result_type;

		T operator()(const T& x)
		{
			return x < T(0) ? -x : x;
		}
	};

	template <typename T>
	struct abs_functor<complex<T>>
	{
		using result_type = T;

		T operator()(const complex<T>& x)
		{
			return sqrt(real(x) * real(x) + imag(x) * imag(x));
		}
	};

#if __cplusplus >= 201402

	template <typename T>
	decltype(auto) abs(const T&)
	{
		return abs_functor<T>(x);
	}

#elif __cplusplus >= 201103

	template <typename T>
	auto abs(const T& x) -> decltype(abs_functor<T>()(x))
	{
		return abs_functor<T>()(x);
	}

#elif __cplusplus >= 199711

	template <typename T>
	typename abs_functor<T>::result_type
		abs(const T& x)
	{
		return abs_functor<T>()(x);
	}

#else
#warning "Your C++ compiler is prehistoric!!!"
#endif
}

int main()
{
	print_compiler();

	cout << "abs(-7.3) = " << book::abs(-7.3) << '\n';

#if __cplusplus >= 201103
	cout << "abs(3-7i) = " << book::abs(complex<double>(3, -7)) << '\n';
#else
	complex<double> z(3, -7);
	cout << "abs(3-7i) = " << book::abs(z) << '\n';
#endif

	return 0;
}