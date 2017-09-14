#include"ThTree.h"
#include<vector>
vector<char> pre;
vector<char> in;
ThTree::ThTree()
{
	root = NULL;
}
ThTree::~ThTree()
{
	delete root;
}
//建立二叉树
void ThTree::BuildTree(string file)
{
	ifstream is;
	is.open(file);
	int n;
	char tmp;
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
	_buildtree(root, 0, n - 1);
}
void ThTree::_buildtree(Node* &cur, int start, int end)
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
	_buildtree(cur->lc, start, key - 1);
	if (start <= key - 1)
	{
		cur->ltag = true;
	}
	_buildtree(cur->rc, key + 1, end);
	if (key + 1 <= end)
	{
		cur->rtag = true;
	}
}
int ThTree::_findkey(int cnt, int start, int end)
{
	for (int i = start; i <= end; i++)
	{
		if (in[i] == pre[cnt])
			return i;
	}
	return -1;
}

//先序线索化
void ThTree::PreOrderThreading()
{
	_prethreading(root);
}
void ThTree::_prethreading(Node* cur)
{
	if (cur == NULL)return;
	if (_pre!= NULL && !_pre->rtag)
	{
		_pre->rc = cur;
	}
	if (!cur->ltag)
	{
		cur->lc = _pre;
	}
	_pre = cur;
	if(cur->ltag)
		_prethreading(cur->lc);
	if(cur->rtag)
		_prethreading(cur->rc);
}

ThTree* t;
int main()
{
	t = new ThTree;
	t->BuildTree("in.txt");
	t->PreOrderThreading();
	return 0;
}