#include <format>

constexpr void print(std::string_view str_fmt, auto&&... args)
{
	fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

class num
{
	int value{};
public:
	num(int x = 0) : value(x) {};
	int getvalue() const { return value; }
	void setvalue(int x) { value = x; }

	operator int() { return value; }
	num& operator++();
	num operator++(int);
	num& operator--();
	num operator--(int);
};

/*
 * Pre-increment. 
 */
num& num::operator++()
{
	print("Pre-increment: ");
	value += 1;
	return *this;
}

/*
 * Post-increment. 
 */
num num::operator++(int)
{
	print("Post-increment: ");
	auto tmp = *this;
	value += 1;
	return tmp;
}

/*
 * Pre-decrement. 
 */
num& num::operator--()
{
	print("Pre-decrement: ");
	value -= 1;
	return *this;
}

/*
 * Post-decrement. 
 */
num num::operator--(int)
{
	print("Post-decrement: ");
	auto tmp = *this;
	value -= 1;
	return tmp;
}

/*
 * Formatter specialization. 
 */
template<>
struct std::formatter<num> : std::formatter<unsigned>
{
	template<typename FormatContext>
	auto format(const num& o, FormatContext ctx)
	{
		return format_to(ctx.out(), "{}", o.getvalue());
	}
};

int main()
{
	num n(42);
	print("Value is: {}\n", n);
	print("Value is: {}\n", ++n);
	print("Value is: {}\n", n);
	print("Value is: {}\n", n--);
}