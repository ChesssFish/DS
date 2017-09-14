#pragma once
#ifndef CHASE_APPLICATION_CHASE_MAP_H
#define CHASE_APPLICATION_CHASE_MAP_H
#define MAPXN 50
#define MAPYN 50
#include"ChaseDef.h"
#include"wx/wx.h"
#include<vector>
#include<bitset>
#include"Astar.h"
#include"NavGenerator.h"
class ChaseMap
{
public:
	ChaseMap();
	int GetID(int x, int y);
	void ChageState(int x, int y);
	void SetPlayer(int x, int y);
	wxPoint GetPlayer();
	void SetChaser(int x, int y);
	wxPoint GetChaser();
	bool IsBlock(int x, int y);
	bool IsPlayer(int x, int y);
	bool IsChaser(int x, int y);
	void Load(int map_id);
	void GenerateAdjList();
	void GenerateNavTable();
	Table& GetNavTable();
	void TranslatePlayer(int dx, int dy);
	void TranslateChaser(int dx, int dy);
	bool Chase();
	AstarPath& GetPath();
	Flag& GetSearchedNodes();
private:
	int m_playerX;
	int m_playerY;
	int m_chaserX;
	int m_chaserY;
	int m_mapxn;
	int m_mapyn;
	Astar astar;
	NavGenerator m_nav;
	Table m_adjList;
	std::bitset<MAPXN * MAPYN> m_mapBlock;
};
#endif