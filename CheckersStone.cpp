#pragma once
#include <iostream>
using namespace std;

#include "CheckersStone.h"
#include "CheckersBoard.h"
#include "CheckersGame.h"
#include "CheckersPlayer.h"

//-------------------------------------------------------------------------------------------------------------------------------------
CheckersStone::CheckersStone(int row, int col) : Stone(row,col)
{
	m_stoneType = Stone::STONE_TYPE::CHECKERS_STONE;
	m_valid_moves.resize(MAX_VALID_MOVES);

	if (row <= 2)
	{
		m_playerID = Stone::PLAYER_ID::black;
		setSymbol('x');
	}
	else
	{
		m_playerID = Stone::PLAYER_ID::white;
		setSymbol('o');
	}

}
//-------------------------------------------------------------------------------------------------------------------------------------
CheckersStone::CheckersStone(istream& in) : Stone(in)
{
	m_valid_moves.resize(MAX_VALID_MOVES);
	load(in);
}
//-------------------------------------------------------------------------------------------------------------------------------------
void CheckersStone::addRisk(CheckersStone* newRisk)
{
	m_risks[m_risks_index] = newRisk;
	++m_risks_index;
}
//-------------------------------------------------------------------------------------------------------------------------------------
void CheckersStone::checkValidMovesForPawn(Position::DIRECTION direction, Board& board)
{
	Position neighbourPos = getPosition().getPosFromDirection(direction);
	int size = board.getSize();

	if (neighbourPos.isInBoard(size))
	{
		if (!board.isOccupied(neighbourPos))
		{
			addValidMove(neighbourPos);
		}
		else
		{
			if (board.getStone(neighbourPos)->getPlayerId() != this->getPlayerId())
			{
				Position furtherNeighbour = neighbourPos.getPosFromDirection(direction);

				if (furtherNeighbour.isInBoard(size))
				{
					if (!board.isOccupied(furtherNeighbour))
					{
						addValidMove(furtherNeighbour);
						static_cast<CheckersStone*>(board.getStone(neighbourPos))->addRisk(this); // eating move
					}
				}
			}
		}
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------
void CheckersStone::checkValidMovesForKing(Board& board)
{
	int directionInt;
	int size = board.getSize();
	for (directionInt = static_cast<int>(Position::DIRECTION::UP_LEFT); directionInt <= static_cast<int>(Position::DIRECTION::DOWN_RIGHT); ++directionInt)
	{
		Position::DIRECTION direction = static_cast<Position::DIRECTION>(directionInt);
		Position prev = getPosition();
		Position neighbourPos = prev.getPosFromDirection(direction);

		while (neighbourPos.isInBoard(size) && !board.isOccupied(neighbourPos))
		{
			addValidMove(neighbourPos);
			prev = neighbourPos;
			neighbourPos = neighbourPos.getPosFromDirection(direction);
		}

		if (neighbourPos.isInBoard(size))
		{
			if (board.getStone(neighbourPos)->getPlayerId() != this->getPlayerId())
			{
				Position furtherNeighbour = neighbourPos.getPosFromDirection(direction);

				if (furtherNeighbour.isInBoard(size))
				{
					if (!board.isOccupied(furtherNeighbour))
					{
						addValidMove(furtherNeighbour);
						static_cast<CheckersStone*>(board.getStone(neighbourPos))->addRisk(this); // eating move
					}
				}
			}
		}
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------
void CheckersStone::displayRisks()
{
	int i;
	for (i = 0; i < m_risks_index; ++i)
	{
		cout << "(" << getRisks()[i]->getPosition().getRow() + 1 << "," << getRisks()[i]->getPosition().getCol() + 1 << ")" << " ";
	}
	cout << endl;
}
//-------------------------------------------------------------------------------------------------------------------------------------
const int CheckersStone::getAmountOfRisks() const
{
	if (m_risks_index == 0)
		return 0;
	else
		return m_risks_index + 1;
}
//-------------------------------------------------------------------------------------------------------------------------------------
bool CheckersStone::makeMoveTo(const Position& from, const Position& to, Game& game)
{
	const vector<Position> validMovesArr = getValidMoves();
	Board& board = *game.getBoard();
	int size = getAmountOfValidMoves();

	int i;

	for (i = 0; i < size; ++i)
	{
		if ((validMovesArr[i].getRow() == to.getRow()) && (validMovesArr[i].getCol() == to.getCol()))
		{
			moveStoneTo(to);
			board.getBoard()[to.getRow()][to.getCol()]->setStoneP(this);
			board.getBoard()[to.getRow()][to.getCol()]->setIsOccupied(true);
			board.getBoard()[from.getRow()][from.getCol()]->setStoneP(nullptr);
			board.getBoard()[from.getRow()][from.getCol()]->setIsOccupied(false);

			checkIfAteStone(from, to, board, game);
			return true;
		}
	}
	return false;
}
//-------------------------------------------------------------------------------------------------------------------------------------
void CheckersStone::moveStoneTo(const Position& to)
{
	setPosition(to);
	if (((to.getRow() == 0) || (to.getRow() == (CheckersBoard::SIZE - 1))) && (!IsKing()))
		makeKing();
}
//-------------------------------------------------------------------------------------------------------------------------------------
void CheckersStone::checkIfAteStone(const Position& from, const Position& to, Board& board, Game& game)
{
	if (from.getRow() - to.getRow() == 1 || from.getRow() - to.getRow() == -1)
		return;

	Position::DIRECTION oppositeDirection = Position::checkOppositeDirection(from, to);
	Position checkedPos = to.getPosFromDirection(oppositeDirection);
	if (board.isOccupied(checkedPos))
	{
		Stone* removedStone = board.getStone(checkedPos);
		if (game.getPlayersTurnId() == Stone::PLAYER_ID::white)
		{
			static_cast<CheckersPlayer*>(game.getBlack())->getStoneList().remove(removedStone);
		}
		else
		{
			static_cast<CheckersPlayer*>(game.getWhite())->getStoneList().remove(removedStone);
		}
		static_cast<CheckersGame&>(game).getStoneList().remove(removedStone);
		delete removedStone;

		board.getBoard()[checkedPos.getRow()][checkedPos.getCol()]->setIsOccupied(false);
		board.getBoard()[checkedPos.getRow()][checkedPos.getCol()]->setStoneP(nullptr);
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------
CheckersStone::CheckersStone(const CheckersStone& other) : Stone(other)
{
	*this = other;
}
//-------------------------------------------------------------------------------------------------------------------------------------
const CheckersStone& CheckersStone::operator=(const CheckersStone& other)
{
	if (this != &other)
	{
		m_isKing = other.m_isKing;		
		m_risks_index = other.m_risks_index;

		const int amountOfRisks = getAmountOfRisks();
		for (int i = 0; i < amountOfRisks; ++i)
			m_risks[i] = other.m_risks[i];
	}

	return *this;
}
//-------------------------------------------------------------------------------------------------------------------------------------
void CheckersStone::save(ostream& out) const
{
	Stone::save(out);
	out.write(rcastcc(&m_isKing), sizeof(m_isKing));
}
//-------------------------------------------------------------------------------------------------------------------------------------
void CheckersStone::load(istream& in)
{
	in.read(rcastc(&m_isKing), sizeof(m_isKing));
}
//-------------------------------------------------------------------------------------------------------------------------------------