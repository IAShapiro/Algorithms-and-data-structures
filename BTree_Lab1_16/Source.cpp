#pragma comment(linker, "/STACK:33554432")
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>

struct key {
	int node;
	key* left;
	key* right;
	int mark1;
	int mark2;
	int count_way;
};

std::vector<key *> vert_max_mark2;
int max_mark2 = 0;

class b_tree {
private:
	key * head;

	key * min_key(key * v) {
		if (v->left != nullptr)
		{
			return min_key(v->left);
		}
		return v;
	}

	void postorder_for_del(key * vertex)
	{
		if (vertex != nullptr)
		{
			postorder_for_del(vertex->left);
			postorder_for_del(vertex->right);
			delete vertex;
		}
	}
public:
	b_tree() {
		head = nullptr;
	}
	~b_tree()
	{
		postorder_for_del(get_head());
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
		*cur = new key{x, nullptr, nullptr, 0, 0, 0};
	}

	std::string NLRLeft(key * vertex)
	{
		std::string tmp;
		if (vertex != nullptr)
		{
			tmp += std::to_string(vertex->node) + " " + std::to_string(vertex->count_way) + "\n" + NLRLeft(vertex->left) + NLRLeft(vertex->right);
		}
		return tmp;
	}

	key * get_head()
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

	int set_mark1(key * vertex)
	{
		int left = 0, right = 0;
		if (vertex->left != nullptr)
		{
			left = 1 + set_mark1(vertex->left);
		}
		if (vertex->right != nullptr)
		{
			right = 1 + set_mark1(vertex->right);
		}
		vertex->mark1 = (left > right ? left : right);

		return vertex->mark1;
	}

	void set_mark2(key * vertex)
	{
		vertex->mark2 = (vertex->left == nullptr ? 0 : 1 + vertex->left->mark1) + (vertex->right == nullptr ? 0 : 1 + vertex->right->mark1);
		if (vertex->mark2 == max_mark2)
		{
			vert_max_mark2.push_back(vertex);
		}
		else if (vertex->mark2 > max_mark2)
		{
			max_mark2 = vertex->mark2;
			vert_max_mark2.clear();
			vert_max_mark2.push_back(vertex);
		}
		if (vertex->left != nullptr)
		{
			set_mark2(vertex->left);
		}
		if (vertex->right != nullptr)
		{
			set_mark2(vertex->right);
		}
	}
};

std::vector<std::vector<key *>> support_COW(std::vector<key *> vect)
{
	key * vertex = vect.back();

	if (vertex->left != nullptr && vertex->right != nullptr)
	{
		if (vertex->left->mark1 == vertex->right->mark1) {
			std::vector<key *> copy_vect = vect;
			copy_vect.push_back(vertex->left);
			std::vector<std::vector<key *>> tmp1 = support_COW(copy_vect);
			vect.push_back(vertex->right);
			std::vector<std::vector<key *>> tmp2 = support_COW(vect);

			tmp1.insert(tmp1.end(), tmp2.begin(), tmp2.end());

			return tmp1;
		}
		if (vertex->left->mark1 > vertex->right->mark1)
		{
			vect.push_back(vertex->left);
			return support_COW(vect);
		}
		// (vertex->left->mark1 < vertex->right->mark1)
		vect.push_back(vertex->right);
		return support_COW(vect);
	}
	if (vertex->left == nullptr && vertex->right == nullptr)
	{
		std::vector<std::vector<key *>> tmp1;
		tmp1.push_back(vect);
		return tmp1;
	}
	if (vertex->left != nullptr) // && vertex->right == nullptr
	{
		vect.push_back(vertex->left);
		return support_COW(vect);
	}
	//vertex->left == nullptr && vertex->right != nullptr
	vect.push_back(vertex->right);
	return support_COW(vect);
}

void count_of_way(key * vertex)
{
	std::vector<std::vector<key *>> left, right;
	std::vector<key *> vect1;
	vect1.push_back(vertex);

	if (vertex->left != nullptr)
	{
		vect1.push_back(vertex->left);
		left = support_COW(vect1);
	}
	else
	{
		left.push_back(vect1);
	}
	vect1.clear();
	vect1.push_back(vertex);
	if (vertex->right != nullptr)
	{
		vect1.push_back(vertex->right);
		right = support_COW(vect1);
	}
	else
	{
		right.push_back(vect1);
	}

	for (auto& i : left)
	{
		for (auto& j : i)
		{
			j->count_way += right.size();
		}
	}

	for (auto& i : right)
	{
		for (auto j = 1; j < static_cast<int>(i.size()); j++)
		{
			i[j]->count_way += left.size();
		}
	}
}

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
	
	while (std::getline(fin, tmp, '\n')) {
		tree.insert(atoi(tmp.c_str()));
	}

	tree.set_head(tree.delete_vertex(tree.get_head(), tree.get_head()->node));

	tree.set_mark1(tree.get_head());
	tree.set_mark2(tree.get_head());

	for (auto& i : vert_max_mark2)
	{
		count_of_way(i);
	}

	fout << tree.NLRLeft(tree.get_head());

	fin.close();
	fout.close();
	return 0;
}