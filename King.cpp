#pragma once
#include "ChessBoard.h"
#include "King.h"

//-------------------------------------------------------------------------------------------------------------------------------------
King::King(int row, int col) : ChessStone(row, col)
{
	m_stoneType = Stone::STONE_TYPE::KING;
	m_valid_moves.resize(MAX_VALID_MOVES);
	if (row <= 1)
	{
		setPlayerId(PLAYER_ID::white);
		setSymbol('k');
	}
	else
	{
		setPlayerId(PLAYER_ID::black);
		setSymbol('K');
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------
void King::generateValidMoves(ChessBoard& board)
{
	int directionInt;
	int size = board.getSize();
	for (directionInt = static_cast<int>(Position::DIRECTION::UP_LEFT); directionInt <= static_cast<int>(Position::DIRECTION::RIGHT); ++directionInt)
	{
		Position::DIRECTION direction = static_cast<Position::DIRECTION>(directionInt);
		Position neighbourPos = getPosition().getPosFromDirection(direction);

		if (neighbourPos.isInBoard(size) && !board.isOccupied(neighbourPos))
		{
			if (simulateIsMoveValid(board, getPosition(), neighbourPos))
				addValidMove(neighbourPos);
		}

		else if (neighbourPos.isInBoard(size)) // neighbour pos is occupied and in board
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
}
//-------------------------------------------------------------------------------------------------------------------------------------

