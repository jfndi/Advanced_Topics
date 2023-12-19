//
// Project: thread
// Filename: thread.cpp
// Creator: Jean-François Ndi
// Creation Date: 31-8-2023 @ 9:15 AM
//
#include <format>
#include <chrono>
#include <thread>

using namespace std;
using std::thread;

constexpr void print(string_view str_fmt, auto&&... args)
{
	fputs(vformat(str_fmt, make_format_args(args...)).c_str(), stdout);
}

void sleepms(const unsigned ms)
{
	using millis = chrono::milliseconds;

	this_thread::sleep_for(millis(ms));
}

void thread_function(const int n)
{
	print("This is thread{}\n", n);
	auto sleep_duration = 100 * n;

	for (auto i = 0; i < 5; ++i)
	{
		sleepms(sleep_duration);
		print("Thread{} {}ms: loop {}.\n", n, sleep_duration, i + 1);
	}
	print("Finishing.\n");
}

int main()
{
	thread t1{ thread_function, 1 };
	thread t2{ thread_function, 2 };

	/*
	 * Detaches the associated thread. The operating system becomes responsible 
	 * for releasing thread resources on termination. In,other words detach()
	 * allows the calling thread to execute indepently (joignable is false).
	 */

	t1.detach();
	t2.detach();

	print("Main() sleep for 2 seconds.\n");
	sleepms(2000);

	print("End of main.\n");
}