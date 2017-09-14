#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#define MAXCHAR 26
#define MAXN 10000
class Node
{
public:
	Node()
	{
		fail = NULL;
		memset(next, NULL, sizeof(next));
		isEnd = false;
	}
	~Node()
	{
		for (int i = 0; i < MAXCHAR; i++)
		{
			delete next[i];
		}
	}
	Node* fail;
	Node* next[MAXCHAR];
	bool isEnd;
};

class AC
{
public:
	AC()
	{
		root = NULL;
	}
	~AC()
	{
		delete root;
	}
	void build(std::vector<std::string> words);
	void insert(std::string str);
	auto query(std::string str) -> std::vector<int>;

private:
	Node* root;

};

void AC::build(std::vector<std::string> words)//建立
{
	delete root;
	root = new Node();

	for (int i = 0; i < words.size(); ++i) //建立树
	{
		insert(words[i]);
	}

	int head = 0;
	int tail = 0;
	root->fail = NULL;
	Node* q[MAXN];
	q[tail++] = root;

	while (head < tail)//建立失效指针
	{
		Node* tmp = q[head++];
		Node* p = NULL;
		for (int i = 0; i < MAXCHAR; ++i)
		{
			if (tmp->next[i] != NULL)
			{
				if (tmp == root)
				{
					tmp->next[i]->fail = root;
				}
				else
				{
					p = tmp->fail;
					while (p != NULL)
					{
						if (p->next[i] != NULL)
						{
							tmp->next[i]->fail = p->next[i];
							break;
						}
						p = p->fail;
					}
					if (p == NULL)
					{
						tmp->next[i]->fail = root;
					}
				}
				q[tail++] = tmp->next[i];
			}
		}
	}
}

void AC::insert(std::string str)//插入单词
{
	Node *p = root;
	int i = 0;
	int index;
	while (i < str.length())
	{
		index = str[i] - 'a';
		if (p->next[index] == NULL)
		{
			p->next[index] = new Node();
		}
		p = p->next[index];
		++i;
	}
	p->isEnd = true;
}

auto AC::query(std::string str) ->std::vector<int>//查询目标串
{
	int len = str.length();
	Node* cur = root;
	std::vector<int> ans;
	int index;
	for (int i = 0; i < len; ++i)
	{
		index = str[i] - 'a';
		while (cur->next[index] == NULL && cur != root)
		{
			cur = cur->fail;
		}
		cur = cur->next[index];
		cur = (cur == NULL) ? root : cur;

		Node* tmp = cur;
		while (tmp != root)
		{
			if (tmp->isEnd)
			{
				ans.push_back(i);
			}
			tmp = tmp->fail;
		}
	}
	return ans;
}
