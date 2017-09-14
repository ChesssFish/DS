#pragma once
#include<queue>
#include<vector>
#include<fstream>
#include<algorithm>
class Edge
{
public:
	Edge(int pv, int pw) :v(pv), w(pw) {};
	Edge(const Edge& rhs) { v = rhs.v;w = rhs.w; }
	~Edge() {};
	int v;
	int w;
	bool operator<(const Edge& rhs) const { return w > rhs.w; }
	Edge& operator=(const Edge& rhs)
	{
		v = rhs.v;
		w = rhs.w;
		return *this;
	}
};
class G
{
public:
	G() {};
	~G() {};
	void ReadGraph(const std::string& filename);
	bool BellmanFord(const int& u);
	void Dijkstra(const int & u);

private:
	static const int Inf = 0xfffffff;
	std::vector<int> d;									//最短路径估值
	std::vector<int> pre;								//前向节点
	std::vector<std::vector<Edge>> edgelist;			//邻接表
	void _relax(const int& u);							//松弛u所有的边
	void _initialize(const int& u);						//初始化 d 和 pre
	int _extract_min(const std::vector<bool>& inSet);	//寻找最小的 d
};
void G::ReadGraph(const std::string& filename)
{
	std::ifstream is;
	is.open(filename);
	int u, v, w;
	while (is >> u >> v >> w)
	{
		while (u >= edgelist.size() || v >= edgelist.size())
		{
			edgelist.push_back(std::vector<Edge>());
		}
		edgelist[u].push_back(Edge(v, w));
		edgelist[v].push_back(Edge(u, w));
	}
	is.close();
}
void G::_initialize(const int& u)
{
	pre.clear();
	d.clear();
	pre.resize(edgelist.size(), -1);
	d.resize(edgelist.size(), Inf);
	d[u] = 0;
}
void G::_relax(const int& u)
{
	for (auto i = edgelist[u].cbegin(); i != edgelist[u].cend(); i++)
	{
		if (d[(*i).v] > d[u] + (*i).w)
		{
			d[(*i).v] = d[u] + (*i).w;
			pre[(*i).v] = u;
		}
	}
}
bool G::BellmanFord(const int& u)
{
	_initialize(u);
	for (int i = 0; i < edgelist.size() - 1; i++)//计数 V - 1次
	{
		for (int j = 0; j < edgelist.size(); j ++)
		{
			_relax(j);
		}
	}
	for (int i = 0; i < edgelist.size(); i++)
	{
		for (auto j = edgelist[i].cbegin(); j != edgelist[i].cend(); j++)
		{
			if (d[(*j).v] > d[u] + (*j).w)
			{
				return false;
			}
		}
	}
	return true;
}
int G::_extract_min(const std::vector<bool>& inSet)
{
	int min = Inf;
	int pos = 0;
	for (int i = 0; i < edgelist.size(); i++)
	{
		if (!inSet[i] && d[i] < min)
		{
			min = d[i];
			pos = i;
		}
	}
	return pos;
}
void G::Dijkstra(const int & u)
{
	std::vector<bool> inSet;
	inSet.resize(edgelist.size(), false);
	_initialize(u);
	int v;
	int cnt = 0;
	while (cnt++ < edgelist.size())
	{
		v = _extract_min(inSet);
		_relax(v);
		inSet[v] = true;
	}
}
