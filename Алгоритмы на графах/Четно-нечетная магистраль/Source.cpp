#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <sstream>
#include <list>

using namespace std;
bool is_bipartite = true;
int n, counter = 0, count_color[2] = {0, 0};
std::vector<list<int>> list_edges;
std::vector<bool> color;
std::vector<bool> used;

int bfs(int vertex, bool color_vertex)
{
	int active_count = 1;
	for (auto i = list_edges[vertex - 1].begin(); i != list_edges[vertex - 1].end(); ++i)
	{
		if (used[*i - 1])
		{
			if (color[*i - 1] == color_vertex)
			{
				is_bipartite = false;
			} 
		}
		else
		{
			used[*i - 1] = true;
			color[*i - 1] = !color_vertex;
			count_color[color[*i - 1] % 2]++;
			active_count += bfs(*i, !color_vertex);
		}
	}

	return active_count;
}




int main() {
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

	list_edges.resize(n);
	color.assign(n, false);
	used.assign(n, false);

	std::string tmp;
	int tmp2;
	std::getline(fin, tmp);
	for (int i = 0; i < n; i++)
	{
		std::getline(fin, tmp);
		stringstream ftmp = stringstream(tmp);

		while (ftmp)
		{
			ftmp >> tmp2;
			if (tmp2 != 0)
			{
				list_edges[i].push_back(tmp2);
			}
		}
	}

	for (int i = 1; i <= n; i++)
	{
		if (!used[i - 1]) {
			used[i - 1] = true;
			count_color[false]++;
			tmp2 = bfs(i, false);

			if (tmp2 != n)
			{
				if (is_bipartite)
				{
					counter += std::max(count_color[0], count_color[1]);
				}
				else
				{
					counter++;
				}
			}
			else
			{
				if (is_bipartite)
				{
					fout << "NO\n" << std::max(count_color[0], count_color[1]);
				}
				else
				{
					fout << "YES";
				}
				return 0;
			}

			is_bipartite = true;
			count_color[0] = count_color[1] = 0;
		}
	}

	fout << "NO\n" << counter;

	fout.close();
	fin.close();
	return 0;

}