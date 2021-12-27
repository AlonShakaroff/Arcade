#pragma once
#include "Stone.h"
#include <iostream>
class AmazonBoard;

class Amazon : public Stone
{
public:
	static constexpr int MAX_THREATS = 36;

	Amazon(int row, int col);
	Amazon(istream& in) : Stone(in) { m_valid_moves.resize(MAX_THREATS); }

	void generateValidMoves(AmazonBoard& board);
	virtual bool makeMoveTo(const Position& from, const Position& to, const Position& arrow, Game& game) override;

};

