#include <format>
#include <string>
#include <vector>
#include <initializer_list>
#include <utility>

using namespace std;

constexpr void print(string_view str_fmt, auto&&... args)
{
	fputs(vformat(str_fmt, make_format_args(args...)).c_str(), stdout);
}

template <typename T>
class container
{
	vector<T> things{};

public:
	container() { print("Default ctor\n"); }
	container(initializer_list<T> il);
	container(const container& rhs);
	~container();
	void reset();
	container<T>& operator=(const container& rhs);
	string str() const;
};

template<typename T>
container<T>::container(initializer_list<T> il) : things{ il.begin(), il.end() }
{
	print("Initializer constructor\n");
}

template <typename T>
container<T>::container(const container<T>& rhs) : things{ rhs.things }
{
	print("Copy ctor\n");
}

template <typename T>
container<T>& container<T>::operator=(const container<T>& rhs)
{
	print("Copy assignment operator\n");
	if (this != &rhs)
		things = rhs.things;

	return *this;
}

template <typename T>
container<T>::~container()
{
	print("dtor\n");
}

template <typename T>
void container<T>::reset()
{
	things.clear();
}

template <typename T>
string container<T>::str() const
{
	string out{};

	if (things.empty())
		return "[empty]";

	for (auto& i : things)
	{
		if (out.size())
			out += ':';
		out += format("{}", i);
	}
	return out;
}

template <typename T>
container<T> f(container<T> o)
{
	return o;
}

int main()
{
	container<string> a{ "one", "two", "three", "four", "five" };
	container<string> b{ "five", "six", "seven" };

	print("a: {}\n", a.str());
	print("b: {}\n", b.str());

	container c(a);

	print("a: {}\n", a.str());
	print("c: {}\n", c.str());
}