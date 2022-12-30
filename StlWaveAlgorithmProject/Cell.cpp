#include "Cell.h"

Cell::Cell() : row{0}, col{0}, value{CellType::Space} {}

Cell::Cell(int row, int col, int value)
	: row{ row }, col{ col }, value{ value } {}

int& Cell::Row() { return row; }
int& Cell::Col() { return col; }
int& Cell::Value() { return value; }

std::ostream& operator<<(std::ostream& out, const Cell& cell)
{
	out << "[" << cell.row << "," << cell.col << "]";
	return out;
}
