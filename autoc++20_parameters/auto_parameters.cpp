//
// Project: autoc++20_parameters
// Filename: auto_parameters.cpp
// Creator: Jean-François Ndi
// Creation Date: 3-1-2024 @ 8:59 AM
//
#include <iostream>

using namespace std;

namespace dmc
{
	auto max(auto a, auto b)
	{
		return a > b ? a : b;
	}
}

int main()
{
	using namespace dmc;

	cout << "max(3, 7) = " << dmc::max(3, 7) << endl;
	cout << "max(3, 7.1- = " << dmc::max(3, 7.1) << endl;

	return 0;
}