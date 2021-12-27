#include <iostream>
#include "AmazonsCell.h"
#include "AmazonBoard.h"
#include "Board.h"
#include "Amazon.h"
using namespace std;

//-------------------------------------------------------------------------------------------------------------------------------------
AmazonsCell::AmazonsCell(int row, int col) : Cell(row,col)
{
	if ((row == 0 && (col == 3 || col == 6)) || (row == 3 && (col == 0 || col == 9)) || (row == 6 && (col == 0 || col == 9)) || (row == 9 && (col == 3 || col == 6)))
	{
		m_isOccupied = true;
		m_StoneP = new Amazon(row, col);

	}
	setPosition(row, col);
}
//-------------------------------------------------------------------------------------------------------------------------------------
AmazonsCell::AmazonsCell(istream& in) : Cell(in)
{
	load(in);
}
//-------------------------------------------------------------------------------------------------------------------------------------
void AmazonsCell::addThreat(const Position& newThreat)
{
	m_threats[++m_threats_index] = newThreat;
}
//-------------------------------------------------------------------------------------------------------------------------------------
void AmazonsCell::displayThreats()
{
	int i;
	int threatsInd = getThreatsIndex();

	if (threatsInd == 0)
	{
		return;
	}

	for (i = 0; i < threatsInd; ++i)
	{
		cout << "(" << getThreats()[i].getRow() + 1 << "," << getThreats()[i].getCol() + 1 << ")" << " ";
	}
	cout << endl;
}
//-------------------------------------------------------------------------------------------------------------------------------------
void AmazonsCell::generateThreats(AmazonBoard& board)
{
	int directionInt;
	for (directionInt = static_cast<int>(Position::DIRECTION::UP_LEFT); directionInt <= static_cast<int>(Position::DIRECTION::RIGHT); ++directionInt)
	{
		Position::DIRECTION direction = static_cast<Position::DIRECTION>(directionInt);
		Position prev = getPosition();
		Position neighbourPos = prev.getPosFromDirection(direction);

		while (neighbourPos.isInBoard(board.getSize()) && !board.isOccupied(neighbourPos))
		{
			addThreat(neighbourPos);
			prev = neighbourPos;
			neighbourPos = neighbourPos.getPosFromDirection(direction);
		}
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------
AmazonsCell::AmazonsCell(const AmazonsCell& other) : Cell(other)
{
	*this = other;
}
//-------------------------------------------------------------------------------------------------------------------------------------
const AmazonsCell& AmazonsCell::operator=(const AmazonsCell& other)
{
	if (this != &other)
	{
		delete m_StoneP;
		m_StoneP = new Amazon(static_cast<const Amazon&>(*(other.m_StoneP)));
	}

	return *this;
}
//-------------------------------------------------------------------------------------------------------------------------------------
void AmazonsCell::save(ostream& out) const
{
	Cell::save(out);
	int threatssSize = m_threats.size();
	out.write(rcastcc(&threatssSize), sizeof(threatssSize));
	for (int i = 0; i < threatssSize; ++i)
	{
		m_threats[i].save(out);
	}
	out.write(rcastcc(&m_threats_index), sizeof(m_threats_index));
}
//-------------------------------------------------------------------------------------------------------------------------------------
void AmazonsCell::load(istream& in)
{
	int threatssSize;
	in.read(rcastc(&threatssSize), sizeof(threatssSize));
	for (int i = 0; i < threatssSize; ++i)
	{
		m_threats[i].load(in);
	}
	in.read(rcastc(&m_threats_index), sizeof(m_threats_index));
}
//-------------------------------------------------------------------------------------------------------------------------------------
