#pragma once
#include <iostream>
#include "ChessStone.h"
#include "ChessBoard.h"
#include "ChessGame.h"
#include "ChessPlayer.h"
#include "Pawn.h"
#include "Queen.h"

using namespace std;

//--------------------------------------------------------------------------------------------------------------------------------------------//
ChessStone::ChessStone(istream& in) : Stone(in) {}
//--------------------------------------------------------------------------------------------------------------------------------------------//
void ChessStone::displayRisks()
{
	int i;
	for (i = 0; i < m_risks_index; ++i)
	{
		cout << "(" << getRisks()[i].getRow() + 1 << "," << getRisks()[i].getCol() + 1 << ")" << " ";
	}
	cout << endl;
}
//--------------------------------------------------------------------------------------------------------------------------------------------//
void ChessStone::addRisk(Position newRisk)
{
	m_risks[m_risks_index] = newRisk;
	++m_risks_index;
}
//--------------------------------------------------------------------------------------------------------------------------------------------//
bool ChessStone::simulateIsMoveValid(ChessBoard& board, const Position& from, const Position& to)
{
	Stone* toPrevStoneP = board.getBoard()[to.getRow()][to.getCol()]->getStoneP();
	bool toPrevOccupationData = board.getBoard()[to.getRow()][to.getCol()]->isOccupied();

	//simulate the move
	board.getBoard()[to.getRow()][to.getCol()]->setStoneP(this);
	board.getBoard()[to.getRow()][to.getCol()]->setIsOccupied(true);
	board.getBoard()[from.getRow()][from.getCol()]->setStoneP(nullptr);
	board.getBoard()[from.getRow()][from.getCol()]->setIsOccupied(false);
	//if king - update king location temporarily
	if (getSymbol() == 'k')
	{
		board.setCurKingPosWhite(to);
	}
	if (getSymbol() == 'K')
	{
		board.setCurKingPosBlack(to);
	}

	//check if king is safe
	bool isKingSafe = board.isKingSafe(getPlayerId());

	//restore previous board data
	board.getBoard()[to.getRow()][to.getCol()]->setStoneP(toPrevStoneP);
	board.getBoard()[to.getRow()][to.getCol()]->setIsOccupied(toPrevOccupationData);
	board.getBoard()[from.getRow()][from.getCol()]->setStoneP(this);
	board.getBoard()[from.getRow()][from.getCol()]->setIsOccupied(true);
	//restore king location if nessecery
	if (getSymbol() == 'k')
	{
		board.setCurKingPosWhite(from);
	}
	if (getSymbol() == 'K')
	{
		board.setCurKingPosBlack(from);
	}

	return isKingSafe;
}
//--------------------------------------------------------------------------------------------------------------------------------------------//
bool ChessStone::makeMoveTo(const Position& from, const Position& to, Game& game)
{
	const vector<Position>& validMovesArr = getValidMoves();
	Board& board = *game.getBoard();
	int size = getAmountOfValidMoves();
	int boardSize = board.getSize();

	int i;

	for (i = 0; i < size; ++i)
	{
		if ((validMovesArr[i].getRow() == to.getRow()) && (validMovesArr[i].getCol() == to.getCol()))
		{
			if (board.isOccupied(to)) // if a stone gets eaten
			{
				Stone* removedStone = board.getStone(to);
				if (game.getPlayersTurnId() == Stone::PLAYER_ID::white)
				{
					static_cast<ChessPlayer*>(game.getBlack())->getStoneList().remove(removedStone);
				}
				else
				{
					static_cast<ChessPlayer*>(game.getWhite())->getStoneList().remove(removedStone);
				}
				static_cast<ChessGame&>(game).getStoneList().remove(removedStone);
				delete removedStone;
			}

			moveStoneTo(to);
			board.getBoard()[to.getRow()][to.getCol()]->setStoneP(this);
			board.getBoard()[to.getRow()][to.getCol()]->setIsOccupied(true);
			board.getBoard()[from.getRow()][from.getCol()]->setStoneP(nullptr);
			board.getBoard()[from.getRow()][from.getCol()]->setIsOccupied(false);

			if (getSymbol() == 'p' || getSymbol() == 'P') // check if pawn made first move, or, if pawn reached the end of the board.
			{
				if(static_cast<Pawn*>(this)->getIsFirstMove())
					static_cast<Pawn*>(this)->SetFirstMoveDone();
				if (getPlayerId() == Stone::PLAYER_ID::white && getPosition().getRow() == boardSize - 1)
				{
					Queen* newQueen = new Queen(getPosition(),getPlayerId());
					board.getBoard()[to.getRow()][to.getCol()]->setStoneP(newQueen);
					delete this;
				}
				if (getPlayerId() == Stone::PLAYER_ID::black && getPosition().getRow() == 0)
				{
					Queen* newQueen = new Queen(getPosition(), getPlayerId());
					board.getBoard()[to.getRow()][to.getCol()]->setStoneP(newQueen);
					delete this;
				}
			}
			if (getSymbol() == 'k') // check if white King was moved
			{
				static_cast<ChessBoard&>(board).setCurKingPosWhite(to);
			}
			if (getSymbol() == 'K') // check if black King was moved
			{
				static_cast<ChessBoard&>(board).setCurKingPosBlack(to);
			}
			return true;
		}
	}
	return false;
}
//--------------------------------------------------------------------------------------------------------------------------------------------//
//void ChessStone::save(ostream& out) const
//{
//	Stone::save(out);
//	int risksSize = m_risks.size();
//	out.write(rcastcc(&risksSize), sizeof(risksSize));
//	for (int i = 0; i < risksSize; ++i)
//	{
//		m_risks[i].save(out);
//	}
//	out.write(rcastcc(&m_risks_index), sizeof(m_risks_index));
//}
////-------------------------------------------------------------------------------------------------------------------------------------
//void ChessStone::load(istream& in)
//{
//	int risksSize;
//	in.read(rcastc(&risksSize), sizeof(risksSize));
//	for (int i = 0; i < risksSize; ++i)
//	{
//		m_risks[i].load(in);
//	}
//	in.read(rcastc(&m_risks_index), sizeof(m_risks_index));
//}
////-------------------------------------------------------------------------------------------------------------------------------------