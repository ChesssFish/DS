#ifndef CHASE_APPLICATION_CHASE_DEF_H
#define CHASE_APPLICATION_CHASE_DEF_H
#include<vector>
#include<bitset>
typedef uint16_t							Tile;
typedef std::vector<Tile>					TileVector;
typedef std::vector<TileVector>				Table;
typedef std::pair<Tile, int>				AstarPathNode;
typedef std::vector<AstarPathNode>			AstarPath;
static const int MAX = std::numeric_limits<Tile>::max();
typedef std::bitset<MAX>					Flag;
#endif
