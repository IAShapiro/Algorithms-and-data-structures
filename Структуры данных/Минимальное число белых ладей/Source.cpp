#pragma comment(linker, "/STACK:33554432")
#include <fstream>
#include <vector>
#include <queue>

std::vector<std::vector<int>> table;
std::vector<std::vector<bool>> used;
int n, m, count = 0;
std::queue<std::pair<int, int>> queue;
std::pair<int, int> tmp;

bool is_cor(int i, int j)
{
	return 0 <= i && 0 <= j && i < n && j < m && !used[i][j] && table[i][j] == 0;
}

int main()
{
	std::ifstream fin("in.txt");
	if (!fin.is_open())
	{
		return 1;
	}

	std::ofstream fout("out.txt");
	if (!fout.is_open())
	{
		return 1;
	}

	fin >> n >> m;
	used.resize(n);
	table.resize(n);
	for (auto& i : table)
	{
		i.resize(m);
		for (int& j : i)
		{
			fin >> j;

		}
	}
	for (auto& i : used)
	{
		i.assign(m, false);
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (table[i][j] == 0 && !used[i][j])
			{
				used[i][j] = true;
				queue.push({ i, j });

				while (!queue.empty())
				{
					tmp = queue.front();
					queue.pop();

					if (is_cor(tmp.first - 1, tmp.second))
					{
						queue.push({ tmp.first - 1, tmp.second });
						used[tmp.first - 1][tmp.second] = true;
					}

					if (is_cor(tmp.first, tmp.second - 1))
					{
						queue.push({ tmp.first, tmp.second - 1});
						used[tmp.first][tmp.second - 1] = true;
					}

					if (is_cor(tmp.first + 1, tmp.second))
					{
						queue.push({ tmp.first + 1, tmp.second });
						used[tmp.first + 1][tmp.second] = true;
					}

					if (is_cor(tmp.first, tmp.second + 1))
					{
						queue.push({ tmp.first, tmp.second + 1 });
						used[tmp.first][tmp.second + 1] = true;
					}

				}
				count++;
			}
		}
	}

	fout << count;

	fin.close();
	fout.close();

	return 0;
}