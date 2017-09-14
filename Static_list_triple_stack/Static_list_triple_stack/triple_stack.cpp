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
//三栈的栈顶(表头)分别为tri_stack[0], tri_stack[1], tri_stack[2]
//空闲空间链表为tri_stack[aval], aval初始为 3
//用作栈的链表有头节点，空闲空间链表无头节点
void makenull();
//将data压入栈i
void push(const int i, const int data);
//弹出栈i
int pop(const int i);
//判断栈i是否为空
bool empty(const int i);
bool full();
void print();
//运行测试样例
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
		error("栈满");
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
		error("栈空");
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
			cout << i+1 << "栈: 空" << endl;
			continue;
		}
		cout << i+1 << "栈: 栈顶> ";
		int j = i;
		while (tri_stack[j].next != 0)
		{
			j = tri_stack[j].next;
			cout << tri_stack[j].data << " ";
		}
		cout << "<栈底" << endl;
	}
	cout << "空闲:";
	int i = aval;
	if (full()) {
		cout << "无" << endl << endl;
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
		if (op == 1)       //执行push操作
		{
			is >> i >> data;
			cout << "push " << i+1 << " "<< data << endl;
			push(i, data);
		}
		else if (op == 2) //执行pop操作
		{
			is >> i;
			cout << "pop " << i+1 << endl;
			pop(i);
		}
	}
	is.close();
}