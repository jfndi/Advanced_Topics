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