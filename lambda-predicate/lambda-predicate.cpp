#include <format>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

constexpr void print(string_view str_fmt, auto&&...args)
{
	fputs(vformat(str_fmt, make_format_args(args...)).c_str(), stdout);
}

/*
 * disp_v: display vector.
 */
void disp_v(const auto& v)
{
	if (!v.size())
		return;
	for (auto& e : v)
		print("{} ", e);
}

int main()
{
	vector<int> v1{ 1, 7, 4, 9, 4, 8, 12, 10, 20 };

	auto is_div4 = [](int i) { return i % 4 == 0; };

	auto count = count_if(v1.begin(), v1.end(), is_div4);
	print("Count is {}\n", count);

	vector<int> v2{};
	copy_if(v1.begin(), v1.end(), back_inserter(v2), is_div4);
	disp_v(v2);

	auto char_upper = [](char c) -> char
		{
			if (c >= 'a' && c <= 'z')
				return (c - ('a' - 'A'));
			else
				return c;
		};

	string s1{ "big light in sky slated to appear in east" };
	string s2{};
	string s3{};
	print("\ns1: {}\n", s1);

	transform(s1.begin(), s1.end(), back_inserter(s2), char_upper);
	print("s2: {}\n", s2);

	auto title_case = [char_upper](char c)
		{
			static char prev_c{ ' ' };
			char new_c{ prev_c == ' ' ? char_upper(c) : c };
			prev_c = c;
			return new_c;
		};

	transform(s1.begin(), s1.end(), back_inserter(s3), title_case);
	print("s3: {}\n", s3);
}