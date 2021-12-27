#pragma once
#include "CheckersGame.h"
#include "CheckersBoard.h"
#include "CheckersPlayer.h"
#include "CheckersStone.h"

//-------------------------------------------------------------------------------------------------------------------------------------
CheckersGame::CheckersGame() 
{
	m_gameType = Game::GAME_TYPE::CHECKERS;

	m_riskByCell = false;
	m_twoStepMove = false;

	try
	{
		m_gameBoard = new CheckersBoard;
		m_stoneList = new list<Stone*>;
		initializeStoneList(*getBoard());

		m_black = new CheckersPlayer(Stone::PLAYER_ID::black, *getBoard());
		m_white = new CheckersPlayer(Stone::PLAYER_ID::white, *getBoard());
	}
	catch (bad_alloc())
	{
		delete m_gameBoard;
		delete m_stoneList;
		delete m_black;
		delete m_white;
	}

	generateValidMovesAndRisks();
}
//-------------------------------------------------------------------------------------------------------------------------------------
void CheckersGame::initializeStoneList(Board& board)
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
void CheckersGame::generateValidMovesAndRisks()
{
	list<Stone*>::iterator curBlack = static_cast<CheckersPlayer*>(m_black)->getStoneList().begin();
	list<Stone*>::iterator curWhite = static_cast<CheckersPlayer*>(m_white)->getStoneList().begin();

	//-----------------------------------------------------------------------------------------------------
	// initialize risks index to 0 for all stones:
	for (; curBlack != static_cast<CheckersPlayer*>(m_black)->getStoneList().end(); ++curBlack)
	{
		CheckersStone* curStone = static_cast<CheckersStone*>(*curBlack);
		curStone->setRisksIndex(0);
	}
	for (; curWhite != static_cast<CheckersPlayer*>(m_white)->getStoneList().end(); ++curWhite)
	{
		CheckersStone* curStone = static_cast<CheckersStone*>(*curWhite);
		curStone->setRisksIndex(0);
	}
	//-----------------------------------------------------------------------------------------------------

	curBlack = static_cast<CheckersPlayer*>(m_black)->getStoneList().begin();
	curWhite = static_cast<CheckersPlayer*>(m_white)->getStoneList().begin();

	for (;curBlack != static_cast<CheckersPlayer*>(m_black)->getStoneList().end(); ++curBlack)
	{
		CheckersStone* curStone = static_cast<CheckersStone*>(*curBlack);
		curStone->setValidMovesIndex(0); // initialize valid moves array
		Board* board = getBoard();
		if (curStone->IsKing())
		{
			curStone->checkValidMovesForKing(*board);
		}
		else
		{
			curStone->checkValidMovesForPawn(Position::DIRECTION::UP_LEFT, *board);
			curStone->checkValidMovesForPawn(Position::DIRECTION::UP_RIGHT, *board);
		}
	}

	for (; curWhite != static_cast<CheckersPlayer*>(m_white)->getStoneList().end(); ++curWhite)
	{
		CheckersStone* curStone = static_cast<CheckersStone*>(*curWhite);
		curStone->setValidMovesIndex(0); // initialize valid moves array
		Board* board = getBoard();
		if (curStone->IsKing())
		{
			curStone->checkValidMovesForKing(*board);
		}
		else
		{
			curStone->checkValidMovesForPawn(Position::DIRECTION::DOWN_LEFT, *board);
			curStone->checkValidMovesForPawn(Position::DIRECTION::DOWN_RIGHT, *board);
		}
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------
void CheckersGame::restoreStoneList()
{
	vector<vector<Cell*>>& board = getBoard()->getBoard();

	int boardSize = getBoard()->getSize();

	for (int i = 0; i < boardSize; ++i)
	{
		for (int j = 0; j < boardSize; ++j)
		{
			Stone* stoneP = board[i][j]->getStoneP();
			if (stoneP)
			{
				m_stoneList->push_back(stoneP);
				if (stoneP->getPlayerId() == Stone::PLAYER_ID::white)
					static_cast<CheckersPlayer*>(m_white)->getStoneList().push_back(stoneP);
				else
					static_cast<CheckersPlayer*>(m_black)->getStoneList().push_back(stoneP);
			}
		}
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------
CheckersGame::CheckersGame(const CheckersGame& other) : Game(other) , m_stoneList(nullptr)
{
	*this = other;
}
//-------------------------------------------------------------------------------------------------------------------------------------
CheckersGame::CheckersGame(CheckersGame&& other) : Game(other), m_stoneList(nullptr)
{
	*this = move(other);
}
//-------------------------------------------------------------------------------------------------------------------------------------
const CheckersGame& CheckersGame::operator=(const CheckersGame& other)
{
	if (this != &other)
	{
		try
		{
			delete[] m_stoneList;
			m_stoneList = new list<Stone*>(*(other.m_stoneList));
			delete m_gameBoard;
			m_gameBoard = new CheckersBoard;
			*m_gameBoard = *(other.m_gameBoard);
			delete m_black;
			delete m_white;
			m_black = new CheckersPlayer(Stone::PLAYER_ID::black, *m_gameBoard);
			m_white = new CheckersPlayer(Stone::PLAYER_ID::white, *m_gameBoard);
			*m_black = *(other.m_black);
			*m_white = *(other.m_white);
		}
		catch (bad_alloc())
		{
			cout << "memory allocation failure" << endl;
			delete m_stoneList;
			delete m_gameBoard;
			delete m_black;
			delete m_white;
			exit(1);
		}
	}

	return *this;
}
//-------------------------------------------------------------------------------------------------------------------------------------
const CheckersGame& CheckersGame::operator=(CheckersGame&& other)
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
CheckersGame:: ~CheckersGame()
{
	delete m_stoneList;
}
//-------------------------------------------------------------------------------------------------------------------------------------
