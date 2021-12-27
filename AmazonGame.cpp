#pragma once
#include "Game.h"
#include "AmazonGame.h"
#include "Amazon.h"
#include "AmazonBoard.h"
#include "AmazonsCell.h"
#include "AmazonPlayer.h"

//-------------------------------------------------------------------------------------------------------------------------------------
AmazonGame::AmazonGame() 
{
	m_gameType = Game::GAME_TYPE::AMAZONS;
	m_riskByCell = true;
	m_twoStepMove = true;

	try
	{
		m_black = new AmazonPlayer(Stone::PLAYER_ID::black);
		m_white = new AmazonPlayer(Stone::PLAYER_ID::white);

		m_gameBoard = new AmazonBoard;	
	}
	catch (bad_alloc())
	{
		cout << "memory allocation failure" << endl;
		delete m_black;
		delete m_white;
		delete m_gameBoard;
		exit(1);
	}
	generateValidMovesAndRisks();
}
//-------------------------------------------------------------------------------------------------------------------------------------
void AmazonGame::generateValidMovesAndRisks()
{
	AmazonBoard* curBoard = static_cast<AmazonBoard*>(getBoard());
	Player* whitePlayer = getWhite();
	Player* blackPlayer = getBlack();
	Amazon* curAmazon;

	int i, j;
	int size = curBoard->getSize();

	for (i = 0; i < size; ++i)
	{
		for (j = 0; j < size; ++j)
		{
			AmazonsCell& curCell = static_cast<AmazonsCell&>(*curBoard->getBoard()[i][j]);
			curCell.setThreatsIndex(-1);
			curAmazon = static_cast<Amazon*>(curCell.getStoneP());
			if (curAmazon)
			{
				if ( (curAmazon->getPlayerId() == Amazon::PLAYER_ID::black) && ((static_cast<AmazonPlayer*>(blackPlayer))->getAmazonArrInd() < NUM_OF_AMAZONS) )
					(static_cast<AmazonPlayer*>(blackPlayer))->InsertAmazonToPlayerArr(curAmazon);
				else if (curAmazon->getPlayerId() == Amazon::PLAYER_ID::white && (static_cast<AmazonPlayer*>(whitePlayer))->getAmazonArrInd() < NUM_OF_AMAZONS)
					(static_cast<AmazonPlayer*>(whitePlayer))->InsertAmazonToPlayerArr(curAmazon);


				curCell.generateThreats(*curBoard);
				curCell.getAmazonP()->generateValidMoves(*curBoard);
			}
			else if (!curCell.isOccupied())
			{
				curCell.generateThreats(*curBoard);
			}
		}
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------
AmazonGame::AmazonGame(const AmazonGame& other) : Game(other)
{
	*this = other;
}
//-------------------------------------------------------------------------------------------------------------------------------------
const AmazonGame& AmazonGame::operator=(const AmazonGame& other)
{
	if (this != &other)
	{
		delete m_gameBoard;
		
		try
		{
			m_gameBoard = new AmazonBoard;

			*m_gameBoard = *(other.m_gameBoard);
			delete m_black;
			delete m_white;

			m_black = new AmazonPlayer(Stone::PLAYER_ID::black);
			m_white = new AmazonPlayer(Stone::PLAYER_ID::white);
		}
		catch(bad_alloc())
		{
			cout << "memory allocation failure" << endl;
			delete m_gameBoard;
			delete m_black;
			delete m_white;
			exit(1);
		}
		
		*m_black = *(other.m_black);
		*m_white = *(other.m_white);
	}

	return *this;
}
//-------------------------------------------------------------------------------------------------------------------------------------
void AmazonGame::restoreStoneList()
{
	vector<vector<Cell*>>& board = getBoard()->getBoard();

	int boardSize = getBoard()->getSize();

	for (int i = 0; i < boardSize; ++i)
	{
		for (int j = 0; j < boardSize; ++j)
		{
			Amazon* amazonP = static_cast<Amazon*>(board[i][j]->getStoneP());
			if (amazonP)
			{
				if (amazonP->getPlayerId() == Stone::PLAYER_ID::white)
				{
					static_cast<AmazonPlayer*>(m_white)->InsertAmazonToPlayerArr(amazonP);
				}
				else
				{
					static_cast<AmazonPlayer*>(m_black)->InsertAmazonToPlayerArr(amazonP);
				}
			}
		}
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------