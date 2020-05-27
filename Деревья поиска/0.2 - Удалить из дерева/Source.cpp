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

class b_tree {
private:
	key * head;

	static void postorder_for_del(key * vertex)
	{
		if (vertex != nullptr)
		{
			postorder_for_del(vertex->left);
			postorder_for_del(vertex->right);
			delete vertex;
		}
	}
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
	b_tree() {
		head = nullptr;
	}
	~b_tree()
	{
		postorder_for_del(head);
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
		*cur = new key{ x, nullptr, nullptr };
	}

	std::string NLR_left(key * vertex)
	{
		std::string tmp;
		if (vertex != nullptr)
		{
			tmp += std::to_string(vertex->node) + "\n" + NLR_left(vertex->left) + NLR_left(vertex->right);
		}
		return tmp;
	}

	key * get_head() const
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

		const int min = min_key(v->right)->node;
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

	b_tree tree;

	std::string tmp;
	std::getline(fin, tmp, '\n');
	const int del_vert = atoi(tmp.c_str());

	std::getline(fin, tmp, '\n');
	bool flag = false;
	while (std::getline(fin, tmp, '\n')) {
		int i = atoi(tmp.c_str());
		if (i == del_vert)
		{
			flag = true;
		}
		tree.insert(i);
	}
	if (flag)
	{
		tree.set_head(tree.delete_vertex(tree.get_head(), del_vert));
	}

	fout << tree.NLR_left(tree.get_head());

	fin.close();
	fout.close();
	return 0;
}