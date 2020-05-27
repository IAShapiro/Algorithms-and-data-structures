#pragma comment(linker, "/STACK:33554432")
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <iostream>

struct three
{
	long b;
	long l;
	long r;
};

three bynary_search(const std::vector<int> &mas, const int &value)
{

	long left = 0, right = mas.size() - 1, left2 = 0;
	while (left < right)
	{
		long middle = (left + right) / 2;
		if (mas[middle] > value)
			right = middle;
		else if (mas[middle] == value)
		{
			right = middle;
			left2 = middle;
		}
		else
			left = middle + 1;
	}

	if (left2 == 0)
	{
		left2 = left;
	}

	if (mas[left] > value)
	{
		return three{0, left, left};
	}
	if (mas[left] < value)
	{
		return three{ 0, left + 1, left + 1 };
	}

	right = mas.size() - 1;
	while (left2 < right)
	{
		long middle = (left2 + right) / 2;
		if (mas[middle] > value + 1)
			right = middle;
		else if (mas[middle] == value + 1)
		{
			right = middle;
		}
		else
			left2 = middle + 1;
	}

	if (mas[left2] < value + 1)
	{
		return three{ 1, left, left2 + 1 };
	}
	else
		return three{ 1, left, left2};	
}

int main() {
	/*std::ifstream fin("input.txt");
	if (!fin.is_open())
	{
		return 1;
	}

	std::ofstream fout("output.txt");
	if (!fout.is_open())
	{
		return 1;
	}*/

	std::string tmp;
	int length;
	std::cin >> length;
	std::vector<int> arr;
	arr.resize(length);
	for (int i = 0; i < length; i++)
	{
		std::cin >> arr[i];
	}
	int call_count;
	std::cin >> call_count;

	for (int i = 0; i < call_count; i++)
	{
		int k;
		std::cin >> k;
		three tmpt = bynary_search(arr, k);

		std::cout << tmpt.b << " " << tmpt.l << " " << tmpt.r << '\n';
	}

	//fin.close();
	//fout.close();
	return 0;
}