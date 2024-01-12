//
// Project: vectorc++20_formatted_output
// Filename: vector_formatted_output.cpp
// Creator: Jean-François Ndi
// Creation Date: 12-1-2024 @ 9:35 AM
//
#include <iostream>
#include <memory>
#include <algorithm>
#include <string>
#include <iterator>

//#include <fmt/format.h>
#include <format>

using namespace std;
//using namespace fmt;

namespace dmc
{
	struct range_error {};
	struct incompatible {};

	template <typename Value>
	class vector
	{
		void check_index(int i) const 
		{
			if (i < 0 || i >= my_size)
				throw range_error{};
		}

		void copy(const vector& that)
		{
			std::copy(&that.data[0], &that.data[that.my_size], &data[0]);
		}

	public:
		vector() : my_size{ 0 }, data{ nullptr } {}
		explicit vector(int size) : my_size{ size }, data{ new Value[my_size] } {}

		vector(initializer_list<Value> values) : vector((int)values.size())
		{
			*this = values;
			cout << "Initializer list constructor called\n";
		}

		vector(const vector& that) : vector(that.size())
		{
			copy(that);
		}

		vector(vector&& that) : my_size(that.my_size), data(move(that.data))
		{
			that.my_size = 0;
		}

		vector& operator=(initializer_list<Value> values)&
		{
			check_size((int)values.size());
			std::copy(begin(values), end(values), &data[0]);
			return *this;
		}

		void check_size(int that_size)
		{
			if (my_size != that_size)
				throw incompatible{};
		}

		int size()
		{
			return my_size;
		}

		const Value& operator[](int i) const&
		{
			check_index(i);
			return data[i];
		}

		Value& operator[](int i)&
		{
			check_index(i);
			return data[i];
		}

		Value operator[](int i)&&
		{
			check_index(i);
			return data[i];
		}

	private:
		int my_size;
		unique_ptr<Value[]> data;
	};

	template <typename Value>
	ostream& operator<<(ostream& os, vector<Value>& v)
	{
		os << '[';
		if (v.size() > 0)
			os << v[0];
		for (int i = 1; i < v.size(); i++)
			os << ", " << v[i];
		return os << ']';
	}

	template <typename Value>
	vector<Value> operator+(const vector<Value>& v, const vector<Value>& w)
	{
		int s = v.size();
		w.check_size(s);
		vector<Value> sum(s);

		for (int i = 0; i < s; i++)
			sum[i] = v[i] + w[i];
		return sum;
	}
}

template <typename Value>
struct formatter<dmc::vector<Value>>
{
	constexpr auto parse(format_parse_context& ctx)
	{
		value_format = "{:";
		for (auto it = begin(ctx), ite = end(ctx); it != ite; it++)
		{
			char c = *it;
			if (c == 'c')
				curly = true;
			else
				value_format += c;
			if (c == '}')
				return it;
		}
		return end(ctx);
	}

	template <typename FormatContext>
	auto format(dmc::vector<Value>& v, FormatContext& ctx)
	{
		auto&& out = ctx.out();
		vformat_to(out, curly ? "{{" : "[", make_format_args());
		if (v.size() > 0)
			vformat_to(out, value_format, make_format_args(v[0]));
		for (int i = 0; i < v.size(); i++)
			vformat_to(out, ", " + value_format, make_format_args(v[i]));
		return vformat_to(out, curly ? "}}" : "]", make_format_args());
	}

	bool curly{ false };
	string value_format;
};

int main()
{
	using namespace dmc;

	dmc::vector<double> v{ 1.394, 1e9, 1.0 / 3.0, 1e-20 };
	cout << "v = " << v << ".\n";

	// If C++23 is supported only
	std::print("u = {}, v = {}, w = {}.\n", 2, v, 4);
	std::print("v with empty format string = {}.\n", v);
	std::print("v with f = {:f}.\n", v);
	std::print("v curly with f = {:fc}.\n", v);
	std::print("v curly with 6 fractional digits = {:.6fc}.\n", v);
	std::print("v with 9 symbols and 4 digits = {:9.4f}.\n", v);
	std::print("v in scientific style = {:ec}.\n", v);
	std::print("v hex = {:a}.\n", v);
}