/*------------------------------------
	文件名：AVL.cpp
	AVL.h中各声明的定义在此文件中
------------------------------------*/


#include"AVL.h"
#include<iostream>
template<typename keyType>
AVLnode<keyType>::AVLnode()
{
	pParent = NULL;
	pLchild = NULL;
	pRchild = NULL;
	mHeight = 1;
}
template<typename keyType>
AVLnode<keyType>::AVLnode(const keyType& key)
{
	pParent = NULL;
	pLchild = NULL;
	pRchild = NULL;
	mHeight = 1;
	mKey = key;
}
template<typename keyType>
AVLnode<keyType>::~AVLnode()
{
	delete pLchild;
	delete pRchild;
}
template<typename keyType>
AVLnode<keyType>& AVLnode<keyType>::operator=(AVLnode& node)
{
	mKey = node.mKey;
}
template<typename keyType>
bool AVLnode<keyType>::operator==(AVLnode& node)
{
	return mKey == node.mKey;
}
template<typename keyType>
bool AVLnode<keyType>::operator<(AVLnode& node)
{
	return mKey < node.mKey;
}
template<typename keyType>
bool AVLnode<keyType>::operator>(AVLnode& node)
{
	return mKey > node.mKey;
}
template<typename keyType>
bool AVLnode<keyType>::operator<=(AVLnode& node)
{
	return (mKey < node.mKey || mKey == node.mKey);
}
template<typename keyType>
void AVLnode<keyType>::_calcHeight()
{
	if (pLchild == NULL && pRchild == NULL)
	{
		mHeight = 1;
	}
	else if (pLchild == NULL)
	{
		mHeight = pRchild + 1;
	}
	else if (pRchild == NULL)
	{
		mHeight = pLchild + 1;
	}
	else
	{
		mHeight = max(pLchild->mHeight, pRchild->mHeight) + 1;
	}
}

template<typename keyType>
AVL<keyType>::AVL()
{
	root = NULL;
	mCount = 0;
	mlen = 0;
	mInOrder = NULL;
}
template<typename keyType>
AVL<keyType>::~AVL()
{
	delete root;//递归析构
	delete[]mInOrder;
}
template<typename keyType>
void AVL<keyType>::clear()
{
	delete root;
	root = NULL;
	mCount = 0;
}
template<typename keyType>
void AVL<keyType>::ins(keyType rec)
{
	mCount++;
	AVLnode<keyType>* newNode = new AVLnode<keyType>(rec);
	AVLnode<keyType>* cur = root;
	AVLnode<keyType>* pre = NULL;
	if (cur == NULL)
	{
		root = newNode;
		return;
	}
	while (cur != NULL)
	{
		pre = cur;
		if (*newNode <= *cur)
		{
			cur = cur->pLchild;
		}
		else
		{
			cur = cur->pRchild;
		}
	}
	if (*newNode <= *pre)
	{
		pre->pLchild = newNode;
	}
	else
	{
		pre->pRchild = newNode;
	}
	newNode->pParent = pre;
}
template<typename keyType>
bool AVL<keyType>::find(const keyType& key)
{
	AVLnode<keyType>* result;
	result = _find(key);
	if (result != NULL)
	{
		return true;
	}
	return false;
}
template<typename keyType>
void AVL<keyType>::del(const keyType& delkey)
{
	AVLnode<keyType>* delNode;
	delNode = _find(delkey);
	if (delNode != NULL)
	{
		_del(delNode);
		mCount--;
	}
}
template<typename keyType>
void AVL<keyType>::getInOrder()
{
	delete[]mInOrder;
	mInOrder = new keyType[mCount];
	mlen = 0;
	_print(root);
	for (int i = 0; i < mlen;i++)
	{
		std::cout << mInOrder[i] << " ";
	}
	std::cout << std::endl;
}
template<typename keyType>
void AVL<keyType>::_print(AVLnode<keyType>* cur)
{
	if (cur == NULL)return;
	_print(cur->pLchild);
	_visit(cur);
	_print(cur->pRchild);
}
template<typename keyType>
void AVL<keyType>::_visit(AVLnode<keyType>* cur)
{
	mInOrder[mlen++] = cur->mKey;
}
template<typename keyType>
AVLnode<keyType>* &AVL<keyType>::_find(const keyType& key)
{
	AVLnode<keyType>* cur = root;
	while (cur != NULL)
	{
		if (key == cur->mKey)
		{
			return cur;
		}
		else if (key < cur->mKey)
		{
			cur = cur->pLchild;
		}
		else
		{
			cur = cur->pRchild;
		}
	}
	return cur;
}
template<typename keyType>
void AVL<keyType>::_del(AVLnode<keyType>* &cur)
{
	AVLnode<keyType>* hNode;
	if (cur->pLchild == NULL && cur->pRchild == NULL)//叶节点
	{
		if (cur->pParent != NULL)
		{
			if (cur == cur->pParent->pLchild)
			{
				cur->pParent->pLchild = NULL;
			}
			else
			{
				cur->pParent->pRchild = NULL;
			}
		}
		delete cur;
		cur = NULL;
	}
	else if (cur->pLchild == NULL)//左子树为空
	{
		hNode = cur->pRchild;
		while (hNode->pLchild != NULL)
		{
			hNode = hNode->pLchild;
		}
		cur->mKey = hNode->mKey;
		if (hNode == cur->pRchild)
		{
			hNode->pParent->pRchild = hNode->pRchild;
		}
		else 
		{
			hNode->pParent->pLchild = hNode->pRchild;
		}
		if(hNode->pRchild != NULL)
		hNode->pRchild->pParent = hNode->pParent;
		hNode->pRchild = NULL;
		delete hNode;
	}
	else//左子树不空
	{
		hNode = cur->pLchild;
		while (hNode->pRchild != NULL)
		{
			hNode = hNode->pRchild;
		}
		cur->mKey = hNode->mKey;
		if (hNode == cur->pLchild)
		{
			hNode->pParent->pLchild = hNode->pLchild;
		}
		else
		{
			hNode->pParent->pRchild = hNode->pLchild;
		}
		if (hNode->pLchild != NULL)
		hNode->pLchild->pParent = hNode->pParent;
		hNode->pLchild = NULL;
		delete hNode;
	}
}
template<typename keyType>
void AVL<keyType>::_r(AVLnode<keyType>* cur)
{
	AVLnode<keyType>* Lnode = cur->pLchild;
	Lnode->pParent = cur->pParent;
	if (cur == cur->pParent->pLchild)//cur是左子树
	{
		cur->pParent->pLchild = Lnode;
		Lnode->pRchild->pParent = cur;
		cur->pLchild = Lnode->pRchild;
	}
	else//cur是右子树
	{
		cur->pParent->pRchild = Lnode;
		Lnode->pLchild->pParent = cur;
		cur->pRchild = cur->pLchild;
	}
	cur->pParent = Lnode;
	Lnode->pRchild = cur;
	if (cur == root)
	{
		root = cur->pParent;
	}

//	cur->calcHeight();
//	cur->pParent->mHeight = 0;
//	cur->pParent->pParent->calcHeight();
}
template<typename keyType>
void AVL<keyType>::_l(AVLnode<keyType>* cur)
{
	AVLnode<keyType>* Rnode = cur->pLchild;
	Rnode->pParent = cur->pParent;
	if (cur == cur->pParent->pLchild)//cur是左子树
	{
		cur->pParent->pLchild = Rnode;
		Rnode->pLchild->pParent = cur;
		cur->pLchild = Rnode->pLchild;
	}
	else//cur是右子树
	{
		cur->pParent->pRchild = Rnode;
		Rnode->pLchild->pParent = cur;
		cur->pRchild = Rnode->pLchild;
	}
	cur->pParent = Rnode;
	Rnode->pLchild = cur;
	if (cur == root)
	{
		root = cur->pParent;
	}

//	cur->calcHeight();
//	cur->pParent->mHeight = 0;
//	cur->pParent->pParent->calcHeight();
}