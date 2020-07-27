#pragma once
#include "Cell.h"
#include "GameObject.h"

#define CELL_WIDTH			/*270*/265
#define CELL_HEIGHT			192
#define MAX_MAP_HEIGHT		768
#define MAX_MAP_HEIGHT		1600

class CCells
{
	// cells[column][row]
	vector<vector<LPCELL>> cells;

	int rows;			// Number of cells in a column
	int columns;		// Number of cells in a row

	

	int cellHeight;
	int cellWidth;

public:
	int firstCellColumn = 0, firstCellRow = 0;
	int lastCellColumn = 0, lastCellRow = 0;

	void Init();
	void Classify(LPGAMEOBJECT obj);
	void GetCellsContainRectangle(float const &left, float const &top,
		float const &right, float const &bottom,
		int &firstCellColumn, int &firstCellRow,
		int &lastCellColumn, int &lastCellRow);

	// Get all the objects in cells that containing the given rectangle
	void GetObjectsInRectangle(float const &left, float const &top,
		float const &right, float const &bottom,
		vector<LPGAMEOBJECT> &objects);

	void SetFirstCellColumn(int &cellcolumn) { this->firstCellColumn = cellcolumn; }
	void SetLastCellColumn(int &cellcolumn) { this->lastCellColumn = cellcolumn; }
	void SetFirstCellRow(int &cellrow) { this->firstCellRow = cellrow; }
	void SetLastCellRow(int &cellrow) { this->lastCellRow = cellrow; }
};

