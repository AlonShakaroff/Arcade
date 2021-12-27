#pragma once
#include "ChessStone.h"
class Rook :  public ChessStone
{
public:
	static constexpr int MAX_VALID_MOVES = 14;

	Rook(int row, int col);															// ctor
	Rook(const Rook& other) : ChessStone(other) {}									// cpy ctor
	Rook(istream& in) : ChessStone(in) { m_valid_moves.resize(MAX_VALID_MOVES); }	// load ctor

	virtual void generateValidMoves(ChessBoard& board) override;
private:
};

