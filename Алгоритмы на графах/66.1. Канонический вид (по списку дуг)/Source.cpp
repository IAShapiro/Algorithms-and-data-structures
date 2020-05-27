#pragma comment(linker, "/STACK:33554432")
#include <string>
#include <fstream>
#include <vector>
#include <list>

int n;
std::vector<int> p;

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

	p.resize(n);

	int tmp1, tmp2;

	for (int i = 0; i < n - 1; i++)
	{
		fin >> tmp1 >> tmp2;

		p[tmp2 - 1] = tmp1;
	}

	for (int i = 0; i < n; i++)
	{
		fout << p[i] << " ";
	}
	
	fin.close();
	fout.close();

	return 0;
}