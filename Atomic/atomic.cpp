//
// Project: Atomic
// Filename: atomic.cpp
// Creator: Jean-François Ndi
// Creation Date: 1-9-2023 @ 3:51 AM
//
#include <format>
#include <string>
#include <list>
#include <thread>
#include <atomic>

/*
 * From cppreference:
 * ------------------
 * Each instantiation and full specialization of the std::atomic template defines
 * an atomic type. If one thread writes to an atomic object while another thread 
 * reads from it, the behavior is well-defined (see memory model for details on 
 * data races).
 *
 * In addition, accesses to atomic objects may establish inter-thread 
 * synchronization and order non-atomic memory accesses as specified by 
 * std::memory_order.
 *
 * std::atomic is neither copyable nor movable.
 */

using namespace std;

atomic_bool ready_flag{};
atomic_uint64_t global_count{};
atomic_flag winner_flag{};

constexpr uint64_t max_count{ 1'000'000 };
constexpr int max_threads{ 100 };

constexpr void print(string_view str_fmt, auto&&... args)
{
	fputs(vformat(str_fmt, make_format_args(args...)).c_str(), stdout);
}

string make_commas(const uint64_t& num)
{
	auto str = to_string(num);

	for (auto position = static_cast<int>(str.length()) - 3; position > 0; position -= 3)
		str.insert(position, ",");

	return str;
}

void sleep_ms(auto ms)
{
	using this_thread::sleep_for;
	using chrono::milliseconds;

	sleep_for(milliseconds((ms)));
}

void count_them(int id)
{
	while (!ready_flag)
		this_thread::yield();

	for (auto i = 0; i < max_count; ++i)
	{
		if (winner_flag.test())
			return;
		++global_count;
	}

	if (!winner_flag.test_and_set())
	{
		print("Thread {:02} won!\n", id);
		winner_flag.notify_all();
	}
}

int main()
{
	list<thread> thread_list{};

	print("Spawn {} threads.\n", max_threads);
	for (auto i = 0; i < max_threads; ++i)
		thread_list.emplace_back(count_them, i);

	sleep_ms(25);
	print("Go!\n");
	ready_flag = true;

	for (auto& t : thread_list)
		t.join();

	print("Global count is: {}.\n", make_commas(global_count));
}