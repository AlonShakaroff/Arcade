#pragma once
#include "Board.h"
#include "Player.h"

class Game
{
public:
	Game() = default;
	Game(const Game& other);						// cpy ctor
	Game(Game&& other);								// move ctor
	Game(istream& in) { load(in); }					// load ctor
	virtual ~Game();								// dtor
	const Game& operator=(const Game& other);
	const Game& operator=(Game&& other);

	virtual	void save(ostream& out) const;
	virtual void load(istream& in);

	enum class GAME_STATUS { running, over };
	enum class GAME_TYPE { CHECKERS = 1, AMAZONS, CHESS };

	void setVictor(Stone::PLAYER_ID victor) { m_victor = victor; }
	Stone::PLAYER_ID getVictor() { return m_victor; }
	GAME_STATUS& getGameStatus() { return m_gameStatus; }
	const GAME_STATUS& getGameStatus() const { return m_gameStatus; }
	Board* getBoard() { return m_gameBoard; }
	const Board* getBoard() const { return m_gameBoard; }
	void updateGameStatus();
	virtual void restoreStoneList() {};

	void displayGame();
	virtual void generateValidMovesAndRisks() = 0;
	const Stone::PLAYER_ID& getPlayersTurnId() const;
	Stone::PLAYER_ID getPlayersTurnId();

	const Player* getWhite() const		{ return m_white;		 }
	Player* getWhite()					{ return m_white;		 }
	const Player* getBlack() const		{ return m_black;		 }
	Player* getBlack()					{ return m_black;		 }
	void setStatus(GAME_STATUS status)	{ m_gameStatus = status; }

	bool getIsRiskByCell()				{ return m_riskByCell;	 }
	bool getIsTwoStepMove()				{ return m_twoStepMove;  }

protected:
	Stone::PLAYER_ID m_victor;
	GAME_STATUS m_gameStatus = GAME_STATUS::running;
	GAME_TYPE m_gameType;
	Board* m_gameBoard;

	bool m_riskByCell;
	bool m_twoStepMove;

	Player* m_black;
	Player* m_white;
};

