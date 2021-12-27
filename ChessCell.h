#pragma once
#include "Cell.h"
#include <iostream>
class ChessCell : public Cell
{
public:
	ChessCell(int row, int col);			// ctor
	ChessCell(const ChessCell& other);		// cpy ctor
	ChessCell(istream& in) : Cell(in) {}	// load ctor
	const ChessCell& operator=(const ChessCell& other);
};

