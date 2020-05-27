#pragma comment(linker, "/STACK:33554432")
#include <string>
#include <fstream>
#include <vector>

int n, counter = 1;
std::vector<int> p;
std::vector<std::vector<int>> matr;

void dfs(int vertex)
{
	p[vertex] = counter++;
	for (int i = 0; i < n; i++)
	{
		if(matr[vertex][i] == 1)
		{
			if (p[i] == -1)
			{
				dfs(i);
			}
		}
	}
}

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

	fin >> n;
	matr.resize(n);
	for (int i = 0; i < n; i++)
	{
		matr[i].resize(n);
		for (int j = 0; j < n; j++)
		{
			fin >> matr[i][j];
		}
	}
	p.assign(n, -1);

	for (int j = 0; j < n; j++)
	{
		if (p[j] == -1)
		{
			dfs(j);
		}
	}

	for (int i = 0; i < n; i++)
	{

		fout << p[i] << " ";
	}

	fin.close();
	fout.close();

	return 0;
}