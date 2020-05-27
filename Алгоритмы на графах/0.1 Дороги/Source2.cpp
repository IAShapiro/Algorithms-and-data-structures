#pragma comment(linker, "/STACK:33554432")
#include <string>
#include <fstream>
#include <vector>

int n, q, count, tmp1, tmp2;
int *t;

int find(int x)
{
	if (t[x] < 0)
	{
		return x;//< 0 - вес
	}

	return t[x] = find(t[x]);//укорачивает путь
}

void _union(int a, int b)
{
	a = find(a);
	b = find(b);

	if (a != b)
	{
		if (t[a] > t[b])
		{
			tmp1 = a;
			a = b;
			b = tmp1;
		}

		t[a] += t[b];
		t[b] = a;
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
	
	t = new int[n];
	for (int i = 0; i < n; i++)
	{
		t[i] = -1;
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