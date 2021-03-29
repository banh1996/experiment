#ifndef TREASUREMAP_H
#define TREASUREMAP_H
#include <fstream>
#include <string>
#include <map>
#define N 8


class TreasureMap						// Represents TreasureMap class' data and function members
{
public:
	TreasureMap(std::ifstream&);		// Constructor: takes file object and reads treasure map from file
	void PrintMap();					// Displays the treasure map and its state
	void FindTreasure(int, int, bool&);	// Recursive function that finds the treasure (ints: row, then column)
private:
	char tmap[10][10];					// 2D array of treasure map - outer columns and rows not traversable
	int maxRows; 						// Maximum number of rows in play area - excludes boundaries
	int maxCols; 						// Maximum number of columns in play area - excludes boundaries
	std::string xplor;					// 4-element string dictating order of map exploration (see specifications)
	std::pair<int,int> getMove(char);	// returns a pair (row, then column offset from current cell) 
};

#endif
