#pragma once
#include "ChessStone.h"
class Queen :  public ChessStone
{
public:
	static constexpr int MAX_VALID_MOVES = 36;

	Queen(int row, int col);														// ctor
	Queen(const Position& position, Stone::PLAYER_ID id);
	Queen(const Queen& other) : ChessStone(other) {}								// cpy ctor
	Queen(istream& in) : ChessStone(in) { m_valid_moves.resize(MAX_VALID_MOVES); }	// load ctor

	virtual void generateValidMoves(ChessBoard& board) override;
private:
};

