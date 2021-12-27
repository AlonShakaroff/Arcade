#pragma once
#include "ChessStone.h"
class Knight :  public ChessStone
{
public:
	static constexpr int MAX_VALID_MOVES = 8;

	Knight(int row, int col);														//ctor
	Knight(const Knight& other) : ChessStone(other) {}								// cpy ctor
	Knight(istream& in) : ChessStone(in) { m_valid_moves.resize(MAX_VALID_MOVES); }	// load ctor

	virtual void generateValidMoves(ChessBoard& board) override;
private:
};

