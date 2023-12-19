//
// Project: filesystem2
// Filename: filesystem2.cpp
// Creator: Jean-François Ndi
// Creation Date: 1-12-2023 @ 6:34 AM
//
#include <string>
#include <iostream>

#if __has_include(<filesystem>)
#	define FSVERSION 2
#	include <filesystem>
	namespace fs = std::filesystem; // C++17
#elif __has_include(<experimental/filesystem>) // Unlikely by these times (experimental stage, I mean).
#	define FSVERION 1
#	include <experimental/filesystem>
	namespace fs = std::experimental::filesystem::v1;
#endif

using namespace std;

int main(int argc, char* argv[])
{
#ifdef FSVERSION
	cout << (FSVERSION == 2 ? "Mature" : "Experimental") << " filesystem support.\n";

	string path = ".";
	if (argc > 1)
		path = argv[1];

	for (auto& p : fs::directory_iterator(path))
	{
		cout << p;
		if (is_regular_file(p))
			cout << " is a regular file.\n";
		else if (is_directory(p))
			cout << " is a directory.\n";
		else
			cout << " is neither a directory not a file.\n";
	}
#else
	cerr << "Filesystem not supported yet by this compiler.\n"
#endif
}