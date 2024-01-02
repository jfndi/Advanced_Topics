#include <iostream>

class value
{
public:
	explicit value(double x) : x{ x } {}

	friend std::ostream& operator<<(std::ostream& os, value v)
	{
		return os << v.x;
	}

	auto operator<=>(const value& v) const = default;

private:
	double x;
};

int main()
{
	using namespace std;

	value x{ 3 }, y{ 5 };

	cout << "x < y: " << boolalpha << (x < y) << endl;
	cout << "x > y: " << boolalpha << (x > y) << endl;
	cout << "x >= y: " << boolalpha << (x >= y) << endl;
	cout << "x <= y: " << boolalpha << (x <= y) << endl;

	cout << "x == y: " << boolalpha << (x == y) << endl;
	cout << "x != y: " << boolalpha << (x != y) << endl;
}