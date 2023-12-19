//
// Project: fstream-io-exception
// Filename: fstreamioexception.cpp
// Creator: Jean-François Ndi
// Creation Date: 1-12-2023 @ 5:57 AM
//
#include <iostream>
#include <fstream>

/*
 * If we want to use exceptions when working with streams, we have to unable
 *  them during runtime for each stream.
 */

static void with_exceptions(std::ios& io)
{
	io.exceptions(std::ios_base::badbit | std::ios_base::failbit);
}

int main()
{
	std::ofstream outfile{};

	try
	{
		with_exceptions(outfile);
		outfile.open("f.txt");

		double o1 = 5.2, o2 = 6.2;
		outfile << o1 << o2 << std::endl;
		outfile.close();
	}
	catch (...)
	{
		std::cout << "Exception caught when writing to the output file." << std::endl; // std::endl is used here to make sure that the buffer is flushed.
		return EXIT_FAILURE;
	}

	std::ifstream infile{};

	int i1{}, i2{};
	char c{};
	try
	{
		with_exceptions(infile);
		infile.open("t.txt");
		infile >> i1 >> c >> i2;
	}
	catch (...)
	{
		std::cout << "Exception caught when reading to the input file.\n";
		return EXIT_FAILURE;
	}
	std::cout << "i1 = " << i1 << ", i2 = " << i2;
}