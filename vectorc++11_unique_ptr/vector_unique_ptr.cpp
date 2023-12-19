//
// Project: vectorc++11_unique_ptr
// Filename: vector_unique_ptr.cpp
// Creator: Jean-François Ndi
// Creation Date: 3-12-2023 @ 12:14 PM
//
#include <cassert>
#include <iostream>
#include <memory>

class vector
{
public:
	vector(int size) : my_size(size), data(new double[size]) {}
	vector() : my_size(0), data(0) {} // nullptr not available in C++03.

	/*
	 * The following copy constructor is not realy what one would in most cases:
	 *	vector(const vector& v) : my_size(v.my_size), data(v.data) {};
	 * data would be an alias of v.data => open dor to chaos.
	 */
	vector(const vector& v) :
		my_size(v.my_size), data(new double[my_size])
	{
		for (int i = 0; i < my_size; i++)
			data[i] = v.data[i];
	}

	/*
	 * The same considerations holds for the copy assignment.
	 */
	vector operator=(const vector& v)
	{
		assert(v.my_size == my_size);

		for (int i = 0; i < my_size; ++i)
			data[i] = v.data[i];

		return *this;
	}

	int size() const
	{
		return my_size;
	}

	double& operator[](int i) const
	{
		assert(i >= 0 && i < my_size);
		return data[i];
	}

	vector operator+(const vector& v) const
	{
		assert(v.my_size == my_size);

		vector sum(my_size);
		for (int i = 0; i < my_size; ++i)
			sum[i] = (*this)[i] + v[i];

		return sum;
	}

private:
	int my_size;
	std::unique_ptr<double[]> data;
};

std::ostream& operator<<(std::ostream& os, const vector& v)
{
	os << '[';
	if (v.size() > 0)
	{
		os << v[0];
		for (int i = 1; i < v.size(); i++)
			os << ", " << v[i];
	}

	return os << ']';
}

double dot(const vector& v, const vector& w)
{
	double s = 0.0;

	assert(v.size() == w.size());
	for (int i = 0; i < v.size(); i++)
		s += v[i] * w[i];

	return s;
}

int main()
{
	vector v(4);
	v[0] = v[1] = 1.0; v[2] = 2.0; v[3] = -3.0;
	std::cout << v << std::endl;

	vector w(v.size());
	w = v;

	const vector z(w);
	std::cout << "z[3] is " << z[3] << '\n';

	std::cout << "w is " << w << '\n';
	v[1] = 9.;
	std::cout << "w is " << w << '\n';


	vector sum(w + v);

	return 0;
}