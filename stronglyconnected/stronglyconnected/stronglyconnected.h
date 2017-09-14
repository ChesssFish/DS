#pragma once
#include<algorithm>
#include<fstream>
#include<string>
#include<vector>
class G
{
public:
	G() {};
	~G() {};
	void ReadGraph(const std::string& filename);
	bool IsStrong(void);
private:
	std::vector<std::vector<int>> edge;
	std::vector<int> dfn;
	std::vector<int> ancestor;
	std::vector<bool> vis;		//访问标记
	bool _isstrong;
	void _dfs(const int u);
};
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
	}
	is.close();

	//根据顶点数调整容器大小
	vis.resize(edge.size(), false);
	dfn.resize(edge.size(), -1);
	ancestor.resize(edge.size(), -1);
	edge.shrink_to_fit();
}
bool G::IsStrong(void)
{
	_isstrong = true;
	_dfs(0);
	return _isstrong;
}
void G::_dfs(const int u)
{
	static int cnt = 0;
	vis[u] = true;
	dfn[u] = ancestor[u] = cnt++;
	for (auto i = edge[u].cbegin(); i != edge[u].cend(); i++)
	{
		if (!vis[*i])
		{
			_dfs(*i);
			ancestor[u] = std::min(ancestor[u], ancestor[*i]);
			if (ancestor[u] == dfn[u] && u != 0)
			{
				_isstrong = false;
			}
		}
		else
		{
			ancestor[u] = std::min(ancestor[u],dfn[*i]);
		}
	}
}