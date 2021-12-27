#pragma once
#include "Player.h"
#include <iostream>
#include <list>

using namespace std;

class ChessPlayer : public Player
{
public:
	ChessPlayer(Stone::PLAYER_ID id, Board& board); // ctor
	ChessPlayer(istream& in) : Player(in) {}		// load ctor
	
	void initializeStoneList(Board& board, Stone::PLAYER_ID id);
	list<Stone*>& getStoneList() { return m_stoneList; }
	bool areThereAvailableMoves() override;

private:
	 list<Stone*> m_stoneList;
};

