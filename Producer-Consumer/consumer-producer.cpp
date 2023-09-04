#include <format>
#include <deque>
#include <thread>
#include <mutex>

using namespace std;

constexpr void print(const string_view str_fmt, auto&&... args)
{
	fputs(vformat(str_fmt, make_format_args(args...)).c_str(), stdout);
}

using namespace std::chrono_literals;

constexpr size_t num_items{ 10 };
constexpr auto delay_time{ 250ms };

mutex producer_mutex{};
mutex consumer_mutex{};

deque<size_t> queue{};
atomic_flag finished{};

void sleep_ms(const auto& delay)
{
	this_thread::sleep_for(delay);
}

void producer()
{
	for (size_t i{}; i < num_items; i++)
	{
		sleep_ms(delay_time);

		print("Push {} on the queue.\n", i);
		lock_guard<mutex> lock{ producer_mutex };
		queue.push_back(i);
	}

	lock_guard<mutex> lock{ producer_mutex };
	finished.test_and_set();
}

void consumer()
{
	while (!finished.test())
	{
		lock_guard<mutex> lock{ consumer_mutex };
		while (!queue.empty())
		{
			print("Pop {} from the queue.\n", queue.front());
			queue.pop_front();
		}
	}
}

int main()
{
	/*
	 * You can add some more consumers and producers.
	 * This change is trivial.
	 */
	thread thd1{ producer };
	thread thd2{ consumer };

	thd1.join();
	thd2.join();

	print("Finished.\n");
}