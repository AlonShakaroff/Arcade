#pragma once
#include "ChessBoard.h"
#include "Pawn.h"

//-------------------------------------------------------------------------------------------------------------------------------------
Pawn::Pawn(int row, int col) : ChessStone(row, col) , m_isFirstMove(true)
{
	m_stoneType = Stone::STONE_TYPE::PAWN;
	m_valid_moves.resize(MAX_VALID_MOVES);
	if (row <= 1)
	{
		setPlayerId(PLAYER_ID::white);
		setSymbol('p');
	}
	else
	{
		setPlayerId(PLAYER_ID::black);
		setSymbol('P');
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------
Pawn::Pawn(istream& in) : ChessStone(in)
{
	m_valid_moves.resize(MAX_VALID_MOVES);
	load(in);
}
//-------------------------------------------------------------------------------------------------------------------------------------
void Pawn::generateValidMoves(ChessBoard& board)
{
	int directionInt;
	int size = board.getSize();
	Position::DIRECTION direction;
	Position neighbourPos;
	
	// white pawn
	if (getPlayerId() == PLAYER_ID::white)
	{
		// check eating directions
		for (directionInt = static_cast<int>(Position::DIRECTION::UP_LEFT); directionInt <= static_cast<int>(Position::DIRECTION::UP_RIGHT); ++directionInt)
		{
			direction = static_cast<Position::DIRECTION>(directionInt);
			neighbourPos = getPosition().getPosFromDirection(direction);

			if (neighbourPos.isInBoard(size) && board.isOccupied(neighbourPos))
			{
				if (board.getStone(neighbourPos)->getPlayerId() != this->getPlayerId())
				{
					if (simulateIsMoveValid(board, getPosition(), neighbourPos))
					{
						addValidMove(neighbourPos);
						static_cast<ChessStone*>(board.getStone(neighbourPos))->addRisk(getPosition()); // adding risk to threatned stone
					}
				}
			}
		}

		// check UP
		direction = Position::DIRECTION::UP;
		neighbourPos = getPosition().getPosFromDirection(direction);

		if (neighbourPos.isInBoard(size) && !board.isOccupied(neighbourPos))
		{
			if (simulateIsMoveValid(board, getPosition(), neighbourPos))
			{
				addValidMove(neighbourPos);
			}
		}
	}
	// black pawn
	else
	{
		// check eating directions
		for (directionInt = static_cast<int>(Position::DIRECTION::DOWN_LEFT); directionInt <= static_cast<int>(Position::DIRECTION::DOWN_RIGHT); ++directionInt)
		{
			direction = static_cast<Position::DIRECTION>(directionInt);
			neighbourPos = getPosition().getPosFromDirection(direction);

			if (neighbourPos.isInBoard(size) && board.isOccupied(neighbourPos))
			{
				if (board.getStone(neighbourPos)->getPlayerId() != this->getPlayerId())
				{
					if (simulateIsMoveValid(board, getPosition(), neighbourPos))
					{
						addValidMove(neighbourPos);
						static_cast<ChessStone*>(board.getStone(neighbourPos))->addRisk(getPosition()); // adding risk to threatned stone
					}
				}
			}
		}

		// check DOWN
		direction = Position::DIRECTION::DOWN;
		neighbourPos = getPosition().getPosFromDirection(direction);

		if (neighbourPos.isInBoard(size) && !board.isOccupied(neighbourPos))
		{
			if (simulateIsMoveValid(board, getPosition(), neighbourPos))
			{
				addValidMove(neighbourPos);
			}
		}
	}

	// check first move
	if (getIsFirstMove())
	{
		Position furtherNeighbour = neighbourPos.getPosFromDirection(direction);
		if (furtherNeighbour.isInBoard(size) && !board.isOccupied(furtherNeighbour))
		{
			if (simulateIsMoveValid(board, getPosition(), furtherNeighbour))
			{
				addValidMove(furtherNeighbour);
			}
		}
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------
void Pawn::save(ostream& out) const
{
	Stone::save(out);
	out.write(rcastcc(&m_isFirstMove), sizeof(m_isFirstMove));
}
//-------------------------------------------------------------------------------------------------------------------------------------
void Pawn::load(istream& in)
{
	in.read(rcastc(&m_isFirstMove), sizeof(m_isFirstMove));
}
//-------------------------------------------------------------------------------------------------------------------------------------
