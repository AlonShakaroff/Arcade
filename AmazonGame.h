#pragma once
#include "Game.h"
class AmazonGame : public Game
{
public:
	AmazonGame(); // ctor
	AmazonGame(const AmazonGame& other);  // cpy ctor
	AmazonGame(istream& in) : Game(in) {} // load ctor
	const AmazonGame& operator=(const AmazonGame& other);

	static constexpr int NUM_OF_AMAZONS = 4;
	virtual void generateValidMovesAndRisks() override;
	virtual void restoreStoneList();
};

