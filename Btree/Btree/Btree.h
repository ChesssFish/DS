/*------------------------------------
Btree.h ver 0.1
�޸�����:2015��11��21��
����:sis

���ļ������˶������Ľڵ�ṹ
�����㽫������������װ��һ�����
Ȼ�������ڶ�...�����ʵ����˵ =_=
ֻ�����˻����Ľڵ�
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