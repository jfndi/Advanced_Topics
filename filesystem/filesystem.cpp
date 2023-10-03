#include <format>
#include <vector>
#include <filesystem>

using namespace std;

namespace fs = std::filesystem;

constexpr void print(const string_view& str_fmt, auto&&... args)
{
	fputs(vformat(str_fmt, make_format_args(args...)).c_str(), stdout);
}

template<>
struct formatter<fs::path> : formatter<int>
{
	template<typename Context>
	auto format(const fs::path& p, Context ctx)
	{
		return format_to(ctx.out(), "{}", p.string());
	}
};

auto newline = [] { print("\n"); };

void printdir(const fs::path& p)
{
	using de = fs::directory_entry;
	vector<de> dir;

	auto dircmp = [](const de& lhs, const de& rhs) -> bool
		{
			return lhs.path().string() < rhs.path().string();
		};

	if (!fs::exists(p))
	{
		print("{} does not exist", fs::absolute(p));
		newline();
	}

	if (fs::is_directory(p))
	{
		for (const auto& de : fs::directory_iterator{ p })
			dir.emplace_back(de);
		sort(dir.begin(), dir.end(), dircmp);
		for (const auto& e : dir)
			print("{} ", fs::relative(e));
		newline();
	}
	else
		print("Not a directory: {}.\n", p);
}

constexpr const char* fp{ "./filesystem.cpp" };
constexpr const char* homedir{ "C:/Users/Kyria" };

int main(void)
{
	fs::path p{ fp };
	print("p: {}\n", p);

	if (!fs::exists(homedir))
	{
		print("{} does notb exist.\n", fs::absolute(homedir));
		return 1;
	}

	try
	{
		print("Current_path: {}\n", fs::current_path());
		print("Change current_path to {}\n", homedir);
		fs::current_path(homedir);
		newline();

		print("Current_path: {}\n", fs::current_path());
		print("Absolute(p): {}\n", fs::absolute(p));
		newline();

		print("Concatenate: {}\n", fs::path{ "Jeff-Progs" } += "README.txt");
		print("Append: {}", fs::path{ "Jeff-Progs" } /= "README.txt");
		newline();

		print("Canonical (.): {}\n", fs::canonical(fs::path(".")));
		newline();

		auto dirpath = fs::path(".") /= "Jeff-Progs";
		print("Directory of {}\n", dirpath);
		printdir(dirpath);
	}
	catch (const fs::filesystem_error& e)
	{
		print("{}\n", e.what());
		print("path1: {}\n", e.path1());
		print("path2: {}\n", e.path2());
	}
}