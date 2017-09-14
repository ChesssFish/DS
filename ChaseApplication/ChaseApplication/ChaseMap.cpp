#include"ChaseMap.h"
ChaseMap::ChaseMap()
	:astar(MAPXN, MAPYN)
{
	m_mapBlock.reset();
	SetPlayer(MAPXN - 1, MAPYN - 1);
	SetChaser(0, 0);
}
int ChaseMap::GetID(int tileX, int tileY)
{
	return tileY * MAPXN + tileX;
}
void ChaseMap::ChageState(int tileX, int tileY)
{
	int tileID = GetID(tileX, tileY);
	m_mapBlock[tileID] = !m_mapBlock[tileID];
}

bool ChaseMap::IsBlock(int tileX, int tileY)
{
	return m_mapBlock[GetID(tileX, tileY)];
}
void ChaseMap::SetPlayer(int tileX, int tileY)
{
	m_playerX = tileX;
	m_playerY = tileY;
}
wxPoint ChaseMap::GetPlayer()
{
	return wxPoint(m_playerX, m_playerY);
}
void ChaseMap::SetChaser(int tileX, int tileY)
{
	m_chaserX = tileX;
	m_chaserY = tileY;
}
wxPoint ChaseMap::GetChaser()
{
	return wxPoint(m_chaserX, m_chaserY);
}

bool ChaseMap::IsPlayer(int tileX, int tileY)
{
	return (tileX == m_playerX) && (tileY == m_playerY);
}
bool ChaseMap::IsChaser(int tileX, int tileY)
{
	return (tileX == m_chaserX) && (tileY == m_chaserY);
}

void ChaseMap::TranslateChaser(int dx, int dy)
{
	if (m_chaserX + dx > MAPXN - 1 || m_chaserX + dx < 0)return;
	if (m_chaserY + dy > MAPYN - 1 || m_chaserY + dy < 0)return;
	if (!IsBlock(m_chaserX + dx, m_chaserY + dy))
	{
		m_chaserX += dx;
		m_chaserY += dy;
	}
}
void ChaseMap::TranslatePlayer(int dx, int dy)
{
	if (m_playerX + dx > MAPXN - 1 || m_playerX + dx < 0)return;
	if (m_playerY + dy > MAPYN - 1 || m_playerY + dy < 0)return;
	if (!IsBlock(m_playerX + dx, m_playerY + dy))
	{
		m_playerX += dx;
		m_playerY += dy;
	}
}

void ChaseMap::GenerateAdjList()
{
	m_adjList.clear();
	m_adjList.resize(MAPXN * MAPYN);
	for (int i = 0; i < MAPXN; ++i)
	{
		for (int j = 0; j < MAPYN; ++j)
		{
			int tileID = GetID(i, j);
			if (m_mapBlock[tileID]) continue;
			if (j -1 >= 0 && !m_mapBlock[GetID(i, j - 1)])
			{
				m_adjList[tileID].push_back(GetID(i, j - 1));
			}
			if (j + 1 < MAPYN && !m_mapBlock[GetID(i, j + 1)])
			{
				m_adjList[tileID].push_back(GetID(i, j + 1));
			}
			if (i - 1 >= 0 && !m_mapBlock[GetID(i - 1, j)])
			{
				m_adjList[tileID].push_back(GetID(i - 1, j));
			}
			if (i + 1 < MAPXN && !m_mapBlock[GetID(i + 1, j)])
			{
				m_adjList[tileID].push_back(GetID(i + 1, j));
			}
		}
	}
}

void ChaseMap::GenerateNavTable()
{
	m_nav.GenerateNavTable(m_adjList);
}

Table & ChaseMap::GetNavTable()
{
	return m_nav.GetNavTable();
}

bool ChaseMap::Chase()
{
	uint16_t src = GetID(m_chaserX, m_chaserY);
	uint16_t des = GetID(m_playerX, m_playerY);
	return astar.FindPath(m_adjList, src, des);
}
AstarPath& ChaseMap::GetPath()
{
	return astar.GetPath();
}
std::bitset<MAX>& ChaseMap::GetSearchedNodes()
{
	return astar.GetSearchedNodes();
}