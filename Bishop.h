#pragma once
#include "ChessStone.h"
class Bishop : public ChessStone
{
public:
	static constexpr int MAX_VALID_MOVES = 14;

	Bishop(int row, int col);														//ctor
	Bishop(const Bishop& other) : ChessStone(other) {}								// cpy ctor
	Bishop(istream& in) : ChessStone(in) { m_valid_moves.resize(MAX_VALID_MOVES); }	// load ctor

	virtual void generateValidMoves(ChessBoard& board) override;

private:
};

