#include <iostream>
#include <fstream>

/*
 * By defautlt streams do not throw exceptions. The reason is historical: they
 * are older than the exceptions and later the behavior was kept in order to 
 * avoid breaking software written in the mean time. Additionnaly, failing I/O
 * is nothing exceptional, it is quite common and checking errors would be
 * natural.
 */
using namespace std;

int main()
{
	ifstream infile{};
	string filename{ "some_missing_file.xyz" };
	bool opened = false;

	while (!opened)
	{
		infile.open(filename);
		if (infile.good())
			opened = true;
		else
		{
			cout << "The file '" << filename
				<< "' does not exist (or can't be opened), "
				<< "please give a new file name: ";
			cin >> filename;
		}
	}

	int i{};
	double d{};
	infile >> i >> d;
	if (infile.good())
		cout << "i is  " << i << ", d is " << d << '\n';
	else
		cout << "Could not correctly read the content.\n";
	infile.close();
}