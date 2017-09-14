#include "Btree.h"
#include <iostream>
#include <fstream>
class Data
{
public:
	Data(char id = 0) :m_id(id) {}
	~Data() {}
	Data& operator=(Data& d);
	//输出Data的内容
	void show(void);
	char m_id;
};
char* PreOrder;
char* InOrder;
Node<Data>** queue;
int head, tail;
Node<Data>** stack;
int top;
Node<Data>* root;
//初始化全局变量
void Init();
//中序序列中,若ch_pre在ch_root之前,则返回-1,否则返回 1
int check(const char ch_pre, const char ch_root);
//递归建树
//cur:当前节点
//start:树在中序序列中的起始位置
//end:树在中序序列中的结束位置
void BuildTree_R(Node<Data>* &cur, int start, int end);
//非递归建树
void BuildTree_NR(void);
//访问节点
void visit(Node<Data>* cur);
//递归先序遍历
void Pre_R(Node<Data>* cur);
//递归中序遍历
void In_R(Node<Data>* cur);
//递归后序遍历
void Post_R(Node<Data>* cur);
//层序遍历
void BFS(Node<Data>* cur);
//非递归先序遍历
void Pre_NR(Node<Data>* cur);
//非递归中序遍历
void In_NR(Node<Data>* cur);
//非递归后序遍历
void Post_NR(Node<Data>* cur);
//------找公共祖先时使用------
char path_a[MAXN] = { 0 };
int cnt_a = 0;
char path_b[MAXN] = { 0 };
int cnt_b = 0;
bool finda = false;
bool findb = false;
//----------------------------
//递归找从根到a, b的两条路
void FindPath(Node<Data>* cur, const char a, const char b);
//找两条路中最后一个相同节点,即为公共祖先
char FindCommonAncestor(const char a, const char b);
using namespace std;

int main()
{
	Init();
	ifstream is("in.txt");
	is >> InOrder;
	is >> PreOrder;
	is.close();

	BuildTree_NR();
	//BuildTree_R(root, 0, strlen(PreOrder) - 1);

	cout << "pre_r: ";
	Pre_R(root);
	cout << endl << "in_r: ";
	In_R(root);
	cout << endl << "post_r: ";
	Post_R(root);
	cout << endl << "level: ";
	BFS(root);
	cout << endl << "pre_nr: ";
 	Pre_NR(root);
	cout << endl << "in_nr: ";
	In_NR(root);
	cout << endl << "post_nr: ";
	Post_NR(root);
	cout << endl;

	char a, b;
	while (true) {
		cout << "请输入求取公共祖先的两个节点: " << endl;
		cin >> a >> b;
		if (a == 0 && b == 0)break;
		cout << "公共祖先为: " << FindCommonAncestor(a, b) << endl << endl;
	}
	return 0;
}
template<class T>
Node<T>::Node() :mp_lc(NULL), mp_rc(NULL) {}
Data& Data::operator=(Data& d)
{
	m_id = d.m_id;
	return *this;
}
void Data::show(void)
{
	cout << m_id << " ";
}
void Init()
{
	PreOrder = new char[MAXN];
	InOrder = new char[MAXN];
	queue = new Node<Data>*[MAXN];
	head = tail = 0;
	stack = new Node<Data>*[MAXN];
	top = -1;
	root = NULL;
}
int check(const char ch_pre, const char ch_root)
{
	int cur = 0;
	while (InOrder[cur] != '\0')
	{
		if (InOrder[cur] == ch_pre)
		{
			return -1;
		}
		if (InOrder[cur] == ch_root)
		{
			return 1;
		}
		cur++;
	}
	return 0;//此语句不会执行
}
void BuildTree_NR(void)
{
	int cnt = 0;
	int tag = 0;
	Node<Data>* pre = root;
	Node<Data>* cur = root;
	while (PreOrder[cnt] != '\0')
	{
		tag = 0;
		pre = root;
		cur = root;
		while (cur != NULL)
		{
			pre = cur;
			tag = check(PreOrder[cnt], cur->mp_data.m_id);
			if (tag == -1)
			{
				cur = cur->mp_lc;
			}
			else
			{
				cur = cur->mp_rc;
			}
		}
		cur = new Node<Data>;
		Data tmp(PreOrder[cnt]);
		cur->mp_data = tmp;
		if (tag == 0)
		{
			root = cur;
		}
		else if (tag == -1)
		{
			pre->mp_lc = cur;
		}
		else
		{
			pre->mp_rc = cur;
		}
		cnt++;
	}//end of while
}
int findkey(const int cnt, const int start, const int end)
{
	int i = start;
	while (InOrder[i] != '\0' && i <= end)
	{
		if (InOrder[i] == PreOrder[cnt])
			return i;
		i++;
	}
	return -1;//此语句不会执行
}
void BuildTree_R(Node<Data>* &cur, int start, int end)
{
	if (start > end)return;
	static int cnt = 0;
	int key;
	if (start == end)
		key = start;
	else
		key = findkey(cnt, start, end);
	cur = new Node<Data>;
	Data tmp(PreOrder[cnt]);
	cur->mp_data = tmp;
	cnt++;
	BuildTree_R(cur->mp_lc, start, key - 1);
	BuildTree_R(cur->mp_rc, key + 1, end);
}
void visit(Node<Data>* cur)
{
	cur->mp_data.show();
}
void Pre_R(Node<Data>* cur)
{
	if (cur == NULL)
	{
		return;
	}
	visit(cur);
	Pre_R(cur->mp_lc);
	Pre_R(cur->mp_rc);
}
void In_R(Node<Data>* cur)
{
	if (cur == NULL)
	{
		return;
	}
	In_R(cur->mp_lc);
	visit(cur);
	In_R(cur->mp_rc);
}
void Post_R(Node<Data>* cur)
{
	if (cur == NULL)
	{
		return;
	}
	Post_R(cur->mp_lc);
	Post_R(cur->mp_rc);
	visit(cur);
}
void BFS(Node<Data>* cur)
{
	queue[head] = cur;
	while (head <= tail)
	{
		visit(queue[head]);
		if (queue[head]->mp_lc != NULL)
			queue[++tail] = queue[head]->mp_lc;
		if (queue[head]->mp_rc != NULL)
			queue[++tail] = queue[head]->mp_rc;
		head++;
	}
	head = tail = 0;
}
void Pre_NR(Node<Data>* cur)
{
	while (true)
	{
		visit(cur);
		if (cur->mp_rc != NULL)
			stack[++top] = cur->mp_rc;
		if (cur->mp_lc != NULL)
			cur = cur->mp_lc;
		else if (top != -1)
			cur = stack[top--];
		else
			break;
	}
	top = -1;
}
void In_NR(Node<Data>* cur)
{
	while (cur != NULL || top != -1) 
	{
		while(cur != NULL)
		{
			stack[++top] = cur;
			cur = cur->mp_lc;
		}
		if (top != -1)
		{
			cur = stack[top--];
			visit(cur);
			cur = cur->mp_rc;
		}
	}
	top = -1;
}
void Post_NR(Node<Data>* cur)
{
	Node<Data>* pr;
	while (cur != NULL || top != -1)
	{
		while (cur != NULL)
		{
			stack[++top] = cur;
			pr = cur->mp_rc;//右子树
			cur = cur->mp_lc;//左子树
			if (cur == NULL)//左子树为空则入栈右子树,直到左右子树均为空
				cur = pr;
		}
		cur = stack[top--];
		visit(cur);
		if (top != -1 && stack[top]->mp_lc == cur)//右子树尚未遍历
			cur = stack[top]->mp_rc;
		else
			cur = NULL;
	}
}
void FindPath(Node<Data>* cur, const char a, const char b)
{
	if (cur == NULL || (finda && findb))
		return ;
	if(!finda)
		path_a[cnt_a++] = cur->mp_data.m_id;
	if(!findb)
		path_b[cnt_b++] = cur->mp_data.m_id;
	if (cur->mp_data.m_id == a)
		finda = true;
	if (cur->mp_data.m_id == b)
		findb = true;
	FindPath(cur->mp_lc, a, b);
	FindPath(cur->mp_rc, a, b);
	if (!finda)cnt_a--;
	if (!findb)cnt_b--;
}
char FindCommonAncestor(const char a, const char b)
{
	//----------------初始化---------------
	cnt_a = 0;
	cnt_b = 0;
	finda = false;
	findb = false;
	memset(path_a, 0, MAXN);
	memset(path_b, 0, MAXN);
	//--------------------------------------
	FindPath(root, a, b);
	cnt_a = cnt_a > cnt_b ? cnt_a : cnt_b;
	char ans;
	//寻找路径中最后一个相同的节点
	for (int i = 0; i < cnt_a; i++)
		if (path_a[i] == path_b[i])
			ans = path_a[i];
		else break;
	return ans;
}