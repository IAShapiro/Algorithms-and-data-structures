#include <string>
#include <fstream>

int tmp;
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

	unsigned long long int k;
	fin >> k;
	int counter = 0;
	while (k != 0)
	{
		if (k % 2 == 1)
		{
			fout << counter << '\n';
		}

		counter++;
		k /= 2;
	}

	fin.close();
	fout.close();

	return 0;
}