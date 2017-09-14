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
	std::vector<bool> vis;		//访问标记
	std::vector<int> parent;	//父节点（由哪个节点递归而来)
	std::vector<int> dfn;		//深度戳
	std::vector<int> ancestor;	//后向边能找到的最早祖先的深度戳
	void _dfs(const int u);		//深搜
	bool _isbio;				//双连通性标记
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

	//根据顶点数调整容器大小
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
	int cnt_child = 0;//记录当前节点在深搜树中孩子的个数
	vis[u] = true;
	dfn[u] = ancestor[u] = depth++;
	//遍历u所有边
	for (auto i = edge[u].cbegin(); i != edge[u].cend(); i++)
	{
		if (!vis[*i])	//树边
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
		else			//后向边
		{
			ancestor[u] = std::min(ancestor[u], dfn[*i]);
		}

	}
}
