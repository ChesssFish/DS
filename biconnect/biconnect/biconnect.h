#pragma once
#include<algorithm>
#include<fstream>
#include<string>
#include<vector>
#include<iostream>
class G
{
public:
	G();
	~G();
	void ReadGraph(const std::string& filename);
	bool IsBioconnected(void);
private:
	std::vector<std::vector<int>> edge;
	std::vector<bool> vis;		//���ʱ��
	std::vector<int> parent;	//���ڵ㣨���ĸ��ڵ�ݹ����)
	std::vector<int> dfn;		//��ȴ�
	std::vector<int> ancestor;	//��������ҵ����������ȵ���ȴ�
	void _dfs(const int u);		//����
	bool _isbio;				//˫��ͨ�Ա��
};
G::G()
{
}

G::~G()
{
}

void G::ReadGraph(const std::string& filename)
{
	std::ifstream is;
	int u, v;
	is.open(filename);
	while (is >> u >> v)
	{
		while (u >= edge.size() || v >= edge.size())
		{
			edge.push_back(std::vector<int>());
		}
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	is.close();

	//���ݶ���������������С
	vis.resize(edge.size(), false);
	parent.resize(edge.size(), -1);
	dfn.resize(edge.size(), -1);
	ancestor.resize(edge.size(), -1);
	edge.shrink_to_fit();
}
bool G::IsBioconnected(void)
{
	_isbio = true;
	_dfs(0);
	return _isbio;
}
void G::_dfs(const int u)
{
	static int depth = 0;	
	int cnt_child = 0;//��¼��ǰ�ڵ����������к��ӵĸ���
	vis[u] = true;
	dfn[u] = ancestor[u] = depth++;
	//����u���б�
	for (auto i = edge[u].cbegin(); i != edge[u].cend(); i++)
	{
		if (!vis[*i])	//����
		{
			cnt_child++;
			parent[*i] = u;
			_dfs(*i);
			ancestor[u] = std::min(ancestor[u], ancestor[*i]);
			if (parent[u] == -1 && cnt_child > 1)
			{
				_isbio = false;
			}
			if (parent[u] != -1 && ancestor[*i] >= dfn[u])
			{
				_isbio = false;
			}
		}
		else			//�����
		{
			ancestor[u] = std::min(ancestor[u], dfn[*i]);
		}

	}
}
