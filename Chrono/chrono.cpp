//
// Project: Chrono
// Filename: chrono.cpp
// Creator: Jean-François Ndi
// Creation Date: 5-9-2023 @ 8:10 AM
//
#include <format>
#include <string>
#include <chrono>
#include <ratio>
/*
 * From CppReference:
 * ==================
 * C++ includes support for two types of time manipulation:
 * The chrono library, a flexible collection of types that track time with varying
 * degrees of precision (e.g. std::chrono::time_point).
* C-style date and time library (e.g. std::time).
 * std::chrono library
 * The chrono library defines three main types as well as utility functions and 
 * common typedefs:
 * - clocks,
 * - time points,
 * - durations.
 * Clocks:
 * -------
 * A clock consists of a starting point (or epoch) and a tick rate. For example, 
 * a clock may have an epoch of January 1, 1970 and tick every second. C++ 
 * defines several clock types.
 * Time point:
 * -----------
 * A time point is a duration of time that has passed since the epoch of a 
 * specific clock.
 * Duration:
 * ---------
 * A duration consists of a span of time, defined as some number of ticks of some 
 * time unit. For example, "42 seconds" could be represented by a duration 
 * consisting of 42 ticks of a 1-second time unit.
 */
using namespace std;

constexpr void print(string_view str_fmt, auto&&... args)
{
	fputs(vformat(str_fmt, make_format_args(args...)).c_str(), stdout);
}

constexpr auto newline = [] { print("\n"); ; };

using chrono::duration;

//
// Aliases. 
//
using seconds = duration<double>;
using milliseconds = duration<double, milli>;
using microseconds = duration<double, micro>;
using fps24 = duration<unsigned long, ratio<1, 24>>;

constexpr uint64_t MAX_PRIME{ 0x1FFF };

string make_commas(const uint64_t num)
{
	auto s = to_string(num);

	for (auto l = static_cast<int>(s.length()) - 3; l > 0; l -= 3)
		s.insert(l, ",");

	return s;
}

//
// Define the Callable concept.
//
template<typename T>
concept Callable = requires(T f) { f(); };

seconds timer(const Callable auto& f)
{
	using timer_clock = chrono::steady_clock;

	auto t1 = timer_clock::now();
	auto count = f();
	auto t2 = timer_clock::now();

	seconds secs{ t2 - t1 };

	print("Found {} prim in range.\n", make_commas(count));

	return secs;
}

uint64_t count_primes()
{
	constexpr auto isprime = [](const uint64_t n)
		{
			for (uint64_t i{ 2 }; i < n / 2; ++i)
			{
				if (n % i == 0)
					return true;
			}

			return false;
		};

	uint64_t count{ 0 };
	uint64_t start{ 2 };
	uint64_t end{ MAX_PRIME };
	for (uint64_t i{ start }; i <= end; ++i)
	{
		if (isprime(i))
			++count;
	}

	return count;
}

int main()
{
	auto t = std::chrono::system_clock::now();
	print("system_clock::now is {:%F %T %Z}\n", t);
	newline();

	print("counting primes up to {}\n", make_commas(MAX_PRIME));
	auto secs{ timer(count_primes) };
	newline();

	print("time elapsed: {:.3f} sec\n", secs.count());
	print("time elapsed: {:.3f} ms\n", milliseconds(secs).count());
	print("time elapsed: {:.3e} us\n", microseconds(secs).count());
	print("time elapsed: {} frames at 24 fps\n", floor<fps24>(secs).count());
	newline();

	print("time elapsed: {:.3}\n", secs);
	print("time elapsed: {:.3}\n", milliseconds(secs));
	print("time elapsed: {:.3}\n", microseconds(secs));
	newline();
}