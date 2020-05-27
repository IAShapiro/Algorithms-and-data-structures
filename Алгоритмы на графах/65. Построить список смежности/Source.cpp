#pragma comment(linker, "/STACK:33554432")
#include <string>
#include <fstream>
#include <vector>
#include <list>

int n, m;
std::vector<std::list<int>> matr;

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

	int tmp1, tmp2;

	for (int i = 0; i < m; i++)
	{
		fin >> tmp1 >> tmp2;

		matr[tmp1 - 1].push_back(tmp2);
		matr[tmp2 - 1].push_back(tmp1);
	}

	for (int i = 0; i < n; i++)
	{
		fout << matr[i].size() << " ";
		for (auto j : matr[i])
		{
			fout << j << " ";
		}
		fout << '\n';
	}
	
	fin.close();
	fout.close();

	return 0;
}