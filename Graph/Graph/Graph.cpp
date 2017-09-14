#include<iostream>
#include<fstream>
#define MAXN 20
using namespace std;
class Node//顶点
{
public:
	Node(int id = 0) :pNext(NULL) { this->id = id; }
	~Node() {};
	int id;
	Node* pNext;
};

ifstream is;//读取文件
int n = 0;//顶点个数

Node G[MAXN];//邻接表
bool* vis;//访问过数组

Node** queue;//广搜用队列
int head, tail;

Node** stack;//非递归深搜用堆栈
int top;
//读取图并进行全局变量初始化
void BuildGraph(void);
//在BuildGraph中调用，在a中插入
void Ins(int a, int b);
//递归深搜
void DFS(Node* cur);
//非递归深搜
void DFS_NR(Node* cur);
//广搜
void BFS(Node* cur);
//访问节点，此程序中为打印节点
void Visit(Node* cur);
int main()
{
	is.open("data.txt");
	BuildGraph();
	is.close();
	int t = 0;
	cout << "非递归深搜:" << endl;
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

	cout << "递归深搜" << endl;
	for (int i = 0; i < n; i++)
	{
		if (!vis[i])
		{
			DFS(&G[i]);
		}
	}
	cout << endl;
	memset(vis, false, n);

	cout << "广搜" << endl;
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
		cout << "此图不连通" << endl;
	}
	else
	{
		cout << "此图连通" << endl;
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
		is >> a >> b;//a b之间有边
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
	}//主循环结束
}
void Visit(Node* cur)
{
	cout << cur->id << " ";
}
