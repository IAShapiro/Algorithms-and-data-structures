#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

int count_of_matr;
std::pair<int, int> * arr_size_matr;
int ** matrix;

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

	fin >> count_of_matr;

	matrix = new int * [count_of_matr];
	arr_size_matr = new std::pair<int, int>[count_of_matr]{ {0, 0} };
	for (int i = 0; i < count_of_matr; i++)
	{
		fin >> arr_size_matr[i].first >> arr_size_matr[i].second;
		matrix[i] = new int [count_of_matr]{0};
	}
	for (int j = 1; j < count_of_matr; j++)
	{
		for (int i = j - 1; i >= 0; i--)
		{
			int min = INT_MAX;

			for (int k = i; k < j; k++)
			{
				int tmp = matrix[i][k] + matrix[k + 1][j] + arr_size_matr[i].first * arr_size_matr[k].second * arr_size_matr[j].second;

				if (tmp < min)
				{
					min = tmp;
				}
			}

			matrix[i][j] = min;
		}
	}

	fout << matrix[0][count_of_matr - 1];

	fin.close();
	fout.close();
	return 0;
}