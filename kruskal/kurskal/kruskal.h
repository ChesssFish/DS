#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<vector>
class Edge
{
public:
	Edge(int ru,int rv,int rw):u(ru),v(rv),w(rw) {};
	Edge(const Edge& rhs) { u = rhs.u;v = rhs.v;w = rhs.w; }
	~Edge() {};
	int u, v;
	int w;
	bool operator<(const Edge& rhs) const { return w < rhs.w; }
	Edge& operator=(const Edge& rhs) 
	{
		u = rhs.u;
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
	std::vector<Edge> Kruskal(void);

private:
	std::vector<Edge> edgeset;
	std::vector<int> father;
	int _findfather(int x);
};
void G::ReadGraph(const std::string& filename)
{
	std::ifstream is;
	is.open(filename);
	int u, v, w;
	int cnt = 0;
	while (is >> u >> v >> w)
	{
		while (u >= father.size() || v >= father.size())
		{
			father.push_back(cnt++);
		}
		edgeset.push_back(Edge(u,v,w));
	}
	is.close();
	std::sort(edgeset.begin(), edgeset.end());
}
int G::_findfather(int x)
{
	if (father[x] == x)return x;
	else 
	{
		father[x] = _findfather(father[x]);
		return father[x];
	}
}
std::vector<Edge> G::Kruskal(void)
{
	std::vector<Edge> result;
	for (auto i = edgeset.cbegin(); i != edgeset.cend(); i++)
	{
		if (_findfather((*i).u) != _findfather((*i).v))
		{
			result.push_back(*i);
			father[_findfather((*i).u)] = father[_findfather((*i).v)];
		}
	}
	return result;
}