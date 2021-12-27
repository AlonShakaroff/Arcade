#pragma once
#include "Stone.h"
class Player
{
public:
	// default ctor
	Player() {}
	Player(istream& in) { load(in); } // load ctor
	virtual ~Player() {}			  // dtor

	virtual	void save(ostream& out) const;
	virtual void load(istream& in);

	bool& getIsPlayersTurn() { return m_isPlayersTurn; }
	const bool& getIsPlayersTurn() const { return m_isPlayersTurn; }
	void setIsPlayersTurn(bool isTurn) { m_isPlayersTurn = isTurn; }
	virtual bool areThereAvailableMoves() = 0;
	void setPlayerWon() { m_didPlayerWin = true; }
	
protected:
	Stone::PLAYER_ID m_id;
	bool m_isPlayersTurn;
	bool m_didPlayerWin = false;
};