#include <iostream>
#include <typeinfo>


/*
 * Had to download MTL to get this file.
 */
#include <boost/numeric/mtl/mtl.hpp>

#include <c++1_print_compiler.hpp>
#include <my_c++03_info.hpp>

using namespace std;

/*
 * Used for tagging. 
 */
struct too_small {};
struct too_large {};

template <typename Vector>
class value_range_vector
{
	using value_type = typename Vector::value_type;
	using size_type = typename Vector::size_type;

public:
	value_range_vector(Vector& vref, value_type minv, value_type maxv)
		: vref(vref), minv(minv), maxv(maxv)
	{}

	decltype(auto) operator[](size_type i)
	{
		decltype(auto) value = vref[i];
		if (value < minv)
			throw too_small{};
		if (value > maxv)
			throw too_large{};
		return value;
	}

private:
	Vector& vref;
	value_type minv, maxv;
};

int main()
{
	print_compiler();

	using Vec = mtl::dense_vector<double>;
	Vec v(3, 0);
	v[0] = 2.3;
	v[1] = 8.1;
	v[2] = 9.2;

	value_range_vector<Vec> w(v, 1.0, 10.0);
	decltype(auto) val = w[1];
	cout << "The type of val is " << my_info<decltype(val)>() << endl;
}