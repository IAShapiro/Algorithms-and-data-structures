#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

int n, m, k;
std::vector<long> dist_1_to_x, dist_x_to_n;
std::vector <std::vector <std::pair<std::pair<int, int>, int> > > graph0, graph_reverse;//graph[i] - список ребер из вершины i. 
// std::pair<std::pair<int, int>, int> - <<вершина-конец, вес_ребра>, номер_ребра>
/*
std::vector<long> Dijkstra2(std::vector<long> dist, int start, std::vector<std::vector<std::pair<std::pair<int, int>, int>>> graph)
{
	dist[start] = 0;
	std::vector<bool> visit(n);

	for (int i = 0; i < n; i++) {
		int min_vertex = -1;

		for (int j = 0; j < n; ++j) {
			if (!visit[j] && (min_vertex == -1 || dist[j] < dist[min_vertex])) {
				min_vertex = j;
			}
		}

		if (dist[min_vertex] == INT_MAX) {
			break;
		}

		visit[min_vertex] = true;

		for (int j = 0; j < graph[min_vertex].size(); j++) {
			int vertex_end = graph[min_vertex][j].first.first;
			long len = graph[min_vertex][j].first.second;

			if (dist[min_vertex] + len < dist[vertex_end]) {
				dist[vertex_end] = dist[min_vertex] + len;
			}
		}
	}
	return dist;
}*/
/*
std::vector<long> Dijkstra3(std::vector<long> dist, int start, std::vector<std::vector<std::pair<std::pair<int, int>, int>>> graph)
{
	dist[start] = 0;

	std::set <std::pair<int, long> > queue;
	queue.insert(std::pair<int, long>{start, dist[start]});

	while (!queue.empty()) {
		int v = queue.begin()->first;
		queue.erase(queue.begin());

		for (int j = 0; j < static_cast<int>(graph[v].size()); j++) {
			int vertex_end = graph[v][j].first.first;
			long len = graph[v][j].first.second;

			if (dist[v] + len < dist[vertex_end]) {
				queue.erase(std::pair<int, long>{vertex_end, dist[vertex_end]});
				dist[vertex_end] = dist[v] + len;
				queue.insert(std::pair<int, long>{vertex_end, dist[vertex_end]});
			}
		}
	}

	return dist;
}
*/

std::vector<long> Dijkstra(std::vector<long> dist, int start, std::vector<std::vector<std::pair<std::pair<int, int>, int>>> graph)
{
	dist[start] = 0;

	std::priority_queue <std::pair<int, long> > queue;
	queue.push(std::pair<int, long>{0, start});

	while (!queue.empty()) {
		int vertex = queue.top().second, cur_dist = -queue.top().first;
		queue.pop();

		if (cur_dist <= dist[vertex])
		{
			for (int j = 0; j < static_cast<int>(graph[vertex].size()); j++) {
				int vertex_end = graph[vertex][j].first.first;
				long len = graph[vertex][j].first.second;

				if (dist[vertex] + len < dist[vertex_end]) {
					dist[vertex_end] = dist[vertex] + len;
					queue.push(std::pair<int, long>{-dist[vertex_end], vertex_end});
				}
			}
		}
	}

	return dist;
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

	fin >> n >> m >> k;

	graph0.resize(n);
	graph_reverse.resize(n);

	for (int i = 0; i < m; i++)
	{
		int tmp1, tmp2, tmp3;
		fin >> tmp1 >> tmp2 >> tmp3;

		graph0[tmp1 - 1].push_back(std::pair<std::pair<int, int>, int>{ {tmp2 - 1, tmp3}, i + 1});
		graph_reverse[tmp2 - 1].push_back(std::pair<std::pair<int, int>, int>{ {tmp1 - 1, tmp3}, i + 1});
	}

	dist_1_to_x.resize(n);
	std::fill(dist_1_to_x.begin(), dist_1_to_x.end(), INT_MAX);
	dist_x_to_n.resize(n);
	std::fill(dist_x_to_n.begin(), dist_x_to_n.end(), INT_MAX);

	dist_1_to_x = Dijkstra(dist_1_to_x, 0, graph0);
	dist_x_to_n = Dijkstra(dist_x_to_n, n - 1, graph_reverse);

	long min_way_length = dist_1_to_x[n - 1];

	if (min_way_length != INT_MAX) {
		std::vector<int> list_of_answer;

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < static_cast<int>(graph0[i].size()); j++)
			{
				std::pair<std::pair<int, int>, int> tmp = graph0[i][j];

				if (dist_1_to_x[i] != INT_MAX && dist_x_to_n[tmp.first.first] != INT_MAX && dist_1_to_x[i] + dist_x_to_n[tmp.first.first] + tmp.first.second <= min_way_length + k)
				{
					list_of_answer.push_back(tmp.second);
				}
			}
		}

		std::sort(list_of_answer.begin(), list_of_answer.end());

		fout << list_of_answer.size() << std::endl;
		for (int numbs_of_edges : list_of_answer)
		{
			fout << numbs_of_edges << std::endl;
		}

	}
	else
	{
		fout << 0 << std::endl;
	}

	fin.close();
	fout.close();
	return 0;
}