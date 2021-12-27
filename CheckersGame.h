#pragma once
#include "Game.h"
#include <iostream>
#include <list>

using namespace std;

class CheckersGame :  public Game
{
public:
	CheckersGame();																	// ctor
	CheckersGame(const CheckersGame& other);										// cpy ctor
	CheckersGame(CheckersGame&& other);												// move ctor
	CheckersGame(istream& in) : Game(in) { m_stoneList = new list<Stone*>; }		// load ctor
	virtual ~CheckersGame();														// dtor
	const CheckersGame& operator=(const CheckersGame& other);
	const CheckersGame& operator=(CheckersGame&& other);

	virtual void restoreStoneList();
	virtual void generateValidMovesAndRisks() override;
	list<Stone*>& getStoneList() { return *m_stoneList; }
	void initializeStoneList(Board& board);

private:
	list<Stone*>* m_stoneList;
};

