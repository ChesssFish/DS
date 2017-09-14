/*-----------------------------------------------------------------------------
	文件名：work3.cpp
	作者：sis
	---------------------------------------------------------------------------
	此题目是在比赛图中找到一条有向哈密顿路
	首先证明比赛图中必有哈密顿路
	设G = <V, E>
	由数学归纳法，
	1.当n = 2 时，结论成立。
	2.假设n = k 时，结论成立，
	  则有哈密顿路 V1, V2 ... Vk
	  当 n = k + 1 时
	  1) <Vk, Vk+1> ∈ E，
		 则有哈密顿路 V1, V2 ... Vk, Vk+1
	  2) <Vk+1, V1> ∈ E,
	     则有哈密顿路 Vk+1, V1, V2 ... Vk
	  3) 若1，2均不满足， 则必有 Vm, 使得<Vm, Vk+1> ∈ E 且 <Vk+1, Vm+1> ∈ E
	     此时有哈密顿路 V1, V2 ... Vm, Vk+1, Vm+1 ... Vk
    ---------------------------------------------------------------------------
	于是算法显然：
	1.任取两个节点，加入哈密顿路
	2.遍历剩余节点，按规则1) - 3)加入哈密顿路
	算法时间复杂度为O(n^2)
-----------------------------------------------------------------------------*/
#include <iostream>
#include <fstream>
#include <Windows.h>
#define PAUSE system("pause")
using namespace std;

bool** map;  //用邻接矩阵存储比赛图
int n;       //参赛人数

class Node //用单链表存储哈密顿路
{
public:
	Node(int vertex = -1);
	~Node() {}
	int vertex;
	Node* pNext;
};
void loadfile(const char* filename);
//在des后插入src
void insert(Node* const &des, Node* const &src);
Node* FindHamiltonianPath();
void print(Node* plistHead);
int main()
{
	loadfile("sample.txt");
	Node* HamiltonianPath;
	HamiltonianPath = FindHamiltonianPath();
	print(HamiltonianPath);
	PAUSE;
	return 0;
}
Node::Node(int vertex)
{
	this->vertex = vertex;
	pNext = NULL;
}
void loadfile(const char* filename)
{
	//读入比赛数据
	ifstream is(filename);
	is >> n;
	map = new bool*[n];
	for (int i = 0; i < n; i++)
		map[i] = new bool[n];

	int x, y, state;
	int num = (n + 1)*n / 2;
	for (int i = 0; i < num; i++)
	{
		is >> x >> y >> state;
		map[x][y] = state;
		if (x != y)
			map[y][x] = !state;
	}
	is.close();
}
void insert(Node* const &des, Node* const &src)
{
	src->pNext = des->pNext;
	des->pNext = src;
}
Node* FindHamiltonianPath()
{
	Node* plistHead = new Node();
	Node* plistTail = plistHead;//方便比较Vk 与 Vk+1

	Node* newNode = new Node(0);
	//将0号选手加入哈密顿路
	insert(plistHead, newNode);
	plistTail = newNode;
	newNode = new Node(1);
	//将1号选手加入哈密顿路
	if (map[0][1])
	{
		insert(plistTail, newNode);
		plistTail = plistTail->pNext;
	}
	else
		insert(plistHead, newNode);
	
	//将余下的选手加入哈密顿路
	for (int i = 2; i < n; i++)
	{
		newNode = new Node(i);
		if (map[i][plistHead->pNext->vertex])
			insert(plistHead, newNode);
		else if (map[plistTail->vertex][i])
		{
			insert(plistTail, newNode);
			plistTail = plistTail->pNext;
		}
		else
		{
			Node* cur = plistHead ->pNext;
			while (cur != plistTail)
			{
				if (map[cur->vertex][i] && map[i][cur->pNext->vertex])
				{
					insert(cur, newNode);
					break;
				}
				cur = cur ->pNext;
			}
		}
	}
	return plistHead;
}
void print(Node* plistHead)
{
	Node* cur = plistHead->pNext;
	while (cur)
	{
		cout << cur->vertex;
		if (cur->pNext)
			cout << " -> ";
		cur = cur->pNext;
	}
	cout << endl;
}