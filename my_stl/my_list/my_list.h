/*---------------------------------------------
�ļ���: my_list.h
�汾: ver 0.1
����: sis
˵��:
	˫������
	��Ҫʹ�õĽṹʵ�� = �� == ������
	ver 0.1:
	ʵ��������ÿա����롢ɾ������ѯ
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