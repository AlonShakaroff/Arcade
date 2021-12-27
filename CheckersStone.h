#pragma once
#include "Stone.h"
#include "Position.h"
#include <iostream>
#include <array>

using namespace std;

class Board;
class Game;

class CheckersStone :  public Stone
{
public:
	static constexpr int MAX_VALID_MOVES = 13;
	static constexpr int MAX_THREATS = 4;

	CheckersStone(int row, int col);			// ctor
	CheckersStone(const CheckersStone& other);	// cpy ctor
	CheckersStone(istream& in);					// load ctor
	const CheckersStone& operator=(const CheckersStone& other);
	virtual ~CheckersStone() {}

	virtual	void save(ostream& out) const;
	virtual void load(istream& in);

	const bool IsKing() { return m_isKing; }
	void checkValidMovesForPawn(Position::DIRECTION direction, Board& board);
	void checkValidMovesForKing(Board& board);
	void addRisk(CheckersStone* newRisk);
	void displayRisks();
	void checkIfAteStone(const Position& from, const Position& to, Board& board, Game& game);
	virtual bool makeMoveTo(const Position& from, const Position& to, Game& game) override;
	virtual void moveStoneTo(const Position& to) override;
	void setRisksIndex(int newInd) { m_risks_index = newInd; }
	const int getAmountOfRisks() const;
	

private:
	array<CheckersStone*, MAX_THREATS>& getRisks() { return m_risks; }
	const array<CheckersStone*, MAX_THREATS>& getRisks() const { return m_risks; }
	void makeKing() { m_isKing = true; setSymbol(getSymbol() - 32); /* Turn lower case letter to capital letter */ }

	bool m_isKing = false;
	array<CheckersStone*, MAX_THREATS> m_risks;
	int m_risks_index = 0;
};

