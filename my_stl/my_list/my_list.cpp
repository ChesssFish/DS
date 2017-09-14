#include"my_list.h"
template<class T>
ListNode<T>::ListNode():
	pNext(NULL),
	pPre(NULL),
	pData(NULL)
{
}
template<class T>
ListNode<T>::~ListNode() {}
template<class T>
ListNode<T>& ListNode<T>::operator=(ListNode<T>& node)
{
	*(pData) = *(node.pData);
	return *this;
}
template<class T>
bool ListNode<T>::operator==(ListNode<T>& node)
{
	return *(pData) == *(node.pData);
}

template<class T>
Mylist<T>::Mylist()
{
	pHead = new ListNode<T>;
	pTail = pHead;
	mCount = 0;
}
template<class T>
Mylist<T>::~Mylist()
{
	MakeNull();
	delete pHead;
}
template<class T>
Mylist<T>& Mylist<T>::MakeNull(void)
{
	ListNode<T>* cur = pHead->pNext;
	ListNode<T>* next;
	if (cur == NULL)
	{
		return;
	}

	while (cur != NULL)
	{
		next = cur->pNext;
		delete cur;
		cur = next;
	}
	return *this;
}
template<class T>
Mylist<T>& Mylist<T>::Ins(const T& newData, int pos)
{
	if (pos < 0 || pos > mCount - 1)
	{
		return *this;
	}
	ListNode<T>* cur = pHead;
	ListNode<T>* tmp = new ListNode<T>;
	tmp->mData = newData;
	while (cur != NULL)
	{
		if (pos-- == 0)
		{
			tmp->pNext = cur->pNext;
			tmp->pPre = cur;
			cur->pNext = tmp;
			if (tmp->pNext != NULL)
			{
				tmp->pNext->pPre = tmp;
			}
			mCount++;
			break;
		}
		cur = cur->pNext;
	}
	return *this;
}
class Node
{
public:
	int a;
};
int main()
{
	Mylist<Node>* n = new Mylist<Node>;
	return 0;
}