#include "Cell.h"
#include "CheckersStone.h"
#include "Amazon.h"
#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"
#include <typeinfo>
#include <iostream>
using namespace std;

//-------------------------------------------------------------------------------------------------------------------------------------
Cell::Cell(const Cell& other) : m_StoneP(nullptr)
{
	*this = other;
}
//-------------------------------------------------------------------------------------------------------------------------------------
Cell::Cell(Cell&& other) : m_StoneP(nullptr)
{
	*this = move(other);
}
//-------------------------------------------------------------------------------------------------------------------------------------
const Cell& Cell::operator=(const Cell& other)
{
	if (this != &other)
	{
		m_position = other.m_position;
		m_isOccupied = other.m_isOccupied;
	}

	return *this;
}
//-------------------------------------------------------------------------------------------------------------------------------------
const Cell& Cell::operator=(Cell&& other)
{
	if (this != &other)
	{
		m_position = other.m_position;
		m_isOccupied = other.m_isOccupied;
		
		delete m_StoneP;
		m_StoneP = other.getStoneP();
		other.m_StoneP = nullptr;
	}

	return *this;
}
//-------------------------------------------------------------------------------------------------------------------------------------
Cell::~Cell()
{
	delete m_StoneP;
}
//-------------------------------------------------------------------------------------------------------------------------------------
void Cell::save(ostream& out) const
{
	m_position.save(out);
	out.write(rcastcc(&m_isOccupied), sizeof(m_isOccupied));
	
	if (m_StoneP)
	{
		Stone::STONE_TYPE stoneType = m_StoneP->getStoneType();
		out.write(rcastcc(&stoneType), sizeof(stoneType));
		m_StoneP->save(out);
	}
	else
	{
		Stone::STONE_TYPE stoneType = Stone::STONE_TYPE::NO_STONE;
		out.write(rcastcc(&stoneType), sizeof(stoneType));
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------
void Cell::load(istream& in)
{
	m_position.load(in);
	in.read(rcastc(&m_isOccupied), sizeof(m_isOccupied));
	
	Stone::STONE_TYPE stoneType;
	in.read(rcastc(&stoneType), sizeof(stoneType));
	
	switch (stoneType)
	{
	case Stone::STONE_TYPE::CHECKERS_STONE:
		m_StoneP = new CheckersStone(in);
		break;
	case Stone::STONE_TYPE::AMAZON:
		m_StoneP = new Amazon(in);
		break;
	case Stone::STONE_TYPE::BISHOP:
		m_StoneP = new Bishop(in);
		break;
	case Stone::STONE_TYPE::KING:
		m_StoneP = new King(in);
		break;
	case Stone::STONE_TYPE::KNIGHT:
		m_StoneP = new Knight(in);
		break;
	case Stone::STONE_TYPE::PAWN:
		m_StoneP = new Pawn(in);
		break;
	case Stone::STONE_TYPE::QUEEN:
		m_StoneP = new Queen(in);
		break;
	case Stone::STONE_TYPE::ROOK:
		m_StoneP = new Rook(in);
		break;
	case Stone::STONE_TYPE::NO_STONE:
		m_StoneP = nullptr;
		break;
	}
	
}
//-------------------------------------------------------------------------------------------------------------------------------------