#pragma once
#include "ChessBoard.h"
#include "Rook.h"

//-------------------------------------------------------------------------------------------------------------------------------------
Rook::Rook(int row, int col) : ChessStone(row, col)
{
	m_stoneType = Stone::STONE_TYPE::ROOK;
	m_valid_moves.resize(MAX_VALID_MOVES);
	if (row <= 1)
	{
		setPlayerId(PLAYER_ID::white);
		setSymbol('r');
	}
	else
	{
		setPlayerId(PLAYER_ID::black);
		setSymbol('R');
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------
void Rook::generateValidMoves(ChessBoard& board)
{
	int directionInt;
	int size = board.getSize();
	for (directionInt = static_cast<int>(Position::DIRECTION::UP); directionInt <= static_cast<int>(Position::DIRECTION::RIGHT); ++directionInt)
	{
		Position::DIRECTION direction = static_cast<Position::DIRECTION>(directionInt);
		Position stonePosition = getPosition();
		Position neighbourPos = stonePosition.getPosFromDirection(direction);

		while (neighbourPos.isInBoard(size) && !board.isOccupied(neighbourPos))
		{
			if (simulateIsMoveValid(board, stonePosition, neighbourPos))
			{
				addValidMove(neighbourPos);
			}
			neighbourPos = neighbourPos.getPosFromDirection(direction);
		}

		if (neighbourPos.isInBoard(size))
		{
			if (board.getStone(neighbourPos)->getPlayerId() != this->getPlayerId())
			{
				if (simulateIsMoveValid(board, stonePosition, neighbourPos))
				{
					addValidMove(neighbourPos);
					static_cast<ChessStone*>(board.getStone(neighbourPos))->addRisk(getPosition()); // adding risk to threatned stone
				}
			}
		}
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------