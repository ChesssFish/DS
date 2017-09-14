#pragma once
#include<vector>
#include<string>
#include<fstream>
using namespace std;
class Node
{
public:
	Node() {};
private:
	int data;
	vector<Node*> next;
	friend class Btree2Forest;
};

class Btree2Forest
{
public:
	Btree2Forest() :state(Btree), _pre(NULL) { roots.push_back(NULL); }
	//功能：将二叉树转化为森林的接口入口
	//调用位置: main
	void ToForest(void);
	//功能：将森林转化为二叉树的接口入口
	//调用位置: main
	void ToBtree(void);
	//功能：建立二叉树的接口入口
	//调用位置: main
	void BuildBtree(string file);
private:
	enum S
	{
		Btree,
		Forest
	};
	S state;
	vector<Node*> roots;
	Node* _pre;
	//功能：将单棵树转化为二叉树
	//参数1：树根节点
	//调用位置：ToBtree
	void _tobtree(Node* cur);

	//功能：将cur节点转化为一个二叉树节点
	//参数1：需转化的节点
	//调用位置：_tobtree
	void _delete(Node* cur);

	//功能：将单棵二叉树转化为树
	//参数1：树根节点
	//调用位置：ToForest
	void _totree(Node* cur);

	//功能:二叉树转化为树过程中，
	//     将左孩子的右、右右、右右右...子树连接至cur
	//参数: 需连接的节点
	//调用位置: _totree
	void _link(Node* cur);

	//功能:根据前序、中序序列建立二叉树
	//参数1:根节点
	//参数2:子树起始位置
	//参数3:子树结束位置（含最末节点）
	//调用位置: BuildTree
	void _buildtree(Node*& cur, int start, int end);

	//功能: 寻找前序序列中某节点在中序序列中的位置
	//参数1: 前序序列中节点的位置
	//参数2: 需要寻找的起始位置
	//参数3: 需要寻找的结束位置
	//调用位置: _buildtree
	int _findkey(int cnt, int start, int end);
};