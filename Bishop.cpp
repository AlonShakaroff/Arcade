#pragma once
#include "Bishop.h"
#include "ChessBoard.h"

//-------------------------------------------------------------------------------------------------------------------------------------
Bishop::Bishop(int row, int col) : ChessStone(row, col)
{
	m_stoneType = Stone::STONE_TYPE::BISHOP;
	m_valid_moves.resize(MAX_VALID_MOVES);
	if (row <= 1)
	{
		setPlayerId(PLAYER_ID::white);
		setSymbol('b');
	}
	else
	{
		setPlayerId(PLAYER_ID::black);
		setSymbol('B');
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------
void Bishop::generateValidMoves(ChessBoard& board)
{
	int directionInt;
	int size = board.getSize();
	for (directionInt = static_cast<int>(Position::DIRECTION::UP_LEFT); directionInt <= static_cast<int>(Position::DIRECTION::DOWN_RIGHT); ++directionInt)
	{
		Position::DIRECTION direction = static_cast<Position::DIRECTION>(directionInt);
		Position neighbourPos = getPosition().getPosFromDirection(direction);
		Position StonePos = getPosition();

		while (neighbourPos.isInBoard(size) && !board.isOccupied(neighbourPos))
		{
			if (simulateIsMoveValid(board, StonePos, neighbourPos))
			{
				addValidMove(neighbourPos);
			}
			neighbourPos = neighbourPos.getPosFromDirection(direction);
		}

		if (neighbourPos.isInBoard(size))
		{
			if (board.getStone(neighbourPos)->getPlayerId() != this->getPlayerId())
			{
				if (simulateIsMoveValid(board, StonePos, neighbourPos))
				{
					addValidMove(neighbourPos);
					static_cast<ChessStone*>(board.getStone(neighbourPos))->addRisk(getPosition()); // adding risk to threatned stone
				}
			}
		}
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------