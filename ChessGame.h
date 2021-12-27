#pragma once
#include "Game.h"
#include <iostream>
#include <list>

using namespace std;

class ChessGame : public Game
{
public:
	ChessGame();															 // ctor
	ChessGame(const ChessGame& other);										 // cpy ctor
	ChessGame(ChessGame&& other);											 // move ctor
	ChessGame(istream& in) : Game(in) { m_stoneList = new list<Stone*>; }	 // load ctor
	virtual ~ChessGame();													 // dtor
	const ChessGame& operator=(const ChessGame& other);	 
	const ChessGame& operator=(ChessGame&& other);

	virtual void restoreStoneList();
	virtual void generateValidMovesAndRisks() override;
	list<Stone*>& getStoneList() { return *m_stoneList; }
	void initializeStoneList(Board& board);

private:
	list<Stone*>* m_stoneList;
};

