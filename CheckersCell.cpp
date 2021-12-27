#include "CheckersCell.h"
#include "CheckersStone.h"
#include "Cell.h"

//-------------------------------------------------------------------------------------------------------------------------------------
CheckersCell::CheckersCell(int row, int col) : Cell(row,col)
{
	if (row == 3 || row == 4)
		return;
	else if (row % 2 == col % 2)
	{
		m_isOccupied = true;
		m_StoneP = new CheckersStone(row, col);
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------
CheckersCell::CheckersCell(const CheckersCell& other) : Cell(other)
{
	*this = other;
}
//-------------------------------------------------------------------------------------------------------------------------------------
const CheckersCell& CheckersCell::operator=(const CheckersCell& other)
{
	if (this != &other)
	{
		delete m_StoneP;
		m_StoneP = new CheckersStone(static_cast<const CheckersStone&>(*(other.m_StoneP)));
	}

	return *this;
}
//-------------------------------------------------------------------------------------------------------------------------------------
