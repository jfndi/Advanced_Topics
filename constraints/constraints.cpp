//
// Project: constraints
// Filename: constraints.cpp
// Creator: Jean-François Ndi
// Creation Date: 31-8-2023 @ 5:04 AM
//
#include <format>
#include <concepts>

using namespace std;

constexpr void print(string_view str_fmt, auto&&...args)
{
	fputs(vformat(str_fmt, make_format_args(args...)).c_str(), stdout);
}

template <typename T>
requires integral<T>
T arg42(const T& arg)
{
	return arg + 42;
}

int main()
{
	//auto n = 7.9;
	auto n = 8;
	print("The answer is {}\n", arg42(n));
}