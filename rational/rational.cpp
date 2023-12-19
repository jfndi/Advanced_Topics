//
// Project: rational
// Filename: rational.cpp
// Creator: Jean-François Ndi
// Creation Date: 31-8-2023 @ 5:04 AM
//
#include <format>
#include <string>

using std::string;

constexpr void print(const std::string_view str_fmt, auto&&... args)
{
	fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

const string nanstr{ "[NAN]" };

class Rational
{
	int n{ 0 };
	int d{ 1 };

public:
	Rational(int numerator = 0, int denominator = 1) :
		n(numerator), d(denominator)
	{}
	Rational(const Rational& rhs) : n(rhs.n), d(rhs.d) {}
	~Rational();

	int numerator() const { return n; }
	int denominator() const { return d; }

	Rational reduce() const;
	string str() const;
	string raw_str() const;

	Rational& operator=(const Rational&);
	Rational operator+(const Rational&) const;
	Rational operator-(const Rational&) const;
	Rational operator*(const Rational&) const;
	Rational operator/(const Rational&) const;
};

Rational Rational::reduce() const
{
	if (n == 0 || d <= 3)
		return *this;

	for (auto div = d; div; --div)
	{
		if (n % div == 0 && d % div == 0)
			return Rational(n / div, d / div);
	}

	return *this;
}

string Rational::str() const
{
	if (d == 0)
		return nanstr;
	if (d == 1 || n == 0)
		return std::to_string(n);

	auto abs_n = abs(n);
	if (abs_n > d)
	{
		auto whole = n / d;
		auto remainder = n % d;
		if (remainder)
			return std::to_string(whole) + " " + Rational(remainder, d).str();
		else
			return std::to_string(whole);
	}
	else
		return reduce().raw_str();
}

string Rational::raw_str() const
{
	return std::to_string(n) + "/" + std::to_string(d);
}

Rational& Rational::operator=(const Rational& rhs)
{
	if (this != &rhs)
	{
		n = rhs.n;
		d = rhs.d;
	}
	return *this;
}

Rational Rational::operator+(const Rational& rhs) const
{
	return Rational((n * rhs.d) + (d * rhs.n), d * rhs.d);
}

Rational Rational::operator-(const Rational& rhs) const
{
	return Rational((n * rhs.d) - (d * rhs.n), d * rhs.d);
}

Rational Rational::operator*(const Rational& rhs) const
{
	return Rational(n * rhs.n, d * rhs.d);
}

Rational Rational::operator/(const Rational& rhs) const
{
	return Rational(n * rhs.d, d * rhs.n);
}

Rational::~Rational()
{
	n = 0;
	d = 1;
}

template<>
struct std::formatter<Rational> : std::formatter<unsigned>
{
	template<typename FormatContext>
	auto format(const Rational& o, FormatContext& ctx) const
	{
		return format_to(ctx.out(), "{}", o.str());
	}
};

int main() {
	Rational a{ 7 };        
	print("a is: {} = {}\n", a.raw_str(), a);

	Rational b(25, 15);     
	print("b is: {} = {}\n", b.raw_str(), b);

	auto c = b;
	print("c is: {} = {}\n", c.raw_str(), c);

	Rational d;     
	print("d is: {} = {}\n", d.raw_str(), d);

	d = c;          
	print("d is: {} = {}\n", d.raw_str(), d);

	auto& e = d;    
	d = e;         
	print("e is: {} = {}\n", e.raw_str(), e);
	print("d is: {} = {}\n", d.raw_str(), d);

	print("\n");
	print("a + b = {}\n", a + b);
	print("a - b = {}\n", a - b);
	print("a * b = {}\n", a * b);
	print("a / b = {}\n", a / b);
}