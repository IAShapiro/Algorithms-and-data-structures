#pragma comment(linker, "/STACK:33554432")
#include <string>
#include <fstream>
#include <vector>

int n, m;
std::vector<std::vector<int>> matr;

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

	fin >> n >> m;

	matr.resize(n);
	for (int i = 0; i < n; i++)
	{
		matr[i].resize(n);
	}

	int tmp1, tmp2;

	for (int i = 0; i < m; i++)
	{
		fin >> tmp1 >> tmp2;

		matr[tmp1 - 1][tmp2 - 1] = 1;
		matr[tmp2 - 1][tmp1 - 1] = 1;

	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			fout << matr[i][j] << " ";
		}
		fout << '\n';
	}
	
	fin.close();
	fout.close();

	return 0;
}