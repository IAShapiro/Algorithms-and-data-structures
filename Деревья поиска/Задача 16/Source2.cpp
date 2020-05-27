#pragma comment(linker, "/STACK:33554432")
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>

struct key {
	int node;
	key* left;
	key* right;
	long mark1;
	long mark2;
	long mark3;
	long mark4;
};

std::vector<key *> vert_max_mark;
long max_mark = 0;

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
		*cur = new key{ x, nullptr, nullptr, 0, 1, 0, 0 };
	}

	std::string NLRLeft(key * vertex)
	{
		std::string tmp;
		if (vertex != nullptr)
		{
			tmp += std::to_string(vertex->node) + " " + std::to_string(vertex->mark4 + vertex->mark3) + "\n" + NLRLeft(vertex->left) + NLRLeft(vertex->right);
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
};

void setMarks(key * head)
{
	if (head != nullptr)
	{
		setMarks(head->left);
		setMarks(head->right);

		long sumM1 = 0;
		if (head->left == nullptr && head->right == nullptr) { head->mark1 = 0; head->mark2 = 1; }
		if (head->left != nullptr && head->right == nullptr)
		{
			sumM1 = head->left->mark1 + 1;
			head->mark1 = 1 + head->left->mark1;
			head->mark2 = head->left->mark2;
		}
		else if (head->left == nullptr && head->right != nullptr)
		{
			sumM1 = head->right->mark1 + 1;
			head->mark1 = 1 + head->right->mark1;
			head->mark2 = head->right->mark2;
		}
		else if (head->left != nullptr && head->right != nullptr)
		{
			sumM1 = head->left->mark1 + head->right->mark1 + 2;

			if (head->right->mark1 == head->left->mark1)
			{
				head->mark1 = 1 + head->right->mark1;
				head->mark2 = head->right->mark2 + head->left->mark2;
			}
			else if (head->right->mark1 > head->left->mark1)
			{
				head->mark1 = 1 + head->right->mark1;
				head->mark2 = head->right->mark2;
			}
			else /*if (head->right->mark1 < head->left->mark1)*/
			{
				head->mark1 = 1 + head->left->mark1;
				head->mark2 = head->left->mark2;
			}
		}

		if (sumM1 == max_mark)
		{
			vert_max_mark.push_back(head);
		}
		else if (sumM1 > max_mark)
		{
			max_mark = sumM1;
			vert_max_mark.clear();
			vert_max_mark.push_back(head);
		}
	}
}

void calc_count_of_way(key * head)
{
	if (head != nullptr)
	{
		if (head->left != nullptr && head->right == nullptr)
		{
			head->left->mark4 = head->mark3 + head->mark4;
		}
		else if (head->left == nullptr && head->right != nullptr)
		{
			head->right->mark4 = head->mark3 + head->mark4;
		}
		else if (head->left != nullptr && head->right != nullptr)
		{
			if (head->left->mark1 < head->right->mark1)
			{
				head->right->mark4 = head->mark3 + head->mark4;
				head->left->mark4 = head->mark3;
			}
			else if (head->left->mark1 > head->right->mark1)
			{
				head->left->mark4 = head->mark3 + head->mark4;
				head->right->mark4 = head->mark3;
			}
			else
			{
				head->left->mark4 = head->mark3 + head->mark4  / (head->left->mark2 + head->right->mark2) * (head->left->mark2);		head->right->mark4 = head->mark3 + head->mark4 / (head->left->mark2 + head->right->mark2) * (head->right->mark2); }
		}
		calc_count_of_way(head->left);
		calc_count_of_way(head->right);
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

	setMarks(tree.get_head());

	for (auto& vert : vert_max_mark)
	{
		vert->mark3 = (vert->left != nullptr ? vert->left->mark2 : 1) * (vert->right != nullptr ? vert->right->mark2 : 1);
	}

	calc_count_of_way(tree.get_head());

	fout << tree.NLRLeft(tree.get_head());

	fin.close();
	fout.close();
	return 0;
}