#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<queue>
#include<vector>
class Edge
{
public:
	Edge(int rv, int rw) :v(rv), w(rw) {};
	Edge(const Edge& rhs) {v = rhs.v;w = rhs.w; }
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
	int Prim(int u = 0);

private:
	std::vector<std::vector<Edge>> edgelist;	//邻接表
	std::vector<bool> used;						//已选择的点集
	std::priority_queue<Edge> avalable;			//待选择的边集
};
void G::ReadGraph(const std::string& filename)
{
	std::ifstream is;
	is.open(filename);
	int u, v, w;
	int cnt = 0;
	while (is >> u >> v >> w)
	{
		while (u >= edgelist.size() || v >= edgelist.size())
		{
			edgelist.push_back(std::vector<Edge>());
		}
		edgelist[u].push_back(Edge(v, w));
		edgelist[v].push_back(Edge(u, w));
	}
	used.resize(edgelist.size(), false);
	is.close();
}
int G::Prim(int u)
{
	int ans = 0;
	used[u] = true;
	for (auto i = edgelist[u].cbegin(); i != edgelist[u].cend(); i++)
	{
		avalable.push(*i);
	}
	while (true)
	{
		//删除不合法的边
		while (!avalable.empty() && used[avalable.top().v])
		{
			avalable.pop();
		}
		//可选择边集为空则程序结束
		if (avalable.empty())
		{
			break;
		}

		//将新节点加入已选择的点集
		int v = avalable.top().v;
		ans += avalable.top().w;
		used[v] = true;
		avalable.pop();

		//将与新加入的点相连的边加入待选择边集
		for (auto
			i = edgelist[v].cbegin();
			i != edgelist[v].cend(); i++)
		{
			if (!used[(*i).v])
			{
				avalable.push(*i);
			}
		}
	}
	return ans;
}