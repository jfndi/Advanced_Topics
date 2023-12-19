//
// Project: sleep
// Filename: sleep.cpp
// Creator: Jean-François Ndi
// Creation Date: 31-8-2023 @ 8:38 AM
//
#include <format>
#include <chrono>
#include <thread>
#include <iostream>

using namespace std;

using chrono::steady_clock;
using chrono::duration;
using this_thread::sleep_for;
using this_thread::sleep_until;

using namespace chrono_literals;

constexpr void print(const string_view str_fmt, auto&&... args)
{
	fputs(vformat(str_fmt, make_format_args(args...)).c_str(), stdout);
}

int main()
{
	print("Let's wait a bit...\n");

	auto t1 = steady_clock::now();
	print("Sleep for 2.5 seconds.\n");
	sleep_for(2s + 500ms);

	print("Sleep for 3 seconds.\n");
	sleep_until(steady_clock::now() + 3s);

	duration<double> dur1 = steady_clock::now() - t1;
	print("Total duration: {:.5}\n", dur1);
}