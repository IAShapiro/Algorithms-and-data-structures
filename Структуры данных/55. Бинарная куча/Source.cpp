#include <iostream>
#include <fstream>
#include <vector>

int main()
{
	std::ifstream fin("input.txt");
	if (!fin.is_open())
	{
		return 1;
	}

	std::ofstream fout("output.txt");
	if (!fout.is_open())
	{
		return 1;
	}

	int n, tmp;
	fin >> n;

	std::vector<int> arr;
	for (int i = 0; i < n; i++)
	{
		fin >> tmp;
		arr.push_back(tmp);
	}

	bool flag = true;

	if (n != 1)
	{
		for (int i = 1; i < n; i++)
		{
			if ((i % 2 == 1 && arr[i / 2] > arr[i]) || (i % 2 == 0 && arr[(i - 1)/ 2] > arr[i]))
			{
				flag = false;
				break;
			}
		}
	}
	
	fout << (flag == true ? "Yes" : "No");

	fout.close();
	fin.close();
	return 0;
}