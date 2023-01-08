#pragma once
#include <vector>
#include "Cell.h"

typedef std::vector<vector<Cell>> matrix;

class Map
{
	matrix map;
	Cell start;
	Cell finish;
	vector<Cell> path;
	bool isFinish;
public:
	Map() {}
	Map(string fileName);

	void CodePrint();
	void Print();
	bool CreateWave();
	void CreatePath();
};

