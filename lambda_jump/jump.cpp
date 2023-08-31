#include <format>
#include <iostream>
#include <string>
#include <map>
#include <exception>

using namespace std;

constexpr void print(string_view str_fmt, auto&&... args)
{
	fputs(vformat(str_fmt, make_format_args(args...)).c_str(), stdout);
}

const char prompt(const char* p)
{
	auto char_upper = [](char c) -> char
		{
			if (c >= 'a' && c <= 'z')
				return c - ('a' - 'A');
			else if (c < 'A' || c > 'z')
				return '\0';
			else
				return c;
		};

	string r{};
	print("{} > ", p);
	getline(cin, r, '\n');

	if (r.size() < 1)
		return '\0';
	else if (r.size() > 1)
	{
		print("Response too long");
		return '\0';
	}
	else if (r.size() == 0)
	{
		print("Response too short");
		return '\0';
	}
	else
		return char_upper(r.at(0));
}

bool jump(const char select)
{
	using jumpfunc = void (*)();

	const map<char, jumpfunc> jumpmap
	{
		{'A', [] { print("func A\n"); } },
		{'B', [] { print("func B\n"); } },
		{'C', [] { print("func C\n"); } },
		{'D', [] { print("func D\n"); } }
	};

	try {
		const auto func = jumpmap.at(select);
		func();
	}
	catch (out_of_range)
	{
		print("Invalid response\n");
		return false;
	}

	return true;
}

int main()
{
	const char* pstr{ "What to do? (A/B/C/D/X)" };

	for (auto key = prompt(pstr); key != 'X'; key = prompt(pstr))
	{
		if (key)
			jump(key);
		else
			print("Invalid response\n");
	}

	print("Bye!\n");
}