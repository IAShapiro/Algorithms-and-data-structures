#pragma comment(linker, "/STACK:33554432")
#include <string>
#include <fstream>
#include <vector>
#include <list>
#include <queue>
#include <iomanip>
#include <unordered_map>
#include <iostream>

typedef std::pair<double, int> pair;
struct pair_hash
{
	std::size_t operator() (const std::pair<double, int> &pair) const
	{
		return std::hash<int>()(static_cast<int>(std::ceil(pair.first * 1000000))) ^ std::hash<int>()(pair.second);
	}
};
struct pair_equal
{
	bool operator()(const std::pair<double, int> &c1, const std::pair<double, int> &c2) const
	{
		return (abs(c1.first - c2.first) <= 0.000000001) && c1.second == c2.second;
	}
};

std::unordered_map<std::pair<double, int>, int, pair_hash, pair_equal> table;

int d, k, n, inf;
auto comp = [](std::pair<double, int> a, std::pair<double, int> b)
{
	return a.first < b.first;
};
std::priority_queue < std::pair<double, int>, std::vector<std::pair<double, int>>, decltype(comp) > queue(comp); // pair<вероятность, глубина вершины>
std::vector<double> p;

int main()
{
	///*
	std::ifstream fin("Tunstall.in");
	if (!fin.is_open())
	{
		return 1;
	}

	std::ofstream fout("Tunstall.out");
	if (!fout.is_open())
	{
		return 1;
	}
	//*/
	/*	
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
	*/

	fin >> d >> k >> n;
	p.resize(k);
	inf = static_cast<int>(pow(d, n));
	int size_table = 0;

	for (int i = 0; i < k; i++)
	{
		fin >> p[i];
	}

	queue.push({ 1, 0 });
	table.insert({ {1, 0}, 1 });
	size_table++;
	std::pair<double, int> tmp_vertex, tmp_vertex2;

	while (size_table - 1 + k <= inf)
	{
		tmp_vertex = queue.top();

		auto it = table.find(tmp_vertex);
		if (it->second == 1) {
			table.erase(tmp_vertex);
			queue.pop();
		}
		else
		{
			it->second--;
		}
		size_table--;

		for (int i = 0; i < k; i++)
		{
			tmp_vertex2 = std::pair<double, int>(tmp_vertex.first * p[i], tmp_vertex.second + 1 );
			auto it2 = table.find(tmp_vertex2);
			if (it2 != table.end()) {
				it2->second++;
			}
			else
			{
				table.insert({ tmp_vertex2, 1 });
				queue.push(tmp_vertex2);
			}
			size_table++;
		}

	}

	double sum = 0;

	for(auto iter: table)
	{
		sum += iter.first.first * iter.first.second * iter.second;
	}

	fout << std::fixed << std::setprecision(3) << sum;

	fin.close();
	fout.close();

	return 0;
}