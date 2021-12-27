#pragma once
#include <iostream>
#include "ChessGame.h"
#include "ChessBoard.h"
#include "ChessPlayer.h"
#include "Stone.h"
#include "ChessStone.h"
#include <list>

using namespace std;

//-------------------------------------------------------------------------------------------------------------------------------------
ChessGame::ChessGame()
{
	m_gameType = Game::GAME_TYPE::CHESS;

	m_riskByCell = false;
	m_twoStepMove = false;

	m_gameBoard = new ChessBoard;
	m_stoneList = new list<Stone*>;
	initializeStoneList(*getBoard());

	m_black = new ChessPlayer(Stone::PLAYER_ID::black, *getBoard());
	m_white = new ChessPlayer(Stone::PLAYER_ID::white, *getBoard());

	generateValidMovesAndRisks();
}
//-------------------------------------------------------------------------------------------------------------------------------------
void ChessGame::initializeStoneList(Board& board)
{
	int row, col;
	int size = board.getSize();

	for (row = 0; row < size; row++)
	{
		for (col = 0; col < size; col++)
		{
			if (board.getBoard()[row][col]->getStoneP() != nullptr)
				getStoneList().push_back(board.getBoard()[row][col]->getStoneP());
		}
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------
void ChessGame::generateValidMovesAndRisks()
{
	list<Stone*>::iterator curBlack = static_cast<ChessPlayer*>(m_black)->getStoneList().begin();
	list<Stone*>::iterator curWhite = static_cast<ChessPlayer*>(m_white)->getStoneList().begin();
	ChessBoard* board = static_cast<ChessBoard*>(getBoard());


	//-----------------------------------------------------------------------------------------------------
	// initialize risks index to 0 for all stones:
	for (; curBlack != static_cast<ChessPlayer*>(m_black)->getStoneList().end(); ++curBlack)
	{
		ChessStone* curStone = static_cast<ChessStone*>(*curBlack);
		curStone->setRisksIndex(0);
	}
	for (; curWhite != static_cast<ChessPlayer*>(m_white)->getStoneList().end(); ++curWhite)
	{
		ChessStone* curStone = static_cast<ChessStone*>(*curWhite);
		curStone->setRisksIndex(0);
	}
	//-----------------------------------------------------------------------------------------------------

	curBlack = static_cast<ChessPlayer*>(m_black)->getStoneList().begin();
	curWhite = static_cast<ChessPlayer*>(m_white)->getStoneList().begin();

	for (; curWhite != static_cast<ChessPlayer*>(m_white)->getStoneList().end(); ++curWhite)
	{
		ChessStone* curStone = static_cast<ChessStone*>(*curWhite);
		curStone->setValidMovesIndex(0); // initialize valid moves array

		curStone->generateValidMoves(*board);
	}

	for (; curBlack != static_cast<ChessPlayer*>(m_black)->getStoneList().end(); ++curBlack)
	{
		ChessStone* curStone = static_cast<ChessStone*>(*curBlack);
		curStone->setValidMovesIndex(0); // initialize valid moves array

		curStone->generateValidMoves(*board);
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------
void ChessGame::restoreStoneList()
{
	vector<vector<Cell*>>& board = getBoard()->getBoard();

	for (int i = 0; i < getBoard()->getSize(); ++i)
	{
		for (int j = 0; j < getBoard()->getSize(); ++j)
		{
			Stone* stoneP = board[i][j]->getStoneP();
			if (stoneP)
			{
				m_stoneList->push_back(stoneP);
				if (stoneP->getPlayerId() == Stone::PLAYER_ID::white)
					static_cast<ChessPlayer*>(m_white)->getStoneList().push_back(stoneP);
				else
					static_cast<ChessPlayer*>(m_black)->getStoneList().push_back(stoneP);
			}
		}
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------
ChessGame::ChessGame(const ChessGame& other) : Game(other), m_stoneList(nullptr)
{
	*this = other;
}
//-------------------------------------------------------------------------------------------------------------------------------------
ChessGame::ChessGame(ChessGame&& other) : Game(other), m_stoneList(nullptr)
{
	*this = move(other);
}
//-------------------------------------------------------------------------------------------------------------------------------------
const ChessGame& ChessGame::operator=(const ChessGame& other)
{
	if (this != &other)
	{
		try
		{
			delete m_stoneList;
			m_stoneList = new list<Stone*>(*(other.m_stoneList));
			delete m_gameBoard;
			m_gameBoard = new ChessBoard;
			*m_gameBoard = *(other.m_gameBoard);
			delete m_black;
			delete m_white;
			m_black = new ChessPlayer(Stone::PLAYER_ID::black, *m_gameBoard);
			m_white = new ChessPlayer(Stone::PLAYER_ID::white, *m_gameBoard);
			*m_black = *(other.m_black);
			*m_white = *(other.m_white);
		}
		catch (bad_alloc())
		{
			delete m_stoneList;
			delete m_gameBoard;
			delete m_black;
			delete m_white;
		}
	}

	return *this;
}
//-------------------------------------------------------------------------------------------------------------------------------------
const ChessGame& ChessGame::operator=(ChessGame&& other)
{
	if (this != &other)
	{
		delete[] m_stoneList;
		m_stoneList = other.m_stoneList;
		other.m_stoneList = nullptr;
	}

	return *this;
}
//-------------------------------------------------------------------------------------------------------------------------------------
ChessGame:: ~ChessGame()
{
	delete m_stoneList;
}
//-------------------------------------------------------------------------------------------------------------------------------------
