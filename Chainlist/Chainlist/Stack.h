/*---------------------------------
	用链表实现的堆栈
	包括基本的操作
---------------------------------*/
#pragma once
#include <iostream>
//打印一条错误信息
void error(char* str)
{
	std::cout << str << std::endl;
}
class Node
{
public:
	Node(int c = 0):val(c),next(NULL) {};
	~Node() {};
	int val;
	Node* next;
};
class Stack
{
public:
	Stack();
	~Stack();
	void makenull();
	void push(int val);
	int pop();
	bool empty();
	void show();
	Node* top;
private:
	Node* phead;
};
Stack::Stack()
{
	phead = new Node;
	top = phead->next;
}
void Stack::makenull()
{
	Node* del = phead;
	Node* cur = del->next;
	while (cur != NULL)
	{
		del = cur;
		cur = cur->next;
		delete del;
	}
	phead->next = NULL;
	top = NULL;
}
void Stack::push(int val)
{
	Node* newNode = new Node(val);
	if (newNode == NULL)
	{
		error("没有足够的内存");
		return;
	}
	newNode->next = phead->next;
	phead->next = newNode;
	top = newNode;
}
int Stack::pop()
{
	if (empty())
	{
		error("栈空");
		return 0;
	}
	int ret = top->val;
	phead->next = top->next;
	delete top;
	top = phead->next;
	return ret;
}
bool Stack::empty()
{
	return top == NULL ? true : false;
}
void Stack::show()
{
	Node* cur = phead->next;
	while (cur != NULL)
	{
		std::cout << cur->val << " ";
		cur = cur->next;
	}
	std::cout << std::endl;
	if(top)
	std::cout << "top: " << top->val << std::endl;
}
Stack::~Stack()
{
	makenull();
	delete phead;
}

class Nodef
{
public:
	Nodef(float c = 0.0) :val(c), next(NULL) {};
	~Nodef() {};
	float val;
	Nodef* next;
};
class Stackf
{
public:
	Stackf();
	~Stackf();
	void makenull();
	void push(float val);
	float pop();
	bool empty();
	Nodef* top;
private:
	Nodef* phead;
};
Stackf::Stackf()
{
	phead = new Nodef;
	top = phead->next;
}
void Stackf::makenull()
{
	Nodef* del = phead;
	Nodef* cur = del->next;
	while (cur != NULL)
	{
		del = cur;
		cur = cur->next;
		delete del;
	}
	phead->next = NULL;
	top = NULL;
}
void Stackf::push(float val)
{
	Nodef* newNode = new Nodef(val);
	if (newNode == NULL)
	{
		error("没有足够的内存");
		return;
	}
	newNode->next = phead->next;
	phead->next = newNode;
	top = newNode;
}
float Stackf::pop()
{
	if (empty())
	{
		error("栈空");
		return 0;
	}
	float ret = top->val;
	phead->next = top->next;
	delete top;
	top = phead->next;
	return ret;
}
bool Stackf::empty()
{
	return top == NULL ? true : false;
}
Stackf::~Stackf()
{
	makenull();
	delete phead;
}