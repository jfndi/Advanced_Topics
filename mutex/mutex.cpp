#include <format>
#include <string_view>
#include <thread>
#include <future>
#include <mutex>
#include <list>
#include <optional>

using namespace std;

constexpr void print(const string_view str_fmt, auto&&... args)
{
	fputs(vformat(str_fmt, make_format_args(args...)).c_str(), stdout);
}

mutex animal_mutex{};

class Animal
{
	using friend_t = list<Animal>;
	string_view s_name{ "unk" };
	friend_t l_friends{};

public:
	Animal() = delete;
	Animal(const string_view n) : s_name{ n } {}

	bool operator==(const Animal& o) const
	{
		/*
		 * Is the underlying buffer pointer the same? 
		 */
		return s_name.data() == o.s_name.data();
	}

	bool add_friend(Animal& o) noexcept
	{
		print("Add friend {} -> {}\n", s_name, o.s_name);
		if (*this == o)
			return false;

		/*
		 * We manipulate the list so take the lock.
		 * The lock will be released when leaving
		 * the method.
		 */
		lock_guard<mutex> l{ animal_mutex };
		if (!is_friend(o))
			l_friends.emplace_back(o);
		if (!o.is_friend(*this))
			o.l_friends.emplace_back(*this);

		return true;
	}

	bool delete_friend(Animal& o)
	{
		print("Delete friend {} -> {}\n", s_name, o.s_name);
		if (*this == o)
			return false;

		/*
		 * We manipulate the list so take the lock.
		 * The lock will be released when leaving
		 * the method.
		 */
		lock_guard<mutex> l{ animal_mutex };
		if (auto it = find_friend(o); it)
			l_friends.erase(it.value());
		if (auto it = find_friend(*this); it)
			l_friends.erase(it.value());

		return true;
	}

	bool is_friend(Animal& o) const
	{
		for (auto& a : l_friends)
		{
			if (a == o)
				return true;
		}

		return false;
	}

	optional<friend_t::iterator> find_friend(Animal& o) noexcept
	{
		for (auto it = l_friends.begin(); it != l_friends.end(); it++)
		{
			if (*it == o)
				return it;
		}

		return {};
	}

	void pfriends() const noexcept
	{
		lock_guard<mutex> l{ animal_mutex };

		auto n_animals = l_friends.size();
		print("{} friends: ", s_name);
		if (!n_animals)
			print("None");
		else
		{
			for (auto n : l_friends)
			{
				print(n.s_name);
				if (--n_animals)
					print(", ");
			}
		}
		print("\n");
	}
};

int main()
{
	auto cat1 = std::make_unique<Animal>("Felix");
	auto tiger1 = std::make_unique<Animal>("Hobbes");
	auto dog1 = std::make_unique<Animal>("Astro");
	auto rabbit1 = std::make_unique<Animal>("Bugs");

	print("Add friends\n");
	auto a1 = async([&] { cat1->add_friend(*tiger1); });
	auto a2 = async([&] { cat1->add_friend(*rabbit1); });
	auto a3 = async([&] { rabbit1->add_friend(*dog1); });
	auto a4 = async([&] { rabbit1->add_friend(*tiger1); });

	a1.wait();
	a2.wait();
	a3.wait();
	a4.wait();

	print("\nPrint animals\n");
	auto p1 = std::async([&] { cat1->pfriends(); });
	auto p2 = std::async([&] { tiger1->pfriends(); });
	auto p3 = std::async([&] { dog1->pfriends(); });
	auto p4 = std::async([&] { rabbit1->pfriends(); });

	p1.wait();
	p2.wait();
	p3.wait();
	p4.wait();

	print("\nDelete Felix/Bugs friendship\n");
	auto a5 = std::async([&] { cat1->delete_friend(*rabbit1); });
	a5.wait();

	print("\nPrint animals\n");
	p1 = std::async([&] { cat1->pfriends(); });
	p2 = std::async([&] { tiger1->pfriends(); });
	p3 = std::async([&] { dog1->pfriends(); });
	p4 = std::async([&] { rabbit1->pfriends(); });

	p1.wait();
	p2.wait();
	p3.wait();
	p4.wait();

	print("\nEnd of main()\n");
}