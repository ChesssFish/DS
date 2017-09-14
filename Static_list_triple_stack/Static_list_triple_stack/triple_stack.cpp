#include "valid.h"
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#define MAXN 10
class Node
{
public:
	Node(int x = 0) :data(x), next(0) {};
	~Node() {};
	int data;
	int next;
}*tri_stack;
int aval;
using namespace std;
//��ջ��ջ��(��ͷ)�ֱ�Ϊtri_stack[0], tri_stack[1], tri_stack[2]
//���пռ�����Ϊtri_stack[aval], aval��ʼΪ 3
//����ջ��������ͷ�ڵ㣬���пռ�������ͷ�ڵ�
void makenull();
//��dataѹ��ջi
void push(const int i, const int data);
//����ջi
int pop(const int i);
//�ж�ջi�Ƿ�Ϊ��
bool empty(const int i);
bool full();
void print();
//���в�������
void test();
int main()
{
	tri_stack = new Node[MAXN];
	makenull();
	test();
	system("pause");
	return 0;
}
void makenull()
{
	aval = 3;
	for (int i = 3; i < MAXN - 1; i++)
		tri_stack[i].next = i + 1;
	tri_stack[MAXN - 1].next = 0;
}
void push(const int i, const int data)
{
	if (full()) {
		error("ջ��");
		return;
	}
	int cur = aval;
	aval = tri_stack[aval].next;
	
	tri_stack[cur].data = data;
	tri_stack[cur].next = tri_stack[i].next;
	tri_stack[i].next = cur;
}
int pop(const int i)
{
	if (empty(i))
	{
		error("ջ��");
		return 0;
	}
	int cur = tri_stack[i].next;
	tri_stack[i].next = tri_stack[cur].next;

	tri_stack[cur].next = aval;
	aval = cur;
	return tri_stack[cur].data;
}
bool empty(const int i)
{
	return tri_stack[i].next == 0 ? true : false;
}
bool full()
{
	return !aval;
}
void print()
{
	for (int i = 0; i < 3; i++)
	{
		if (empty(i)) {
			cout << i+1 << "ջ: ��" << endl;
			continue;
		}
		cout << i+1 << "ջ: ջ��> ";
		int j = i;
		while (tri_stack[j].next != 0)
		{
			j = tri_stack[j].next;
			cout << tri_stack[j].data << " ";
		}
		cout << "<ջ��" << endl;
	}
	cout << "����:";
	int i = aval;
	if (full()) {
		cout << "��" << endl << endl;
		return;
	}
	while (i != 0)
	{
		cout << i << " ";
		i = tri_stack[i].next;
	}
	cout << endl << endl;
}
void test()
{
	int op = 1;
	int i, data;
	ifstream is("sample.txt");
	while (op)
	{
		print();
		is >> op;
		if (op == 1)       //ִ��push����
		{
			is >> i >> data;
			cout << "push " << i+1 << " "<< data << endl;
			push(i, data);
		}
		else if (op == 2) //ִ��pop����
		{
			is >> i;
			cout << "pop " << i+1 << endl;
			pop(i);
		}
	}
	is.close();
}