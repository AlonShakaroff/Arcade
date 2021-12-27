#pragma once
#include "ChessBoard.h"
#include "ChessStone.h"
#include "ChessCell.h"

//--------------------------------------------------------------------------------------------------------------------------------------------//
ChessBoard::ChessBoard() : Board(SIZE), m_curKingPosWhite(Position(0, 4)), m_curKingPosBlack(Position(7, 4)) 
{
	m_boardType = Board::BOARD_TYPE::CHESS;
	int row, col;

	for (row = 0; row < SIZE; row++)
	{
		for (col = 0; col < SIZE; col++)
		{
			m_board[row][col] = new ChessCell(row, col);
		}
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------//
bool ChessBoard::isKingSafe(Stone::PLAYER_ID playerID)
{
	Position curKingPos;

	if(playerID == Stone::PLAYER_ID::white)
	{
		curKingPos = getCurKingPosWhite();
	}
	else
	{
		curKingPos = getCurKingPosBlack();
	}

	int directionInt;
	int size = getSize();
	Position::DIRECTION direction;
	Position neighbourPos;


	//check King Threats
	if (playerID == Stone::PLAYER_ID::white)
	{
		for (directionInt = static_cast<int>(Position::DIRECTION::UP_LEFT); directionInt <= static_cast<int>(Position::DIRECTION::RIGHT); ++directionInt)
		{
			direction = static_cast<Position::DIRECTION>(directionInt);
			neighbourPos = curKingPos.getPosFromDirection(direction);

			if (neighbourPos.isInBoard(size) && isOccupied(neighbourPos))
			{
				Stone* neighbourStone = getStone(neighbourPos);
				const char neighbourSymbol = neighbourStone->getSymbol();
				if (getStone(neighbourPos)->getPlayerId() != playerID && (neighbourSymbol == 'k' || neighbourSymbol == 'K'))
					return false;
			}
		}
	}

	//check Knight Threats
	for (directionInt = static_cast<int>(Position::KNIGHT_DIRECTION::LEFT_DOWN); directionInt <= static_cast<int>(Position::KNIGHT_DIRECTION::DOWN_LEFT); ++directionInt)
	{
		Position::KNIGHT_DIRECTION direction = static_cast<Position::KNIGHT_DIRECTION>(directionInt);
		neighbourPos = curKingPos.getPosFromDirection(direction);

		if (neighbourPos.isInBoard(size) && isOccupied(neighbourPos))
		{
			Stone* neighbourStone = getStone(neighbourPos);
			const char neighbourSymbol = neighbourStone->getSymbol();
			if (neighbourStone->getPlayerId() != playerID && (neighbourSymbol == 'n' || neighbourSymbol == 'N'))
				return false;
		}
	}

	//check Pawn Threats - white
	if (playerID == Stone::PLAYER_ID::white)
	{
		for (directionInt = static_cast<int>(Position::DIRECTION::UP_LEFT); directionInt <= static_cast<int>(Position::DIRECTION::UP_RIGHT); ++directionInt)
		{
			direction = static_cast<Position::DIRECTION>(directionInt);
			neighbourPos = curKingPos.getPosFromDirection(direction);

			if (neighbourPos.isInBoard(size) && isOccupied(neighbourPos))
			{
				Stone* neighbourStone = getStone(neighbourPos);
				const char neighbourSymbol = neighbourStone->getSymbol();
				if (getStone(neighbourPos)->getPlayerId() != playerID && (neighbourSymbol == 'p' || neighbourSymbol == 'P'))
					return false;
			}
		}
	}
	//check Pawn Threats - black
	else
	{
		for (directionInt = static_cast<int>(Position::DIRECTION::DOWN_LEFT); directionInt <= static_cast<int>(Position::DIRECTION::DOWN_RIGHT); ++directionInt)
		{
			direction = static_cast<Position::DIRECTION>(directionInt);
			neighbourPos = curKingPos.getPosFromDirection(direction);

			if (neighbourPos.isInBoard(size) && isOccupied(neighbourPos))
			{
				Stone* neighbourStone = getStone(neighbourPos);
				const char neighbourSymbol = neighbourStone->getSymbol();
				if (getStone(neighbourPos)->getPlayerId() != playerID && (neighbourSymbol == 'p' || neighbourSymbol == 'P'))
					return false;
			}
		}
	}
	
	//check Vertical Threats
	for (directionInt = static_cast<int>(Position::DIRECTION::UP); directionInt <= static_cast<int>(Position::DIRECTION::RIGHT); ++directionInt)
	{
		direction = static_cast<Position::DIRECTION>(directionInt);
		Position prev = curKingPos;
		Position neighbourPos = prev.getPosFromDirection(direction);

		while (neighbourPos.isInBoard(size) && !isOccupied(neighbourPos))
		{
			prev = neighbourPos;
			neighbourPos = neighbourPos.getPosFromDirection(direction);
		}

		if (neighbourPos.isInBoard(size)) // neighbourPos is occupied
		{
			Stone* neighbourStone = getStone(neighbourPos);
			const char neighbourSymbol = neighbourStone->getSymbol();
			if (neighbourStone->getPlayerId() != playerID && (neighbourSymbol == 'r' || neighbourSymbol == 'R' || neighbourSymbol == 'q' || neighbourSymbol == 'Q'))
			{
				return false;
			}
		}
	}

	//check Diagonal Threats
	for (directionInt = static_cast<int>(Position::DIRECTION::UP_LEFT); directionInt <= static_cast<int>(Position::DIRECTION::DOWN_RIGHT); ++directionInt)
	{
		direction = static_cast<Position::DIRECTION>(directionInt);
		Position prev = curKingPos;
		Position neighbourPos = prev.getPosFromDirection(direction);

		while (neighbourPos.isInBoard(size) && !isOccupied(neighbourPos))
		{
			prev = neighbourPos;
			neighbourPos = neighbourPos.getPosFromDirection(direction);
		}

		if (neighbourPos.isInBoard(size)) // neighbourPos is occupied
		{
			Stone* neighbourStone = getStone(neighbourPos);
			const char neighbourSymbol = neighbourStone->getSymbol();
			if (neighbourStone->getPlayerId() != playerID && (neighbourSymbol == 'b' || neighbourSymbol == 'B' || neighbourSymbol == 'q' || neighbourSymbol == 'Q'))
			{
				return false;
			}
		}
	}

	//if King is Safe
	return true;
}
//-------------------------------------------------------------------------------------------------------------------------------------
ChessBoard::ChessBoard(const ChessBoard& other) : Board(other)
{
	*this = other;
}
//-------------------------------------------------------------------------------------------------------------------------------------
const ChessBoard& ChessBoard::operator=(const ChessBoard& other)
{
	if (this != &other)
	{
		int size = m_size;
		m_board.resize(size);

		int row, col;

		for (row = 0; row < size; ++row)
		{
			m_board[row].resize(size);
			for (col = 0; col < size; ++col)
			{
				m_board[row][col] = new ChessCell(static_cast<const ChessCell&>(*(other.m_board[row][col])));
			}
		}
	}

	return *this;
}
//-------------------------------------------------------------------------------------------------------------------------------------
void ChessBoard::save(ostream& out) const
{
	Board::save(out);
	m_curKingPosWhite.save(out);
	m_curKingPosBlack.save(out);
}
//-------------------------------------------------------------------------------------------------------------------------------------
void ChessBoard::load(istream& in)
{
	m_curKingPosWhite.load(in);
	m_curKingPosBlack.load(in);
}
//-------------------------------------------------------------------------------------------------------------------------------------