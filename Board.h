#pragma once
#include "Cell.h"
#include <vector>
#include <iostream>

using namespace std;

class Board
{
protected:
	Board(int size);							// ctor
	Board(istream& in) { load(in); }			// load ctor

public:
	enum class BOARD_TYPE { CHECKERS, AMAZONS, CHESS };

	Board(const Board& other);			   		// cpy ctor
	Board(Board&& other);						// move ctor
	virtual ~Board();							//dtor
	const Board& operator=(const Board& other);
	const Board& operator=(Board&& other);

	virtual	void save(ostream& out) const;
	virtual void load(istream& in);

	void setBoard(vector<vector<Cell*>> board) { m_board = board; }
	const vector<vector<Cell*>>& getBoard() const { return m_board; }
	vector<vector<Cell*>>& getBoard() { return m_board; }
	int getSize() { return m_size; }
	const int getSize() const { return m_size; }
	Stone* getStone(const Position& pos);
	virtual Cell& getCell(const Position& pos) { return *getBoard()[pos.getRow()][pos.getCol()]; }
	BOARD_TYPE& getBoardType() { return m_boardType; }
	const BOARD_TYPE& getBoardType() const { return m_boardType; }

	virtual void printBoard() const;
	const bool& isOccupied(Position pos) const;



protected:
	vector<vector<Cell*>> m_board;
	int m_size;
	BOARD_TYPE m_boardType;
};

