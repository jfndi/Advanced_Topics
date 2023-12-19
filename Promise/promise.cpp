//
// Project: Promise
// Filename: promise.cpp
// Creator: Jean-François Ndi
// Creation Date: 31-8-2023 @ 3:13 PM
//
#include <format>
#include <list>
#include <chrono>
#include <future>

/*
 * From cppreference:
 * ------------------
 * The class template std::promise provides a facility to store a value or an 
 * exception that is later acquired asynchronously via a std::future object 
 * created by the std::promise object. Note that the std::promise object is 
 * meant to be used only once.
 *
 * Each promise is associated with a shared state, which contains some
 * state information and a result which may be not yet evaluated, evaluated 
 * to a value (possibly void) or evaluated to an exception. A promise may do 
 * three things with the shared state:
 * 
 * - make ready: the promise stores the result or the exception in the shared 
 * state. Marks the state ready and unblocks any thread waiting on a future
 * associated with the shared state.
 * - release: the promise gives up its reference to the shared state. If this 
 * was the last such reference, the shared state is destroyed. Unless this 
 * was a shared state created by std::async which is not yet ready, this 
 * operation does not block.
 * - abandon: the promise stores the exception of type std::future_error with
 * error code std::future_errc::broken_promise, makes the shared state ready, and
 * then releases it.
 * The promise is the "push" end of the promise-future communication channel: the
 * operation that stores a value in the shared state synchronizes-with (as 
 * defined in std::memory_order) the successful return from any function that is 
 * waiting on the shared state (such as std::future::get). Concurrent access to 
 * the same shared state may conflict otherwise: for example multiple callers of 
 * std::shared_future::get must either all be read-only or provide external 
 * synchronization.
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

void count_prime(const uint64_t max, promise<prime_time> pval)
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

	auto t1 = steady_clock::now();
	for (auto i = start; i <= end; i++)
	{
		if (isprime(i))
			++ret.count;
	}

	ret.duration = steady_clock::now() - t1;
	pval.set_value(ret);
}

int main()
{
	constexpr uint64_t max_prime{ 0x1FFFF };
	constexpr size_t num_thread{ 15 };
	list<future<prime_time>> populate;

	print("Start parallel primes.\n");
	auto t1 = steady_clock::now();

	for (auto i = num_thread; i; --i)
	{
		promise<prime_time> promise_o{};
		auto future_o = promise_o.get_future();
		populate.emplace_back(move(future_o));
		thread t(count_prime, max_prime, move(promise_o));
		t.detach();
	}

	for (auto& f : populate)
	{
		static auto i = 0;
		/*
		 * Structure binding (C++17). 
		 */
		auto [dur, count] = f.get();
		print("Thread {:02}: found {} primes in {:.5}.\n", ++i, count, dur);
	}

	secs total_duration{ steady_clock::now() - t1 };
	print("Total duration: {:.5}s.\n", total_duration.count());
}