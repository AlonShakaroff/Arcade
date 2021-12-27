#pragma once
#include "ChessCell.h"
#include "Pawn.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Knight.h"

//-------------------------------------------------------------------------------------------------------------------------------------
ChessCell::ChessCell(int row, int col) : Cell(row,col)
{
	if (row >= 2 && row <= 5)
		return;
	//else
	m_isOccupied = true;

	if (row == 1 || row == 6)
	{
		m_StoneP = new Pawn(row,col);
	}
	else if (col == 0 || col == 7)
	{
		m_StoneP = new Rook(row, col);
	}
	else if (col == 1 || col == 6)
	{
		m_StoneP = new Knight(row, col);
	}
	else if (col == 2 || col == 5)
	{
		m_StoneP = new Bishop(row, col);
	}
	else if (col == 3)
	{
		m_StoneP = new Queen(row, col);
	}
	else
	{
		m_StoneP = new King(row, col);
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------
ChessCell::ChessCell(const ChessCell& other) : Cell(other)
{
	*this = other;
}
//-------------------------------------------------------------------------------------------------------------------------------------
const ChessCell& ChessCell::operator=(const ChessCell& other)
{
	if (this != &other)
	{
		delete m_StoneP;
		char symbol = other.m_StoneP->getSymbol();
		
		if (symbol == 'p' || symbol == 'P')
			m_StoneP = new Pawn(static_cast<const Pawn&>(*(other.m_StoneP)));

		if (symbol == 'r' || symbol == 'R')
			m_StoneP = new Rook(static_cast<const Rook&>(*(other.m_StoneP)));
			
		if (symbol == 'n' || symbol == 'N')
			m_StoneP = new Knight(static_cast<const Knight&>(*(other.m_StoneP)));
			
		if (symbol == 'b' || symbol == 'B')
			m_StoneP = new Bishop(static_cast<const Bishop&>(*(other.m_StoneP)));
			
		if (symbol == 'q' || symbol == 'Q')
			m_StoneP = new Queen(static_cast<const Queen&>(*(other.m_StoneP)));
			
		if (symbol == 'k' || symbol == 'K')
			m_StoneP = new King(static_cast<const King&>(*(other.m_StoneP)));
	}

	return *this;
}
//-------------------------------------------------------------------------------------------------------------------------------------
