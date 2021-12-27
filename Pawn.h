#pragma once
#include "ChessStone.h"
class Pawn :  public ChessStone
{
public:
	static constexpr int MAX_VALID_MOVES = 4;

	Pawn(int row, int col);																 // ctor
	Pawn(const Pawn& other) : ChessStone(other) { m_isFirstMove = other.m_isFirstMove; } // cpy ctor
	Pawn(istream& in);																	 // load ctor

	virtual	void save(ostream& out) const;
	virtual void load(istream& in);

	virtual void generateValidMoves(ChessBoard& board) override;
	const bool getIsFirstMove() const { return m_isFirstMove; }
	void SetFirstMoveDone() { m_isFirstMove = false; }

private:
	bool m_isFirstMove;
};

