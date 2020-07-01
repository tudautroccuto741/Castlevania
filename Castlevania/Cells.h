#pragma once
#include "Cell.h"
#include "GameObject.h"

#define CELL_WIDTH			270/*270*/
#define CELL_HEIGHT			192/*224*/

class CCells
{
	// cells[column][row]
	vector<vector<LPCELL>> cells;

	int rows;			// Number of cells in a column
	int columns;		// Number of cells in a row

	int cellHeight;
	int cellWidth;

public:

	void Init(/*int cellWidth, int cellHeight*/);
	void Classify(LPGAMEOBJECT obj);
	void GetCellsContainRectangle(float const &left, float const &top,
		float const &right, float const &bottom,
		int &firstCellColumn, int &firstCellRow,
		int &lastCellColumn, int &lastCellRow);

	// Get all the objects in cells that containing the given rectangle
	void GetObjectsInRectangle(float const &left, float const &top,
		float const &right, float const &bottom,
		vector<LPGAMEOBJECT> &objects);
};

