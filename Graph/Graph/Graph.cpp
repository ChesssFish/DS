#include<iostream>
#include<fstream>
#define MAXN 20
using namespace std;
class Node//����
{
public:
	Node(int id = 0) :pNext(NULL) { this->id = id; }
	~Node() {};
	int id;
	Node* pNext;
};

ifstream is;//��ȡ�ļ�
int n = 0;//�������

Node G[MAXN];//�ڽӱ�
bool* vis;//���ʹ�����

Node** queue;//�����ö���
int head, tail;

Node** stack;//�ǵݹ������ö�ջ
int top;
//��ȡͼ������ȫ�ֱ�����ʼ��
void BuildGraph(void);
//��BuildGraph�е��ã���a�в���
void Ins(int a, int b);
//�ݹ�����
void DFS(Node* cur);
//�ǵݹ�����
void DFS_NR(Node* cur);
//����
void BFS(Node* cur);
//���ʽڵ㣬�˳�����Ϊ��ӡ�ڵ�
void Visit(Node* cur);
int main()
{
	is.open("data.txt");
	BuildGraph();
	is.close();
	int t = 0;
	cout << "�ǵݹ�����:" << endl;
	for (int i = 0; i < n; i++)
	{
		if (!vis[i])
		{
			t++;
			DFS_NR(&G[i]);
		}
	}
	cout << endl;
	memset(vis,false, n);

	cout << "�ݹ�����" << endl;
	for (int i = 0; i < n; i++)
	{
		if (!vis[i])
		{
			DFS(&G[i]);
		}
	}
	cout << endl;
	memset(vis, false, n);

	cout << "����" << endl;
	for (int i = 0; i < n; i++)
	{
		if (!vis[i])
		{
			BFS(&G[i]);
		}
	}
	cout << endl;
	if (t > 1)
	{
		cout << "��ͼ����ͨ" << endl;
	}
	else
	{
		cout << "��ͼ��ͨ" << endl;
	}
	return 0;
}
void BuildGraph(void)
{
	int a, b;
	for (int i = 0; i < MAXN; i++)
	{
		G[i].id = i;
	}
	while (true)
	{
		is >> a >> b;//a b֮���б�
		if (is.fail())
			break;
		if (a + 1 > n)
		{
			n = a + 1;
		}
		if (b + 1 > n)
		{
			n = b + 1;
		}
		Ins(a, b);
		Ins(b, a);
	}
	vis = new bool[n];
	memset(vis, false, n);
	queue = new Node*[n];
	stack = new Node*[n];
}
void Ins(int a, int b)
{
	Node* newNode = new Node(b);
	newNode->pNext = G[a].pNext;
	G[a].pNext = newNode;
}
void DFS(Node* cur)
{
	if (vis[cur->id] || cur == NULL)
	{
		return;
	}
	Visit(cur);
	vis[cur->id] = true;
	while (cur->pNext != NULL)
	{
		DFS(&G[cur->pNext->id]);
		cur = cur->pNext;
	}
}
void BFS(Node* cur)
{
	head = tail = 0;
	vis[cur->id] = true;
	queue[tail++] = cur;
	while (head < tail)
	{
		Visit(queue[head]);
		cur = queue[head] ->pNext;
		while (cur != NULL)
		{
			if (!vis[cur->id])
			{
				vis[cur->id] = true;
				queue[tail++] = &G[cur->id];
			}
			cur = cur->pNext;
		}
		head++;
	}
}
void DFS_NR(Node* cur)
{
	top = -1;
	stack[++top] = cur;
	Visit(cur);
	vis[stack[top]->id] = true;
	while (top != -1)
	{
		cur = stack[top]->pNext;
		while (!vis[cur->id])
		{
			stack[++top] = &G[cur->id];
			cur = stack[top]->pNext;
			Visit(stack[top]);
			vis[stack[top]->id] = true;
		}
		cur = stack[top];
		while (cur != NULL)
		{
			if (!vis[cur->id])
			{
				break;
			}
			cur = cur->pNext;
		}
		if (cur != NULL)
		{
			Visit(cur);
			vis[cur->id] = true;
			stack[top] = &G[cur->id];
		}
		else
		{
			top--;
		}
	}//��ѭ������
}
void Visit(Node* cur)
{
	cout << cur->id << " ";
}
