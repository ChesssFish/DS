#pragma once
#include<iostream>
#include<string>
#include<fstream>
using namespace std;
class ThTree;
class Node
{
public:
	Node() :lc(NULL), rc(NULL) {};
	~Node()
	{
		if (lc)
			delete lc;
		if (rc)
			delete rc;
	};
private:
	typedef char dataType;
	Node* lc;
	Node* rc;
	bool ltag; //true:Õæº¢×Ó false:ÏßË÷
	bool rtag;
	dataType data;
	friend class ThTree;
};

class ThTree
{
public:
	ThTree();
	~ThTree();
	void PreOrderThreading();
	void Traverse();
	void BuildTree(string file);
private:
	Node* root;
	Node* _pre;
	//void InOrderTraverse();
	void _buildtree(Node* &cur, int start, int end);
	void _prethreading(Node* cur);
	int _findkey(int cnt, int start, int end);
};