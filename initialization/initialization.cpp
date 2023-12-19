//
// Project: initialization
// Filename: initialization.cpp
// Creator: Jean-François Ndi
// Creation Date: 3-10-2023 @ 2:42 AM
//
#include <format>
#include <initializer_list>
#include <vector>
#include <string>

using namespace std;

constexpr void print(const string_view& str_fmt, auto&&... args)
{
	fputs(vformat(str_fmt, make_format_args(args...)).c_str(), stdout);
}

constexpr auto newline = []{ print("\n"); };

constexpr void pvec(const auto& v)
{
	if (v.empty())
		print("[Empty]\n");
	else
	{
		for (const auto e : v)
			print("{} ", e);
		newline();
	}
}

template <typename T>
class thing
{
	T v{};
	string state{ "undef" };
public:
	thing() : v(T{})
	{
		print("Default constructor.\n");
		state = "zero";
	}

	thing(const T& p) : v(p)
	{
		print("Copy constructor.\n");
		state = "copied value";
	}

	thing(const initializer_list<T>& ilist)
	{
		print("Initializer_list: ");
		for (const auto& e : ilist)
			print("{} ", e);
		newline();

		const auto sz = ilist.size();
		auto pt = ilist.begin();
		if (sz > 1)
			pt += sz / 2;
		v = *pt;

		state = "list constructor";
	}

	thing(const size_t p1, const T& p2)
	{
		print("Specific constructor: {}, {}", p1, p2);
		newline();

		if (p1 < 10)
			return;
		else
			v = p2;

		state = "specific value";
	}

	void status() const
	{
		print("Status: {}, value {}", state, v);
		newline();
	}
};

void initialize_this() 
{
	print("t1: ");
	thing<int> t1{};
	t1.status();
	newline();

	print("t2: ");
	thing<int> t2{ 7 };
	t2.status();
	newline();

	print("t3: ");
	thing t3(42);
	t3.status();
	newline();

	print("t4: ");
	thing<int> t4{ 1, 2, 3, 4, 5 };
	t4.status();
	newline();

	print("t5: ");
	thing<int> t5{ 1, 2 };
	t5.status();
	newline();

	print("t6: ");
	thing<int> t6(1, 2);
	t6.status();
	newline();
}

int main()
{
	int x{};
	print("x is {}\n", x);

	initialize_this();
}
