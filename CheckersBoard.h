#pragma once
#include "Board.h"
class CheckersBoard : public Board
{
public:
	static constexpr int SIZE = 8;
	CheckersBoard();							// ctor
	CheckersBoard(const CheckersBoard& other);  // cpy ctor
	CheckersBoard(istream& in) : Board(in) {}   // load ctor
	const CheckersBoard& operator=(const CheckersBoard& other);
};

