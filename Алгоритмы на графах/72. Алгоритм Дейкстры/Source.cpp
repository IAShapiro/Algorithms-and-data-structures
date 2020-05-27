#pragma comment(linker, "/STACK:33554432")
#include <string>
#include <fstream>
#include <vector>
#include <queue>
#include <list>

int n, m;
std::vector<std::list<std::pair<int, int>>> graph;
std::vector<int> dist;

unsigned int Dijkstra()
{
	dist[0] = 0;
	std::priority_queue <std::pair<int, int> > queue;
	queue.push(std::pair<int, int>{0, 0});
	int vertex, cur_dist;
	while (!queue.empty()) {
		vertex = queue.top().second;
		cur_dist = -queue.top().first;
		queue.pop();

		if (cur_dist <= dist[vertex])
		{
			for(auto edge : graph[vertex])
			{
				if (dist[vertex] + edge.second < dist[edge.first]) {
					dist[edge.first] = dist[vertex] + edge.second;
					queue.push(std::pair<int, int>{-dist[edge.first], edge.first});
				}
			}
		}
	}
	
	return dist[n - 1];
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

	fin >> n >> m;

	graph.resize(n);
	dist.resize(n);
	std::fill(dist.begin(), dist.end(), INT_MAX);

	int tmp1, tmp2, tmp3;
	for (int i = 0; i < m; i++)
	{
		fin >> tmp1 >> tmp2 >> tmp3;
		if (tmp1 != tmp2)
		{
			graph[tmp1 - 1].emplace_back(tmp2 - 1, tmp3);
			graph[tmp2 - 1].emplace_back(tmp1 - 1, tmp3);
		}
	}

	fout << Dijkstra();

	fin.close();
	fout.close();

	return 0;
}