#include <fstream>
#include <algorithm>
#include "Map.h"

vector<Cell> diff{ {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

Map::Map(string fileName)
{
	this->path = vector<Cell>();
	this->isFinish = false;

	fstream fileMap;
	fileMap.open(fileName, ios::in);
	
	//int sizeStr = 1024;
	//char* str = new char[sizeStr] {};
	

	int row{};
	while (!fileMap.eof())
	{
		string str(1024, '\0');

		fileMap.getline(str.data(), str.length());
		int col{};
		vector<Cell> line;
		while (str[col])
		{
			int code{};
			switch (str[col])
			{
			case '#': code = CellType::Wall; break;
			case ' ': code = CellType::Space; break;
			case 's':
			case 'S': 
				code = CellType::Start;
				start = Cell(row, col);
				break;
			case 'f':
			case 'F':
				code = CellType::Finish; 
				finish = Cell(row, col);
				break;
			default:
				break;
			}
			line.push_back(Cell(row, col, code));
			col++;
		}
		map.push_back(line);
		row++;
	}
	fileMap.close();
}

void Map::CodePrint()
{
	cout << "\n";
	for (auto line : map)
	{
		for (auto item : line)
			cout << setw(2) << item.Value();
		cout << "\n";
	}
}

void Map::Print()
{
	int rows = map.size();
	int cols = map[0].size();
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			switch ((CellType)map[row][col].Value())
			{
			case CellType::Space:
				cout << setw(2) << " "; break;
			case CellType::Wall:
				cout << WallChar << WallChar; break;
			case CellType::Start:
				cout << setw(2) << "S"; break;
			case CellType::Finish:
				cout << setw(2) << "F"; break;
			default:
				//bool isPath{ false };
				if (path.size())
				{
					auto result = find_if(path.begin(), path.end(), [row, col](auto cell) {
						return row == cell.Row() && col == cell.Col();
						});
					if (result != path.end())
						cout << setw(2) << map[row][col].Value();
					else
						cout << setw(2) << " ";
				}
				else
					cout << setw(2) << map[row][col].Value();
				
				break;
			}
		}
		cout << "\n";
	}
}

bool Map::CreateWave()
{
	vector<Cell> fronts[2];
	bool indexCurrentFront{ false };
	int numberCurrentFront{};

	fronts[indexCurrentFront].push_back(start);
	this->isFinish = false;
	while (true)
	{
		fronts[!indexCurrentFront].clear();
		numberCurrentFront++;

		for (auto cell : fronts[indexCurrentFront])
		{
			int row = cell.Row();
			int col = cell.Col();

			for (int i = 0; i < diff.size(); i++)
			{
				int drow = row + diff[i].Row();
				int dcol = col + diff[i].Col();

				if (map[drow][dcol].Value() == CellType::Finish)
				{
					map[drow][dcol].Value() = numberCurrentFront;
					isFinish = true;
					break;
				}

				if (map[drow][dcol].Value() == CellType::Space)
				{
					map[drow][dcol].Value() = numberCurrentFront;
					fronts[!indexCurrentFront].push_back(Cell(drow, dcol));
				}
			}
			if (this->isFinish) break;
		}
		if (this->isFinish) break;
		if (!fronts[!indexCurrentFront].size())
			break;
		indexCurrentFront = !indexCurrentFront;

		//this->Print();
		//cout << "\n";
	}
	return this->isFinish;
}

void Map::CreatePath()
{
	if (!this->isFinish) return;

	path.clear();
	path.push_back(finish);
	int row = finish.Row();
	int col = finish.Col();
	int numberWave = map[row][col].Value();

	while (numberWave)
	{
		for (int i = 0; i < diff.size(); i++)
		{
			row = path.back().Row();
			col = path.back().Col();

			int drow = row + diff[i].Row();
			int dcol = col + diff[i].Col();

			if (map[drow][dcol].Value() == numberWave - 1)
			{
				path.push_back(Cell(drow, dcol));
				break;
			}
		}
		numberWave--;
	}

	for_each(path.rbegin(), path.rend(), [](auto cell) {
		cout << cell << " ";
		});
	cout << "\n";
}
