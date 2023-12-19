//
// Project: span
// Filename: span.cpp
// Creator: Jean-François Ndi
// Creation Date: 13-10-2023 @ 6:06 AM
//
#include <format>
#include <span>

using namespace std;

constexpr void print(const string_view& str_fmt, auto&&... args)
{
	fputs(vformat(str_fmt, make_format_args(args...)).c_str(), stdout);
}

template <typename T>
void pspan(const span<T> s)
{
	print("Number of elements: {}\n", s.size());
	print("Size of span: {}\n", s.size_bytes());

	for (auto e : s)
		print("{} ", e);
	print("\n");
}

int main()
{
	int ca1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	pspan<int>(ca1);
}