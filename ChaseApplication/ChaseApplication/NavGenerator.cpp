#include "NavGenerator.h"
#include <queue>
#include <vector>
#include <bitset>
void NavGenerator::GenerateNavTable(Table & adjList)
{
	int tileN = adjList.size();
	NavTable.clear();
	NavTable.resize(tileN);
	for (int i = 0; i < tileN; ++i)
	{
		path.clear();
		path.resize(tileN, -1);
		_bfs(i, adjList);
		_generateTableRow(i, tileN);
	}
}

Table & NavGenerator::GetNavTable()
{
	return NavTable;
}

void NavGenerator::_bfs(const Tile & src, const Table & adjList)
{
	typedef std::pair<uint16_t, uint16_t> node;
	
	std::queue<node> q;
	std::bitset<std::numeric_limits<uint16_t>::max()> vis;
	q.push(node(src,0));
	vis[src] = true;
	while (!q.empty())
	{
		node u = q.front();
		q.pop();
		for (auto i : adjList[u.first])
		{
			if (!vis[i])
			{
				path[i] = u.first;
				q.push(node(i, u.second + 1));
				vis[i] = true;
			}
		}
	}
	return;
}

void NavGenerator::_generateTableRow(const int & row, const int & tileN)
{
	NavTable[row].resize(tileN);
	for (auto i = 0; i < tileN; ++i)
	{
		int pos = i;
		int d = pos;
		if (path[i] != (uint16_t)-1)
		{
			while (pos != row)
			{
				d = pos;
				pos = path[pos];
			}
		}
		else
		{
			d = row;
		}
		NavTable[row][i] = d;
	}
}
