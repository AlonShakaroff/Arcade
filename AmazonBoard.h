#pragma once
#include "Board.h"
#include "AmazonsCell.h"
#include <iostream>
using namespace std;

class AmazonBoard : public Board
{
public:
	static constexpr int SIZE = 10;
	AmazonBoard();							// ctor
	AmazonBoard(const AmazonBoard& other);  // cpy ctor
	AmazonBoard(istream& in) : Board(in) {} // load ctor
	const AmazonBoard& operator=(const AmazonBoard& other);

	virtual void printBoard() const override;
	virtual AmazonsCell& getCell(const Position& pos) const { return static_cast<AmazonsCell&>(*getBoard()[pos.getRow()][pos.getCol()]); }
};

