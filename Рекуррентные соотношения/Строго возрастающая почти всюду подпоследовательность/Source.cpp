#pragma comment(linker, "/STACK:33554432")
#include <string>
#include <fstream>
#include <vector>
#include <list>
#include <queue>

std::vector<int> p1, p2, end1, end2, max1, max2;
int n;

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

	p1.resize(n);
	p2.resize(n);
	end1.resize(n + 1);
	end2.resize(n + 1);
	max1.push_back(0);
	max2.push_back(0);

	end1[0] = end2[0] = INT_MIN;
	for (int i = 0; i < n; i++)
	{
		fin >> p1[i];
		p2[n - i - 1] = - p1[i];
		end1[i + 1] = end2[i + 1] = INT_MAX;
	}

	for (int i = 0; i < n; i++) {
		bool flag = false;
		int j = int(std::upper_bound(end1.begin(), end1.end(), p1[i]) - end1.begin());
		if (end1[j - 1] < p1[i] && p1[i] < end1[j]) {
			end1[j] = p1[i];
			flag = true;
		}
		if (flag == false)
		{
			max1.push_back(max1[max1.size() - 1]);
		}
		else
		{
			if (j <= max1[max1.size() - 1])
			{
				max1.push_back(max1[max1.size() - 1]);
			}
			else
			{
				max1.push_back(max1[max1.size() - 1] + 1);
			}
		}
		
		flag = false;
		j = int(std::upper_bound(end2.begin(), end2.end(), p2[i]) - end2.begin());
		if (end2[j - 1] < p2[i] && p2[i] < end2[j]) {
			end2[j] = p2[i];
			flag = true;
		}
		if (flag == false)
		{
			max2.push_back(max2[max2.size() - 1]);
		}
		else
		{
			if (j <= max2[max2.size() - 1])
			{
				max2.push_back(max2[max2.size() - 1]);
			}
			else
			{
				max2.push_back(max2[max2.size() - 1] + 1);
			}
		}
	}

	int maxtmp = INT_MIN;
	for (int i = 0; i < n + 1; i++)
	{
		if (max1[i] + max2[n - i] > maxtmp)
		{
			maxtmp = max1[i] + max2[n - i];
		}
	}

	fout << maxtmp;
	
	fin.close();
	fout.close();

	return 0;
}