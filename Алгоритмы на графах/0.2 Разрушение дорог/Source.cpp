#pragma comment(linker, "/STACK:33554432")
#include <string>
#include <fstream>
#include <vector>

int n, m, q, count, tmp1, tmp2, j = 0;
int *t, *d;
std::pair<std::pair<int, int>, bool> * mas;//<<город, город>, рарушится?>

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

	fin >> n >> m >> q;
	count = n;
	
	t = new int[n];
	d = new int[q];//номера
	mas = new std::pair<std::pair<int, int>, bool>[m];

	for (int i = 0; i < n; i++)
	{
		t[i] = -1;
	}

	for (int i = 0; i < m; i++)
	{
		fin >> mas[i].first.first >> mas[i].first.second;
		mas[i].second = false;
	}

	for (int i = 0; i < q; i++)
	{
		fin >> d[i];

		mas[d[i] - 1].second = true;
	}

	for (int i = 0; i < m; i++)
	{
		if (!mas[i].second)
		{
			_union(mas[i].first.first - 1, mas[i].first.second - 1);
		}
	}
	//сейчас в count число компонент связности

	for (j = q - 1; j >= 0 && count != 1; j--)
	{
		_union(mas[d[j] - 1].first.first - 1, mas[d[j] - 1].first.second - 1);
	}

	for (int i = 0; i < j + 1; i++)
	{
		fout << '1';
	}

	for (int i = j + 1; i < q; i++)
	{
		fout << '0';
	}
	
	fin.close();
	fout.close();

	return 0;
}