/*---------------------------------------------
文件名: my_list.h
版本: ver 0.1
作者: sis
说明:
	双向链表
	需要使用的结构实现 = 与 == 的重载
	ver 0.1:
	实现链表的置空、插入、删除、查询
---------------------------------------------*/

#pragma once
#include<iostream>
template <class T>class Mylist;
template <class T>
class ListNode
{
public:
	ListNode();
	~ListNode();
	ListNode<T>& operator=(ListNode<T>& node);
	bool operator==(ListNode<T>& node);
private:
	T* pData;
	ListNode<T>* pNext;
	ListNode<T>* pPre;
	friend class Mylist<T>;
};
template <class T>class Mylist
{
public:
	Mylist();
	~Mylist();
	Mylist<T>& MakeNull();
	Mylist<T>& Ins(const T& newData, int pos);
	Mylist<T>& Del(const int pos);
	ListNode<T> Get(const int pos);
private:
	int mCount;
	ListNode<T>* pHead;
	ListNode<T>* pTail;

};