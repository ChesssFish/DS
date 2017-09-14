#include "Btree.h"
#include <iostream>
#include <fstream>
class Data
{
public:
	Data(char id = 0) :m_id(id) {}
	~Data() {}
	Data& operator=(Data& d);
	//���Data������
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
//��ʼ��ȫ�ֱ���
void Init();
//����������,��ch_pre��ch_root֮ǰ,�򷵻�-1,���򷵻� 1
int check(const char ch_pre, const char ch_root);
//�ݹ齨��
//cur:��ǰ�ڵ�
//start:�������������е���ʼλ��
//end:�������������еĽ���λ��
void BuildTree_R(Node<Data>* &cur, int start, int end);
//�ǵݹ齨��
void BuildTree_NR(void);
//���ʽڵ�
void visit(Node<Data>* cur);
//�ݹ��������
void Pre_R(Node<Data>* cur);
//�ݹ��������
void In_R(Node<Data>* cur);
//�ݹ�������
void Post_R(Node<Data>* cur);
//�������
void BFS(Node<Data>* cur);
//�ǵݹ��������
void Pre_NR(Node<Data>* cur);
//�ǵݹ��������
void In_NR(Node<Data>* cur);
//�ǵݹ�������
void Post_NR(Node<Data>* cur);
//------�ҹ�������ʱʹ��------
char path_a[MAXN] = { 0 };
int cnt_a = 0;
char path_b[MAXN] = { 0 };
int cnt_b = 0;
bool finda = false;
bool findb = false;
//----------------------------
//�ݹ��ҴӸ���a, b������·
void FindPath(Node<Data>* cur, const char a, const char b);
//������·�����һ����ͬ�ڵ�,��Ϊ��������
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
		cout << "��������ȡ�������ȵ������ڵ�: " << endl;
		cin >> a >> b;
		if (a == 0 && b == 0)break;
		cout << "��������Ϊ: " << FindCommonAncestor(a, b) << endl << endl;
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
	return 0;//����䲻��ִ��
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
	return -1;//����䲻��ִ��
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
			pr = cur->mp_rc;//������
			cur = cur->mp_lc;//������
			if (cur == NULL)//������Ϊ������ջ������,ֱ������������Ϊ��
				cur = pr;
		}
		cur = stack[top--];
		visit(cur);
		if (top != -1 && stack[top]->mp_lc == cur)//��������δ����
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
	//----------------��ʼ��---------------
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
	//Ѱ��·�������һ����ͬ�Ľڵ�
	for (int i = 0; i < cnt_a; i++)
		if (path_a[i] == path_b[i])
			ans = path_a[i];
		else break;
	return ans;
}