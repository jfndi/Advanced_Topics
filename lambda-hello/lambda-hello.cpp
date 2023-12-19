//
// Project: lambda-hello
// Filename: lambda-hello.cpp
// Creator: Jean-François Ndi
// Creation Date: 31-8-2023 @ 5:04 AM
//
#include <format>

using namespace std;

constexpr void print(string_view str_fmt, auto&&... args)
{
	fputs(vformat(str_fmt, make_format_args(args...)).c_str(), stdout);
}

int main()
{
	auto x = [] { print("Hello, heartlings\n"); };
	x();
}