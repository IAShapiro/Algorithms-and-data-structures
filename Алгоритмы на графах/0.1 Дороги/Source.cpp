#include <string>
#include <fstream>
#include <vector>

int n, q, count, tmp1, tmp2;
int * size, * parent;

int find(int x)
{
	if (x == parent[x])
	{
		return x;
	}

	return parent[x] = find(parent[x]);//укорачивает путь
}

void _union(int a, int b)
{
	a = find(a);
	b = find(b);

	if (a != b)
	{
		if (size[a] < size[b])
		{
			tmp1 = a;
			a = b;
			b = tmp1;
		}

		parent[b] = a;
		size[b] += size[a];

		count--;
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

	fin >> n >> q;
	count = n;
	size = new int[n];
	
	parent = new int[n];
	for (int i = 0; i < n; i++)
	{
		size[i] = 1;
		parent[i] = i;
	}

	for (int i = 0; i < q; i++)
	{
		fin >> tmp1 >> tmp2;

		_union(tmp1 - 1, tmp2 - 1);
		fout << count << '\n';
	}

	fin.close();
	fout.close();

	return 0;
}