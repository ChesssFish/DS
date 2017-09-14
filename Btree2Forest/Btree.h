/*------------------------------------
Btree.h ver 0.1
修改日期:2015年11月21日
作者:sis

此文件定义了二叉树的节点结构
本打算将整个二叉树封装在一个类里，
然而问题众多...先完成实验再说 =_=
只定义了基本的节点
------------------------------------*/
#pragma once
#define MAXN 100
#define NULL 0
template<class T>
class Node
{
public:
	Node();
	~Node() {}
	T mp_data;
	Node* mp_lc;
	Node* mp_rc;
};
/*
template<class T>
class bTree
{
public:
	typedef Node<T> treeNode;
	bTree();
	~bTree();
	bTree<T>* BuildTree();
	bTree<T>* DelTree();

private:
	int mCount;
	treeNode* mPre;
	treeNode* mIn;
	treeNode* mPost;
	treeNode* mpRoot;
};*/