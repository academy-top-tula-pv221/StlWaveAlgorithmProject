#pragma once
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

const char WallChar = 178;

enum CellType
{
	Space = -1,
	Wall = -3,
	Start = 0,
	Finish = -2
};

class Cell
{
	int row;
	int col;
	int value;
public:
	Cell();
	Cell(int row, int col, int value = CellType::Space);
	int& Row();
	int& Col();
	int& Value();
	friend std::ostream& operator<<(std::ostream& out, const Cell& cell);
};

//typedef vector<Cell> cvector;


