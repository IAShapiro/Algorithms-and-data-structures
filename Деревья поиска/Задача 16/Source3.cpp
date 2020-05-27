#pragma comment(linker, "/STACK:33554432")
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
//и все же надо ВСЕ пути в один вектор собрать, и только потом сверять (?). 
//Или нет? right и left содержат полноценные пути теперь, а не их части
//А теперь снова части, собирать не имеет смысла

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
		*cur = new key{x, nullptr, nullptr, 0, 0, 0};
	}

	std::string NLRLeft(key * vertex)
	{
		std::string tmp = "";
		if (vertex != nullptr)
		{
			tmp += std::to_string(vertex->node) + " " + std::to_string(vertex->count_way) + "\n" + NLRLeft(vertex->left) + NLRLeft(vertex->right);
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
		vertex->mark1 = std::max(left, right);

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

std::vector<std::vector<key *>> support_COW(std::vector<key *> vect, key * subhead)
{
	key * vertex = vect.back();

	if (vertex->left != nullptr && vertex->right != nullptr)
	{
		if (vertex->left->mark1 == vertex->right->mark1) {
			std::vector<key *> copy_vect = vect;
			copy_vect.push_back(vertex->left);
			std::vector<std::vector<key *>> tmp1 = support_COW(copy_vect, subhead);
			vect.push_back(vertex->right);
			std::vector<std::vector<key *>> tmp2 = support_COW(vect, subhead);

			tmp1.insert(tmp1.end(), tmp2.begin(), tmp2.end());

			return tmp1;
		}
		if (vertex->left->mark1 > vertex->right->mark1)
		{
			vect.push_back(vertex->left);
			return support_COW(vect, subhead);
		}
		if (vertex->left->mark1 < vertex->right->mark1)
		{
			vect.push_back(vertex->right);
			return support_COW(vect, subhead);
		}
	}
	else if (vertex->left == nullptr && vertex->right == nullptr)
	{
		std::vector<std::vector<key *>> tmp1;
		tmp1.push_back(vect);
		return tmp1;
	}
	else if (vertex->left != nullptr) // && vertex->right == nullptr
	{
		vect.push_back(vertex->left);
		return support_COW(vect, subhead);
	}
	else //vertex->left == nullptr && vertex->right != nullptr
	{
		vect.push_back(vertex->right);
		return support_COW(vect, subhead);
	}
}

void count_of_way(key * vertex)
{
	std::vector<std::vector<key *>> left, right;
	std::vector<key *> vect1;
	vect1.push_back(vertex);

	if (vertex->left != nullptr)
	{
		vect1.push_back(vertex->left);
		left = support_COW(vect1, vertex);
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
		right = support_COW(vect1, vertex);
	}
	else
	{
		right.push_back(vect1);
	}

	for (auto i = 0; i < left.size(); i++)
	{
		for (auto j = 0; j < left[i].size(); j++)
		{
			left[i][j]->count_way += right.size();
		}
	}

	for (auto i = 0; i < right.size(); i++)
	{
		for (auto j = 1; j < right[i].size(); j++)
		{
			right[i][j]->count_way += left.size();
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

	BTree T;

	std::string tmp;
	std::getline(fin, tmp, '\n');
	int del_vert = atoi(tmp.c_str());
	T.insert(del_vert);
	
	while (std::getline(fin, tmp, '\n')) {
		T.insert(atoi(tmp.c_str()));
	}

	T.set_head(T.delete_vertex(T.getHead(), del_vert));

	T.set_mark1(T.getHead());
	T.set_mark2(T.getHead());

	for (auto i = 0; i < vert_max_mark2.size(); i++)
	{
		count_of_way(vert_max_mark2[i]);
	}

	fout << T.NLRLeft(T.getHead());

	fin.close();
	fout.close();
	return 0;
}