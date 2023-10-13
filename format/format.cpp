#include <format>
#include <iostream>
#include <string_view>
#include <numbers>

using namespace std;
using numbers::pi;

template <typename T>
struct Frac
{
	T n;
	T d;
};

constexpr void print(const string_view& str_fmt, auto&&... args)
{
	fputs(vformat(str_fmt, make_format_args(args...)).c_str(), stdout);
}

template <typename T>
struct formatter<Frac<T>> : formatter<int>
{
	template <typename Context>
	auto format(const Frac<T>& f, Context& ctx) const
	{
		return format_to(ctx.out(), "{}/{}", f.n, f.d);
	}
};

int main()
{
	const int inta{ 47 };
	const char* human{ "earthlings" };
	const string_view alien{ "vulcans" };
	const double df_pi{ pi };

	cout << format("Hello {}\n", human);

	print("Hello {}, we are {}\n", human, alien);
	print("Hello {1}, we are {0}\n", human, alien);

	print("pi is {}\n", df_pi);
	print("pi is {:.5}\n", df_pi);
	print("inta is {1:}, pi is {0:.5}\n", df_pi, inta);

	print("inta is [{:*<10}]\n", inta);
	print("inta is [{:0>10}]\n", inta);
	print("inta is [{:^10}]\n", inta);
	print("inta is [{:_^10}]\n", inta);

	print("{:>8}: [{:04X}]\n", "Hex", inta);
	print("{:>8}: [{:4o}]\n", "Octal", inta);
	print("{:>8}: [{:4d}]\n", "Decimal", inta);

	Frac<long> n{ 3, 5 };
	print("Frac: {}\n", n);
}