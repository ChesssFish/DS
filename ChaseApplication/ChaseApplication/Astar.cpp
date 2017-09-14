#include"Astar.h"
#include"PriorityQueue.h"
#include<queue>
#include<algorithm>

Astar::Astar(uint16_t mapW, uint16_t mapH) :
	m_mapWidth(mapW),
	m_mapHeight(mapH),
	m_plen(0)
{
	m_tileN = mapW * mapH;
	_m_init();
};
void Astar::_m_getTile(const uint16_t& id, uint16_t& tileX, uint16_t& tileY)
{
	tileY = id / m_mapWidth;
	tileX = id % (m_mapWidth);
}
int	 Astar::_m_h(Tile src, Tile des)
{
	uint16_t src_x, src_y;
	uint16_t des_x, des_y;
	_m_getTile(src, src_x, src_y);
	_m_getTile(des, des_x, des_y);
	return abs(src_x - des_x) + abs(src_y - des_y);
}
bool Astar::FindPath(Table& adjList, uint16_t src, uint16_t des)
{
	_m_init();
	int ord = 0;
	PriorityQueue<PathNode>* q = new PriorityQueue<PathNode>();
	Flag inq;
	q->Push(PathNode(src, 0, _m_h(src, des), ord++));
	PathNode u(0, 0, 0, 0);
	while (!q->IsEmpty())
	{
		u = q->Pop();
		if (u.tileId == des)
		{
			return true;
		}
		m_vis[u.tileId] = true;
		for (auto i : adjList[u.tileId])
		{
			if (!m_vis[i])
			{
				if (inq[i] && m_path[i].second > u.g + 1)
				{
					m_path[i].first = u.tileId;
					m_path[i].second = u.g + 1;
					q->DecreaseKey(PathNode(i,u.g+1,_m_h(i,des),ord++));
				}
				if(!inq[i])
				{
					q->Push(PathNode(i, u.g + 1, _m_h(i, des),ord++));
					m_path[i].first = u.tileId;
					m_path[i].second = u.g + 1;
					inq[i] = true;
				}
			}
		}
	}
	return false;
}
	
AstarPath& Astar::GetPath()
{
	return m_path;
}
Flag& Astar::GetSearchedNodes()
{
	return m_vis;
}

void Astar::_m_init()
{
	m_find = false;
	m_path.clear();
	for (auto i = 0; i < m_tileN; ++i)
		m_path.push_back(std::pair<uint16_t, uint16_t>(i, MAX));
	m_vis.reset();
}

Astar::PathNode::PathNode(uint16_t id, int pg, int ph, int ord) :
	tileId(id), g(pg), h(ph), order(ord)
{
}

bool Astar::PathNode::operator<(const PathNode & p) const
{
	return tileId < p.tileId;
}

bool Astar::PathNode::operator>(const PathNode & p) const
{
	return g + h == p.g + p.h ? 
		order < p.order : g + h > p.g + p.h;
}

Astar::PathNode& Astar::PathNode::operator=(const PathNode & p)
{
	tileId = p.tileId;
	g = p.g;
	h = p.h;
	return *this;
}