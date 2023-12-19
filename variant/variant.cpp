//
// Project: variant
// Filename: variant.cpp
// Creator: Jean-François Ndi
// Creation Date: 31-8-2023 @ 5:04 AM
//
#include <format>
#include <string_view>
#include <vector>
#include <variant>

using namespace std;

constexpr void print(string_view str_fmt, auto&&...args)
{
	fputs(vformat(str_fmt, make_format_args(args...)).c_str(), stdout);
}

constexpr auto newline = [] { print("\n"); };

class Animal
{
	string_view _name{};
	string_view _sound{};

public:
	Animal() = delete;
	Animal(string_view n, string_view s) : _name{ n }, _sound{s} {}

	void speak() const
	{
		print("{} says {}\n", _name, _sound);
	}

	void sound(string_view s)
	{
		_sound = s;
	}
};

class Cat : public Animal
{
public:
	Cat(string_view n) : Animal(n, "Meow!") {}
};

class Dog : public Animal
{
public:
	Dog(string_view n) : Animal(n, "Arf!") {}
};

class Wookie : public Animal
{
public:
	Wookie(string_view n) : Animal(n, "Grrrrraaaarrggh!") {}
};

struct animal_speaks
{
	void operator()(const Dog& d) const { d.speak(); }
	void operator()(const Cat& c) const { c.speak(); }
	void operator()(const Wookie& w) const { w.speak(); }
};

int main()
{
	using v_animal = variant<Cat, Dog, Wookie>;
	vector<v_animal> pets{ Cat{"Hobbes"}, Dog{"Fido"}, Cat{"Bill"}, Wookie{"Chewie"} };

	print("-- get method\n");
	for (const v_animal& a : pets)
	{
		auto idx = a.index();

		if (idx == 0) get<Cat>(a).speak();
		if (idx == 1) get<Dog>(a).speak();
		if (idx == 2) get<Wookie>(a).speak();
	}

	newline();

	print("-- get_if method\n");
	for (const v_animal& a : pets)
	{
		if (auto o = get_if<Cat>(&a); o) o->speak();
		else if (auto o = get_if<Dog>(&a); o) o->speak();
		else if (auto o = get_if<Wookie>(&a); o) o->speak();
	}

	newline();

	print("-- visit method\n");
	for (const v_animal& a : pets)
		visit(animal_speaks{}, a);
}