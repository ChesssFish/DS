#ifndef CHASE_APPLICATION_A_STAR_H
#define CHASE_APPLICATION_A_STAR_H
#include"ChaseDef.h"
#include<vector>
#include<bitset>
class Astar
{
public:
	Astar(Tile mapW, Tile mapH);
	bool FindPath(Table& adjList, Tile src, Tile des);
	AstarPath& GetPath();
	Flag& GetSearchedNodes();
private:
	class PathNode
	{
	public:
		PathNode(Tile id, int f, int h, int order);
		bool operator<(const PathNode& p)const;
		bool operator>(const PathNode& p)const;
		PathNode& operator=(const PathNode& p);
		Tile tileId;
		int g;
		int h;
		int order;
	};
	AstarPath m_path;
	int m_plen;
	Tile m_mapWidth;
	Tile m_mapHeight;
	Flag m_vis;
	int _m_h(Tile src, Tile des);
	int m_tileN;
	bool m_find;
	void _m_getTile(const Tile& id, Tile& tileX, Tile& tileY);
	void _m_init();
};
#endif