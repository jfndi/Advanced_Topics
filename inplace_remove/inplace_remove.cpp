//
// Project: inplace_remove
// Filename: inplace_remove.cpp
// Creator: Jean-Fran�ois Ndi
// Creation Date: 31-8-2023 @ 5:04 AM
//
#include <vector>
#include <iostream>
#include <concepts>

using namespace std;

vector<int> input_v{ 1, 1, 2, 2, 2, 3, 3, 5 };

int main()
{
	int pos = 0;
	if (input_v.size())
	{
		int pivot = input_v[pos];
		for (pos = 1; pos < input_v.size();)
		{
			if (pivot == input_v[pos])
				input_v.erase(input_v.begin() + pos);
			else
			{
				pivot = *(input_v.begin() + pos);
				pos++;
			}
		}

		cout << "Final size: " << input_v.size() << endl;
		for (auto& e : input_v)
			cout << e << " ";
		cout << endl;
	}
	else
		cout << "Empty\n";
}