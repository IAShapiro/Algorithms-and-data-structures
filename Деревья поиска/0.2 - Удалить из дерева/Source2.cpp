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

	key * min_key(key * v) {
		if (v->left != nullptr)
		{
			return min_key(v->left);
		}
		else
		{
			return v;
		}
	}
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

	key* delete_vertex(key * v, int x) {
		if (v == nullptr)
		{
			return nullptr;
		}

		if (x < v->node)
		{
			v->left = delete_vertex(v->left, x);
			return v;
		}
		if (x > v->node)
		{
			v->right = delete_vertex(v->right, x);
			return v;
		}
		if (v->left == nullptr)
		{
			return v->right;
		}
		if (v->right == nullptr)
		{
			return v->left;
		}
 		
		int min = min_key(v->right)->node;
		v->node = min;
		v->right = delete_vertex(v->right, min);
		return v;
	}

	void set_head(key * v)
	{
		head = v;
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
	std::getline(fin, tmp, '\n');
	int del_vert = atoi(tmp.c_str());
	
	std::getline(fin, tmp, '\n');
	bool flag = false;
	while (std::getline(fin, tmp, '\n')) {
		int i = atoi(tmp.c_str());
		if (i == del_vert)
		{
			flag = true;
		}
		T.insert(i);
	}
	if (flag)
	{
		T.set_head(T.delete_vertex(T.getHead(), del_vert));
	}

	fout << T.NLRLeft(T.getHead());

	fin.close();
	fout.close();
	return 0;
}