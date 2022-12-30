#pragma once
#include <vector>
#include "Cell.h"

using namespace std;

typedef vector<vector<Cell>> matrix;

class Map
{
	matrix map;
	Cell start;
	Cell finish;
public:
	Map() {}
	Map(string fileName);

	void MapCodePrint();
};

