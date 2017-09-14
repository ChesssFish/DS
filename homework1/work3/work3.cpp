/*-----------------------------------------------------------------------------
	�ļ�����work3.cpp
	���ߣ�sis
	---------------------------------------------------------------------------
	����Ŀ���ڱ���ͼ���ҵ�һ��������ܶ�·
	����֤������ͼ�б��й��ܶ�·
	��G = <V, E>
	����ѧ���ɷ���
	1.��n = 2 ʱ�����۳�����
	2.����n = k ʱ�����۳�����
	  ���й��ܶ�· V1, V2 ... Vk
	  �� n = k + 1 ʱ
	  1) <Vk, Vk+1> �� E��
		 ���й��ܶ�· V1, V2 ... Vk, Vk+1
	  2) <Vk+1, V1> �� E,
	     ���й��ܶ�· Vk+1, V1, V2 ... Vk
	  3) ��1��2�������㣬 ����� Vm, ʹ��<Vm, Vk+1> �� E �� <Vk+1, Vm+1> �� E
	     ��ʱ�й��ܶ�· V1, V2 ... Vm, Vk+1, Vm+1 ... Vk
    ---------------------------------------------------------------------------
	�����㷨��Ȼ��
	1.��ȡ�����ڵ㣬������ܶ�·
	2.����ʣ��ڵ㣬������1) - 3)������ܶ�·
	�㷨ʱ�临�Ӷ�ΪO(n^2)
-----------------------------------------------------------------------------*/
#include <iostream>
#include <fstream>
#include <Windows.h>
#define PAUSE system("pause")
using namespace std;

bool** map;  //���ڽӾ���洢����ͼ
int n;       //��������

class Node //�õ�����洢���ܶ�·
{
public:
	Node(int vertex = -1);
	~Node() {}
	int vertex;
	Node* pNext;
};
void loadfile(const char* filename);
//��des�����src
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
	//�����������
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
	Node* plistTail = plistHead;//����Ƚ�Vk �� Vk+1

	Node* newNode = new Node(0);
	//��0��ѡ�ּ�����ܶ�·
	insert(plistHead, newNode);
	plistTail = newNode;
	newNode = new Node(1);
	//��1��ѡ�ּ�����ܶ�·
	if (map[0][1])
	{
		insert(plistTail, newNode);
		plistTail = plistTail->pNext;
	}
	else
		insert(plistHead, newNode);
	
	//�����µ�ѡ�ּ�����ܶ�·
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