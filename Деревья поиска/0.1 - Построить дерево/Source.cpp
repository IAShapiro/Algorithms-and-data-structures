#pragma comment(linker, "/STACK:16777216")
#include <iostream>
#include <fstream>
#include <set>
#include <sstream>

struct key {
	int node;
	key* left;
	key* right;
};

class BTree {
private:
	key * head;
public:
	BTree() {
		head = nullptr;
	}
	void insert(int x) {
		key** cur = &head;
		while (*cur) {
			key& v = **cur;
			if (x < v.node) {
				cur = &v.left;
			}
			else if (x > v.node) {
				cur = &v.right;
			}
			else {
				return;
			}
		}
		*cur = new key{x, nullptr, nullptr};
	}

	std::string NLRLeft(key * vertex)
	{
		std::string tmp = "";
		if (vertex != nullptr)
		{
			tmp += std::to_string(vertex->node) + "\n" + NLRLeft(vertex->left) + NLRLeft(vertex->right);
		}
		return tmp;
	}

	key * getHead()
	{
		return head;
	}
};

int main() {
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

	BTree T;

	std::string tmp;

	while (std::getline(fin, tmp, '\n')) {
		T.insert(atoi(tmp.c_str()));
	}

	fout << T.NLRLeft(T.getHead());

	fin.close();
	fout.close();
	return 0;
}