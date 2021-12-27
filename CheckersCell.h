#pragma once
#include "Cell.h"

class CheckersCell :  public Cell
{
public:
	CheckersCell(int row, int col);
	CheckersCell(const CheckersCell& other); // cpy ctor
	CheckersCell(istream& in) : Cell(in) {}	 // load ctor
	const CheckersCell& operator=(const CheckersCell& other);
};

