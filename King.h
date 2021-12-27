#pragma once
#include "ChessStone.h"
class King :  public ChessStone
{
public:
	static constexpr int MAX_VALID_MOVES = 8;

	King(int row, int col);															//ctor
	King(const King& other) : ChessStone(other) {}									// cpy ctor
	King(istream& in) : ChessStone(in) { m_valid_moves.resize(MAX_VALID_MOVES); }	// load ctor

	virtual void generateValidMoves(ChessBoard& board) override;
private:
};

