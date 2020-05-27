#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
constexpr auto MAX_SUM_LENGTH_DIAG = 150000; /* макс. диагональ = \sqrt{2} * 1000 < 1,5 * 1000, а всего их <= 100 */

struct point
{
	int x;
	int y;
};

point *poligon;
int length;

double distance(int i, int j)
{
	if (abs(i - j) % length <= 1 || abs(length - abs(i - j) % length) <= 1)
	{
		return 0;
	}

	return sqrt((poligon[i].x - poligon[j].x) * (poligon[i].x - poligon[j].x) + (poligon[i].y - poligon[j].y) * (poligon[i].y - poligon[j].y));
}

double search_min_sum_of_diag(int a, int b, double** sum_of_diag)
{
	double min = MAX_SUM_LENGTH_DIAG;

	for (int count = a + 1; count < b + (b < a ? length : 0); count++)
	{
		double tmp = (sum_of_diag[a][count % length] + sum_of_diag[count % length][b % length] +
			distance(a, count % length) + distance(count % length, b % length));
		if (min > tmp)
		{
			min = tmp;
		}
	}
	return (min == MAX_SUM_LENGTH_DIAG ? 0 : min);
}

int main()
{
	double ** sum_of_diag;
	
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

	fin >> length;
	poligon = new point[length];
	sum_of_diag = new double* [length];

	for (int i = 0; i < length; i++)
	{
		fin >> poligon[i].x;
		fin >> poligon[i].y;

		sum_of_diag[i] = new double[length] {0};
	}

	for (int i = 3; i < length - 1; i++)//число вершин подмногоугольника - 1. ¬озможно, стоит даже с 3 начинать?
	{
		for (int j = 0; j < length - 1; j++)//начальна€ вершина
		{
			sum_of_diag[j][(i + j) % length] = search_min_sum_of_diag(j, i + j, sum_of_diag);
		}
	}
	double a = (int)(search_min_sum_of_diag(0, length - 1, sum_of_diag) * 100) * 1. / 100;

	fout << std::setiosflags(std::ios_base::showpoint | std::ios_base::fixed) << std::setprecision(2) << a;
	fin.close();
	fout.close();
	return 0;
}