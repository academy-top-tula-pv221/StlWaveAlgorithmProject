#include <fstream>
#include "Map.h"

Map::Map(string fileName)
{
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
			case 'S': code = CellType::Start; break;
			case 'f':
			case 'F': code = CellType::Finish; break;
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

void Map::MapCodePrint()
{
	cout << "\n";
	for (auto line : map)
	{
		for (auto item : line)
			cout << setw(2) << item.Value();
		cout << "\n";
	}
}
