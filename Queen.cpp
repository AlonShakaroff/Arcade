#pragma once
#include "ChessBoard.h"
#include "Queen.h"
#include "Position.h"

//-------------------------------------------------------------------------------------------------------------------------------------
Queen::Queen(int row, int col) : ChessStone(row, col)
{
	m_stoneType = Stone::STONE_TYPE::QUEEN;
	m_valid_moves.resize(MAX_VALID_MOVES);
	if (row <= 1)
	{
		setPlayerId(PLAYER_ID::white);
		setSymbol('q');
	}
	else
	{
		setPlayerId(PLAYER_ID::black);
		setSymbol('Q');
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------
Queen::Queen(const Position& position, Stone::PLAYER_ID id) : ChessStone(position.getRow(),position.getCol())
{
	m_stoneType = Stone::STONE_TYPE::QUEEN;
	m_valid_moves.resize(MAX_VALID_MOVES);
	if (id == Stone::PLAYER_ID::white)
	{
		setSymbol('q');
	}
	else
	{
		setSymbol('Q');
	}
	setPlayerId(id);
}
//-------------------------------------------------------------------------------------------------------------------------------------
void Queen::generateValidMoves(ChessBoard& board)
{
	int directionInt;
	int size = board.getSize();
	for (directionInt = static_cast<int>(Position::DIRECTION::UP_LEFT); directionInt <= static_cast<int>(Position::DIRECTION::RIGHT); ++directionInt)
	{
		Position::DIRECTION direction = static_cast<Position::DIRECTION>(directionInt);
		Position StonePosition = getPosition();
		Position neighbourPos = StonePosition.getPosFromDirection(direction);

		while (neighbourPos.isInBoard(size) && !board.isOccupied(neighbourPos))
		{
			if (simulateIsMoveValid(board, StonePosition, neighbourPos))
			{
				addValidMove(neighbourPos);
			}
			neighbourPos = neighbourPos.getPosFromDirection(direction);
		}

		if (neighbourPos.isInBoard(size))
		{
			if (board.getStone(neighbourPos)->getPlayerId() != this->getPlayerId())
			{
				if (simulateIsMoveValid(board, StonePosition, neighbourPos))
				{
					addValidMove(neighbourPos);
					static_cast<ChessStone*>(board.getStone(neighbourPos))->addRisk(getPosition()); // adding risk to threatned stone
				}
			}
		}
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------
