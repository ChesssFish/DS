#ifndef CHASE_APPLICATION_NAVGENERATOR_H
#define CHASE_APPLICATION_NAVGENERATOR_H
#include "ChaseDef.h"
#include <vector>
class NavGenerator
{
public:
	NavGenerator() {};
	void GenerateNavTable(Table& adjList);
	Table& GetNavTable();
private:
	Table NavTable;
	TileVector path;
	void _bfs(const Tile& src, const Table& adjList);
	void _generateTableRow(const int& row, const int& tileN);
};
#endif
