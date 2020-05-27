#include <iostream>
#include <fstream>
#include <set>
#include <sstream>

int main() {
	
	std::set<int> S;

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

	std::string tmp;

	while (std::getline(fin, tmp, '\n')) {
		S.insert(atoi(tmp.c_str()));
	}
	long long counter = 0;

	for (auto i = S.begin(); i != S.end(); i++) {
		counter += atoi(std::to_string(*i).c_str());
	}

	fout << counter;
	
	fin.close();
	fout.close();
	return 0;
}