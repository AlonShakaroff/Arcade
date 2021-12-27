#pragma once
#include <iostream>
using namespace std;

#include "Stone.h"
#include "Board.h"
#include "Game.h"

//-------------------------------------------------------------------------------------------------------------------------------------
Stone::Stone(int row, int col)
{
	Position pos(row, col);
	setPosition(pos);
}
//-------------------------------------------------------------------------------------------------------------------------------------
Stone::Stone(istream& in)
{
	load(in);
}
//-------------------------------------------------------------------------------------------------------------------------------------
void Stone::displayValidMoves()
{
	int i;
	int validMovesInd = getValidMovesIndex();

	if (validMovesInd == 0)
	{
		return;
	}

	for (i = 0; i < m_valid_moves_index; ++i)
	{
		cout << "(" << getValidMoves()[i].getRow() + 1 << "," << getValidMoves()[i].getCol() + 1 << ")" << " ";
	}
	cout << endl;
}
//-------------------------------------------------------------------------------------------------------------------------------------
void Stone::moveStoneTo(const Position& to)
{
	setPosition(to);
}
//-------------------------------------------------------------------------------------------------------------------------------------
void Stone::addValidMove(const Position& newPos)
{
	m_valid_moves[m_valid_moves_index] = newPos;
	++m_valid_moves_index;
}
//-------------------------------------------------------------------------------------------------------------------------------------
int Stone::getAmountOfValidMoves()
{
	if (m_valid_moves_index == 0)
		return 0;
	else
		return m_valid_moves_index + 1;
}
//-------------------------------------------------------------------------------------------------------------------------------------
const int Stone::getAmountOfValidMoves() const
{
	if (m_valid_moves_index == 0)
		return 0;
	else
		return m_valid_moves_index + 1;
}
//-------------------------------------------------------------------------------------------------------------------------------------
Stone::Stone(const Stone& other)
{
	*this = other;
}
//-------------------------------------------------------------------------------------------------------------------------------------
Stone::Stone(Stone&& other)
{
	*this = move(other);
}
//-------------------------------------------------------------------------------------------------------------------------------------
const Stone& Stone::operator=(const Stone& other)
{
	if (this != &other)
	{
		int amountOfValidMoves = other.getAmountOfValidMoves();
		m_position = other.m_position;
		m_valid_moves_index = other.m_valid_moves_index;
		m_playerID = other.m_playerID;
		m_symbol = other.m_symbol;
		m_stoneType = other.m_stoneType;

		for (int i = 0; i < amountOfValidMoves; i++)
		{
			m_valid_moves[i] = other.m_valid_moves[i];
		}
	}

	return *this;
}
//-------------------------------------------------------------------------------------------------------------------------------------
const Stone& Stone::operator=(Stone&& other)
{
	if (this != &other)
	{
		m_position = other.m_position;
		m_valid_moves_index = other.m_valid_moves_index;
		m_playerID = other.m_playerID;
		m_symbol = other.m_symbol;
		m_stoneType = other.m_stoneType;
		m_valid_moves = other.m_valid_moves;
	}

	return *this;
}
//-------------------------------------------------------------------------------------------------------------------------------------
void Stone::save(ostream& out) const
{
	m_position.save(out);
	out.write(rcastcc(&m_playerID), sizeof(m_playerID));
	out.write(rcastcc(&m_symbol), sizeof(m_symbol));
}
//-------------------------------------------------------------------------------------------------------------------------------------
void Stone::load(istream& in)
{
	m_position.load(in);

	in.read(rcastc(&m_playerID), sizeof(m_playerID));
	in.read(rcastc(&m_symbol), sizeof(m_symbol));
}
//-------------------------------------------------------------------------------------------------------------------------------------