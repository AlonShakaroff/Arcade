#pragma once
#include "Amazon.h"
#include "Board.h"
#include "AmazonGame.h"
#include "AmazonBoard.h"

//-------------------------------------------------------------------------------------------------------------------------------------
Amazon::Amazon(int row, int col) : Stone(row,col)
{
	m_stoneType = Stone::STONE_TYPE::AMAZON;
	m_valid_moves.reserve(MAX_THREATS);
	if (row <= 4)
	{
		setPlayerId(PLAYER_ID::white);
		setSymbol('O');
	}
	else
	{
		setPlayerId(PLAYER_ID::black);
		setSymbol('X');
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------
void Amazon::generateValidMoves(AmazonBoard& board)
{
	AmazonsCell& curCell = board.getCell(getPosition());
	array<Position, MAX_THREATS>& threatsArr = curCell.getThreats();
	int size = curCell.getThreatsIndex() + 1;
	m_valid_moves.resize(size);
	for (int i = 0; i < size; ++i)
	{
		m_valid_moves[i] = threatsArr[i];
	}
	setValidMovesIndex(curCell.getThreatsIndex());
}
//-------------------------------------------------------------------------------------------------------------------------------------
bool Amazon::makeMoveTo(const Position& from, const Position& to, const Position& arrow, Game& game)
{
	vector<Position>& validMovesArr = getValidMoves();
	AmazonGame& amazonGame = static_cast<AmazonGame&>(game);
	Board* board = amazonGame.getBoard();
	AmazonsCell& destinationCell = static_cast<AmazonsCell&>(board->getCell(to));
	array<Position, MAX_THREATS>& risksArr = destinationCell.getThreats();
	int size = destinationCell.getThreatsIndex() + 1; 

	int i;
	bool arrowIsValid = false;

	for (i = 0; i < size; i++)
	{
		if (risksArr[i] == arrow)
		{
			arrowIsValid = true;
			break;
		}
	}

	if (!arrowIsValid)
		return false;

	size = getAmountOfValidMoves();
	for (i = 0; i < size; ++i)
	{
		if (validMovesArr[i] == to)
		{
			moveStoneTo(to);
			board->getCell(to).setStoneP(this);
			board->getCell(to).setIsOccupied(true);
			board->getCell(from).setStoneP(nullptr);
			board->getCell(from).setIsOccupied(false);
			board->getCell(arrow).setStoneP(nullptr);
			board->getCell(arrow).setIsOccupied(true);

			return true;
		}
	}
	return false;
}
//-------------------------------------------------------------------------------------------------------------------------------------
