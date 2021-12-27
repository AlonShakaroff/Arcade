#pragma once
#include "Game.h"
#include "Player.h";
#include "AmazonPlayer.h"
#include "CheckersPlayer.h"
#include "ChessPlayer.h"
#include "AmazonBoard.h"
#include "CheckersBoard.h"
#include "ChessBoard.h"
#include <iostream>
using namespace std;

//-------------------------------------------------------------------------------------------------------------------------------------
void Game::displayGame()
{
	m_gameBoard->printBoard();
	if (m_gameStatus == GAME_STATUS::running)
	{
		cout << "Game Status: running" << endl;
		if (m_black->getIsPlayersTurn())
			cout << "Blacks Turn" << endl;
		else
			cout << "Whites Turn" << endl;
	}
	else // game over
	{
		cout << "Game Status: over" << endl;
		if (m_victor == Stone::PLAYER_ID::black)
			cout << "Black Won" << endl;
		else
			cout << "White Won" << endl;
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------
Stone::PLAYER_ID Game::getPlayersTurnId()
{
	if (m_white->getIsPlayersTurn())
		return Stone::PLAYER_ID::white;
	else
		return Stone::PLAYER_ID::black;
}
//-------------------------------------------------------------------------------------------------------------------------------------
const Stone::PLAYER_ID& Game::getPlayersTurnId() const
{
	if (m_white->getIsPlayersTurn())
		return Stone::PLAYER_ID::white;
	else
		return Stone::PLAYER_ID::black;
}
//-------------------------------------------------------------------------------------------------------------------------------------
void Game::updateGameStatus()
{
	if (getPlayersTurnId() == Stone::PLAYER_ID::white)
	{
		if (!getBlack()->areThereAvailableMoves())
		{
			setStatus(GAME_STATUS::over);
			setVictor(Stone::PLAYER_ID::white);
			getWhite()->setPlayerWon();
		}
		else
		{
			getBlack()->setIsPlayersTurn(true);
			getWhite()->setIsPlayersTurn(false);
		}
	}
	else
	{
		if (!getWhite()->areThereAvailableMoves())
		{
			setStatus(GAME_STATUS::over);
			setVictor(Stone::PLAYER_ID::black);
			getBlack()->setPlayerWon();
		}
		else
		{
			getWhite()->setIsPlayersTurn(true);
			getBlack()->setIsPlayersTurn(false);
		}
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------
Game::Game(const Game& other)
{
	*this = other;
}
//-------------------------------------------------------------------------------------------------------------------------------------
Game::Game(Game&& other)
{
	*this = move(other);
}
//-------------------------------------------------------------------------------------------------------------------------------------
const Game& Game::operator=(const Game& other)
{
	if (this != &other)
	{
		m_victor = other.m_victor;
		m_gameStatus = other.m_gameStatus;
		m_gameType = other.m_gameType;
		m_riskByCell = other.m_riskByCell;
		m_twoStepMove = other.m_twoStepMove;
	}

	return *this;
}
//-------------------------------------------------------------------------------------------------------------------------------------
const Game& Game::operator=(Game&& other)
{
	if (this != &other)
	{
		m_victor = other.m_victor;
		m_gameStatus = other.m_gameStatus;
		m_gameType = other.m_gameType;
		m_riskByCell = other.m_riskByCell;
		m_twoStepMove = other.m_twoStepMove;

		delete m_gameBoard;
		delete m_black;
		delete m_white;
		m_gameBoard = other.m_gameBoard;
		m_black = other.m_black;
		m_white = other.m_white;
		other.m_gameBoard = nullptr;
		other.m_black = nullptr;
		other.m_white = nullptr;
	}

	return *this;
}
//-------------------------------------------------------------------------------------------------------------------------------------
Game::~Game()
{
	delete m_gameBoard;
	delete m_black;
	delete m_white;
}
//-------------------------------------------------------------------------------------------------------------------------------------
void Game::save(ostream& out) const
{
	out.write(rcastcc(&m_gameType), sizeof(m_gameType));
	out.write(rcastcc(&m_victor), sizeof(m_victor));
	out.write(rcastcc(&m_gameStatus), sizeof(m_gameStatus));
	m_gameBoard->save(out);
	out.write(rcastcc(&m_riskByCell), sizeof(m_riskByCell));
	out.write(rcastcc(&m_twoStepMove), sizeof(m_twoStepMove));
	m_black->save(out);
	m_white->save(out);
}
//-------------------------------------------------------------------------------------------------------------------------------------
void Game::load(istream& in)
{
	in.read(rcastc(&m_gameType), sizeof(m_gameType));
	in.read(rcastc(&m_victor), sizeof(m_victor));
	in.read(rcastc(&m_gameStatus), sizeof(m_gameStatus));

	switch (m_gameType)
	{
	case GAME_TYPE::AMAZONS:
		m_gameBoard = new AmazonBoard(in);
		break;
	case GAME_TYPE::CHECKERS:
		m_gameBoard = new CheckersBoard(in);
		break;
	case GAME_TYPE::CHESS:
		m_gameBoard = new ChessBoard(in);
		break;
	}

	in.read(rcastc(&m_riskByCell), sizeof(m_riskByCell));
	in.read(rcastc(&m_twoStepMove), sizeof(m_twoStepMove));

	switch (m_gameType)
	{
	case GAME_TYPE::AMAZONS:
		m_black = new AmazonPlayer(in);
		m_white = new AmazonPlayer(in);
		break;
	case GAME_TYPE::CHECKERS:
		m_black = new CheckersPlayer(in);
		m_white = new CheckersPlayer(in);
		break;
	case GAME_TYPE::CHESS:
		m_black = new ChessPlayer(in);
		m_white = new ChessPlayer(in);
		break;
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------