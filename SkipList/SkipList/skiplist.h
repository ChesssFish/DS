#pragma once
#include<vector>
#define MAXLEVEL 29
using std::vector;
template<class keyType> class Node;
template<class keyType> class Skiplist;

template<class keyType>
class Node
{
public:
	Node(int lv, keyType k);
	Node() {};
	~Node();
	keyType key;
	vector<Node*> next;
	void Print();
};
template<class keyType>
class Skiplist
{
public:
	Skiplist();
	~Skiplist();
	Node<keyType>* Find(const keyType& key);
	Skiplist* Insert(const keyType& key);
	Skiplist* Delete(const keyType& key);
	bool Empty();
	void Print();

private:
	Node<keyType>* head;
};

/*-------------------------------------------------------------------
			           Node实现
-------------------------------------------------------------------*/

template<class keyType>
Node<keyType>::Node(int level, keyType k)
{
	key = k;
	while (level--)
	{
		next.push_back(NULL);
	}
}
template<class keyType>
Node<keyType>::~Node()
{
	if (!next.empty())
	{
		delete next[0];
	}
}
template<class keyType>
void Node<keyType>::Print()
{
	cout << "节点信息:" << endl;
	cout << "Key: " << key << endl;
	cout << "Level: " << next.size() << endl;
	cout << endl;
}

/*------------------------------------------------
		           Skiplist实现
------------------------------------------------*/

template<class keyType>
Skiplist<keyType>::Skiplist()
{
	head = new Node<keyType>;
}
template<class keyType>
Skiplist<keyType>::~Skiplist()
{
	delete head;
}

template<class keyType>
Node<keyType>* Skiplist<keyType>::Find(const keyType& k)
{
	Node<keyType>* cur = head;
	if (Empty())
	{
		return NULL;
	}
	while (cur != NULL)
	{
		if (cur != head)
		{
			if (cur->key == k)
			{
				return cur;
			}
			else if (cur->key > k)
			{
				return NULL;
			}
		}
		for (auto i = cur->next.crbegin(); i != cur->next.crend(); i++)
		{
			if ((*i) != NULL && ((*i)->key <= k || (*i) == cur->next[0]))
			{
				cur = *i;
				break;
			}
		}
	}
	return NULL;
}

template<class keyType>
Skiplist<keyType>* Skiplist<keyType>::Insert(const keyType& k)
{
	int coin = 1;
	int randlevel = 0;
	int dif = 0;
	int pos = numeric_limits<int>::max();
	bool done = false;
	Node<keyType>* cur = head;
	Node<keyType>* newNode;

	while (coin && randlevel <= MAXLEVEL)
	{
		randlevel++;
		coin = rand() % 2;
	}
	dif = randlevel - cur->next.size();
	while (dif-- > 0)
	{
		cur->next.push_back(NULL);
	}
	newNode = new Node<keyType>(randlevel, k);
	while (cur != NULL)
	{
		auto begin = cur->next.crbegin();
		auto end = cur->next.crend();
		for (auto i = begin; i != end; i++)
		{
			if ((*i) != NULL && (*i)->key < k)
			{
				cur = *i;
				break;
			}

			pos = end - i - 1;
			if (randlevel - 1 >= pos)//新插入节点层数大于当前层数，则需要更新
			{
				newNode->next[pos] = cur->next[pos];
				cur->next[pos] = newNode;
			}
		}
		if (pos == 0)
		{
			break;
		}
	}
	return this;
}

template<class keyType >
Skiplist<keyType>* Skiplist<keyType>::Delete(const keyType& k)
{
	vector<Node<keyType>*> update;
	bool inlist = false;
	Node<keyType>* cur = head;

	if (Empty())
	{
		return this;
	}
	while (cur != NULL)
	{
		inlist = false;
		if (cur != head)
		{
			if (cur->key == k)
			{
				break;
			}
			else if (cur->key > k)
			{
				return this;
			}
		}
		for (auto i = cur->next.crbegin(); i != cur->next.crend(); i++)
		{
			if ((*i) != NULL && (*i)->key < k)
			{
				cur = *i;
				break;
			}
			else if ((*i) != NULL && (*i) == cur->next[0])
			{
				update.push_back(cur);
				cur = *i;
				break;
			}
			else if (!inlist)
			{
				inlist = true;
				update.push_back(cur);
			}
		}
	}
	for (unsigned i = 0; i < update.size(); i++)
	{
		for (unsigned j = 0; j < update[i]->next.size(); j++)
		{
			if (update[i]->next[j] == cur)
			{
				update[i]->next[j] = cur->next[j];
			}
		}
	}
	for (unsigned i = 0; i < cur->next.size(); i++)
	{
		cur->next[i] = NULL;
	}
	delete cur;
	return this;
}
template<class keyType>
void Skiplist<keyType>::Print()
{
	Node<keyType>* cur = head;
	while (cur != NULL)
	{
		cout << cur->key << " " << cur->next.size() << " -> ";
		cur = cur->next[0];
	}
	cout << endl;
}
template<class keyType>
bool Skiplist<keyType>::Empty()
{
	for (unsigned i = 0; i < head->next.size(); i++)
	{
		if (head->next[i] != NULL)
			return false;
	}
	return true;
}