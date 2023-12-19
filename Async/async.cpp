//
// Project: Async
// Filename: async.cpp
// Creator: Jean-François Ndi
// Creation Date: 1-9-2023 @ 3:20 AM
//
#include <format>
#include <list>
#include <chrono>
#include <future>

/*
 * From cppreference:
 * ------------------
 * The function template std::async runs the function f asynchronously
 * (potentially in a separate thread which might be a part of a thread pool) and
 * returns a std::future that will eventually hold the result of that function 
 * call.
 *
 * 1) Behaves as if (2) is called with policy being std::launch::async |
 * std::launch::deferred.
 * 2) Calls a function f with arguments args according to a specific launch 
 * policy policy (see below).
 * The call to std::async synchronizes-with (as defined in std::memory_order) 
 * the call to f, and the completion of f is sequenced-before making the 
 * shared state ready.
 */

using namespace std;
using namespace chrono;

using launch = launch;
using secs = chrono::duration<double>;

constexpr void print(string_view str_fmt, auto&&... args)
{
	fputs(vformat(str_fmt, make_format_args(args...)).c_str(), stdout);
}

struct prime_time
{
	secs duration{};
	int64_t count{};
};

prime_time count_prime(const uint64_t& max)
{
	prime_time ret{};

	constexpr auto isprime = [](uint64_t n)
		{
			for (uint64_t i{ 2 }; i < n / 2; ++i)
			{
				if (n % i == 0)
					return false;
			}
			return true;
		};

	uint64_t start{ 2 };
	uint64_t end{ max };

	auto time_thread_start = steady_clock::now();
	for (auto i = start; i <= end; i++)
	{
		if (isprime(i))
			++ret.count;
	}

	ret.duration = steady_clock::now() - time_thread_start;
	return ret;
}

int main()
{
	constexpr uint64_t max_prime{ 0x1FFFF };
	constexpr size_t num_thread{ 15 };
	list<future<prime_time>> populate;

	print("Start parallel primes.\n");
	auto time_start = steady_clock::now();

	for (auto i = num_thread; i; --i)
		populate.emplace_back(async(count_prime, max_prime));

	for (auto& f : populate)
	{
		static auto i = 0;
		/*
		 * Structure binding (C++17).
		 */
		auto [dur, count] = f.get();
		print("Thread {:02}: found {} primes in {:.5}.\n", ++i, count, dur);
	}

	secs total_duration{ steady_clock::now() - time_start };
	print("Total duration: {:.5}s.\n", total_duration.count());
}