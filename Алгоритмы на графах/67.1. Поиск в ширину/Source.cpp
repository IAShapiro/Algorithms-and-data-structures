#pragma comment(linker, "/STACK:33554432")
#include <string>
#include <fstream>
#include <vector>
#include <list>
#include <queue>

int n, counter = 1;
std::vector<int> p;
std::vector<std::vector<int>> matr;
std::queue<int> q;
std::vector<bool> used;

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
	p.resize(n);
	used.resize(n);
	
	for (int j = 0; j < n; j++)
	{
		if (!used[j])
		{
			q.push(j + 1);
			used[j] = true;
			
			while (!q.empty()) {
				int v = q.front();
				q.pop();
				p[v - 1] = counter++;
				for (int i = 0; i < n; i++) {
					if (matr[v - 1][i] != 0)
					{
						if (!used[i]) {
							used[i] = true;
							q.push(i + 1);
							
						}
					}
				}
			}

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