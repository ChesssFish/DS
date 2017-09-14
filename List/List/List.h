#pragma once
#include <iostream>
#include <fstream>
#include <cstring>
#define MAXLEN 50
using std::cin;
using std::cout;
using std::endl;
class Node
{
public:
	Node(char* name = "", char* logo = "", double price = 0.0, int amount = 0);
	Node(const Node& node);//拷贝构造函数不拷贝pNext,而是赋值为空
	~Node();
	char* mName;
	char* mLogo;
	double mPrice;
	int mAmount;
	Node& operator=(const Node& node);//仅复制以上四个成员，不改变pNext
	bool operator==(const Node& node);//当数据一致时，返回true
	void show();
private:
	friend class List;
	Node* pNext;
};
Node::Node(char* name, char* logo, double price, int amount):
	mPrice(price),mAmount(amount),pNext(NULL)
{
	mName = new char[MAXLEN];
	mLogo = new char[MAXLEN];
	memcpy(mName, name, MAXLEN);
	memcpy(mLogo, logo, MAXLEN);
}
Node::Node(const Node& node)
{
	memcpy(mName, node.mName, MAXLEN);
	memcpy(mLogo, node.mLogo, MAXLEN);
	mPrice = node.mPrice;
	mAmount = node.mAmount;
}
Node::~Node()
{
	delete[]mName;
	delete[]mLogo;
}
void Node::show()
{
	std::cout << "品名: " << mName << std::endl;
	std::cout << "商标: " << mLogo << std::endl;
	std::cout << "价格: " << mPrice << std::endl;
	std::cout << "数量: " << mAmount << std::endl << std::endl;;
}
Node& Node::operator=(const Node& node)
{
	memcpy(mName, node.mName, MAXLEN);
	memcpy(mLogo, node.mLogo, MAXLEN);
	mPrice = node.mPrice;
	mAmount = node.mAmount;
	return *this;
}
bool Node::operator==(const Node& node)
{
	if (strcmp(node.mName, mName) == 0 &&
		strcmp(mLogo, node.mLogo) == 0 &&
		mPrice == node.mPrice &&
		mAmount == node.mAmount)
		return true;
	return false;
}
class List
{
public:
	List();
	~List();
	List* makenull();//置空链表
	List* load(std::ifstream& is);
	List* save(std::ofstream& os);
	List* ins(Node* newNode);//将元素插入适当位置(升序)
	List* del(int pos);//删除pos位置的元素，不存在则不做任何事
	List* del(Node& nd);//删除数据与nd一致的节点，不存在则不做任何事
	Node& operator[](int pos);//获得pos处的元素,元素不存在则返回*pHead
	Node& operator[](const char* name);//获得名为name的元素,元素不存在则返回*pHead
	List* show();//打印链表
	bool exist(Node&);//判断[]返回的节点是不是头*pHead
private:
	Node* pHead;
	int mCount;
};

List::List():
	mCount(0)
{
	pHead = new Node;
}

List::~List()
{
	makenull();
	delete pHead;
}
List* List::makenull()
{
	Node* cur = pHead->pNext;
	Node* next;
	while (cur != NULL)
	{
		next = cur->pNext;
		delete cur;
		cur = next;
	}
	pHead->pNext = NULL;
	mCount = 0;
	return this;
}
List* List::ins(Node* newNode)
{
	Node* cur = pHead;
	while (cur->pNext != NULL)
	{
		if (cur->pNext->mPrice >= newNode->mPrice)
			break;
		cur = cur->pNext;
	}
	newNode->pNext = cur->pNext;
	cur->pNext = newNode;
	mCount++;
	return this;
}
List* List::del(int pos)
{
	if (pos < 0 || pos >= mCount)
		return this;
	Node* cur = pHead->pNext;
	Node* pre = pHead;
	while (pos--)
	{
		pre = cur;
		cur = cur->pNext;
	}
	pre->pNext = cur->pNext;
	delete cur;
	mCount--;
	return this;
}
List* List::del(Node& nd)
{
	Node* cur = pHead->pNext;
	Node* pre = pHead;
	while (cur != NULL)
	{
		if (*cur == nd)
		{
			pre->pNext = cur->pNext;
			delete cur;
			mCount--;
			return this;
		}
		pre = cur;
		cur = cur->pNext;
	}
	return NULL;
}
List* List::show()
{
	Node* cur = pHead->pNext;
	int cnt = 0;
	while (cur != NULL)
	{
		std::cout << "No." << ++cnt << ": " << std::endl;
		cur->show();
		cur = cur->pNext;
	}
	return this;
}
Node& List::operator[](int pos)
{
	if (pos < 0 || pos >= mCount)
		return *pHead;
	Node* cur = pHead->pNext;
	while (cur!= NULL)
	{
		if (pos-- == 0)
			return *cur;
		cur = cur->pNext;
	}
	return *pHead;
}
Node& List::operator[](const char* name)
{
	Node* cur = pHead->pNext;
	while (cur != NULL)
	{
		if (strcmp(name, cur->mName) == 0)
			return *cur;
		cur = cur->pNext;
	}
	return *pHead;
}
bool List::exist(Node& node)
{
	if (node == *pHead)
		return false;
	return true;
}
List* List::save(std::ofstream& os)
{
	cout << "正在保存..." << endl;
	os.write((char*)&mCount, sizeof(mCount));
	Node* cur = pHead->pNext;
	while (cur != NULL)
	{
		os.write((cur->mName), sizeof(char)*MAXLEN);
		os.write((cur->mLogo), sizeof(char)*MAXLEN);
		os.write((char*)&(cur->mPrice), sizeof(double));
		os.write((char*)&(cur->mAmount), sizeof(int));
		cur = cur->pNext;
	}
	cout << "已保存" << endl;
	return this;
}
List* List::load(std::ifstream& is)
{
	cout << "正在加载数据..." << endl;
	is.read((char*)&mCount, sizeof(mCount));
	int count = mCount;
	Node* newNode;
	while (count-- > 0)
	{
		newNode = new Node;
		is.read((newNode->mName), sizeof(char)*MAXLEN);
		is.read((newNode->mLogo), sizeof(char)*MAXLEN);
		is.read((char*)&(newNode->mPrice), sizeof(double));
		is.read((char*)&(newNode->mAmount), sizeof(int));
		newNode->pNext = NULL;
		ins(newNode);
	}
	cout << "已加载数据" << endl;
	return this;
}