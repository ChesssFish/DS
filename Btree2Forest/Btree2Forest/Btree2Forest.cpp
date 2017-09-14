#include"Btree2Forest.h"
vector<int> pre;
vector<int> in;
int Btree2Forest::_findkey(int cnt, int start, int end)
{
	for (int i = start; i <= end; i++)
	{
		if (in[i] == pre[cnt])
			return i;
	}
	return -1;
}
void Btree2Forest::ToBtree(void)
{
	//将每一棵树变为二叉树
	for (unsigned i = 0; i < roots.size(); i++)
	{
		_tobtree(roots[i]);
	}
	//将所有树连起来
	for (unsigned i = roots.size() - 1; i >= 1; i--)
	{
		roots[i - 1]->next[1] = roots[i];
		roots.pop_back();
	}
	state = Btree;
}
void Btree2Forest::ToForest(void)
{
	Node* cur = roots[0];
	int cnt = 0;
	while (cur->next[1] != NULL)
	{
		roots.push_back(cur->next[1]);
		cur->next[1] = NULL;
		cur = *(roots.crbegin());
	}
	for (size_t i = 0; i < roots.size(); i++)
	{
		_totree(roots[i]);
	}
	state = Forest;
}
void Btree2Forest::_link(Node* cur)
{
	Node* rc = cur->next[0];
	while (rc != NULL && rc->next[1] != NULL)
	{
		cur->next.push_back(rc->next[1]);
		rc->next[1] = NULL;
		rc = *(cur->next.crbegin());
	}
}
void Btree2Forest::_totree(Node* cur)
{
	if (cur == NULL)
	{
		return;
	}
	_link(cur);
	for (size_t i = 0; i < cur->next.size();i++)
	{
		_totree(cur->next[i]);
	}
}
void Btree2Forest::_delete(Node* cur)
{
	for (int i = cur->next.size() - 1; i >= 2; i--)
	{
		cur->next[i == 2 ? 0 : i - 1]->next[1] = cur->next[i];
		cur->next.pop_back();
	}
}
void Btree2Forest::_tobtree(Node* cur)
{
	if (cur == NULL)
	{
		return;
	}
	for (size_t i = 0; i < cur->next.size(); i++)
	{
		_tobtree(cur->next[i]);
	}
	_delete(cur);
}
void Btree2Forest::BuildBtree(string file)
{
	ifstream is;
	is.open(file);
	int n, tmp;
	is >> n;
	for (int i = 0; i < n; i++)
	{
		is >> tmp;
		pre.push_back(tmp);
	}
	for (int i = 0; i < n; i++)
	{
		is >> tmp;
		in.push_back(tmp);
	}
	_buildtree(roots[0], 0, n - 1);
}
void Btree2Forest::_buildtree(Node* &cur, int start, int end)
{
	if (start > end)return;
	static int cnt = 0;
	int key;
	if (start == end)
		key = start;
	else
		key = _findkey(cnt, start, end);
	cur = new Node;
	cur->data = pre[cnt];
	cnt++;
	cur->next.push_back(NULL);
	_buildtree(cur->next[0], start, key - 1);
	cur->next.push_back(NULL);
	_buildtree(cur->next[1], key + 1, end);
}


Btree2Forest* t;
int main()
{
	t = new Btree2Forest;
	t->BuildBtree("in.txt");
	t->ToForest();
	t->ToBtree();
	return 0;
}