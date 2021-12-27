#pragma once
#include "Player.h"
#include <array>
using namespace std;

class Amazon;
class AmazonPlayer : public Player
{
public:
	static constexpr int NUM_OF_AMAZONS = 4;

	AmazonPlayer(Stone::PLAYER_ID id);			// ctor
	AmazonPlayer(istream& in) : Player(in), m_amazonArrInd(0) {}	// load ctor

	void increaseAmazonArrInd() { m_amazonArrInd++; }
	int getAmazonArrInd() { return m_amazonArrInd; }
	const int getAmazonArrInd() const { return m_amazonArrInd; }
	array<Amazon*, NUM_OF_AMAZONS>& getAmazonArr() { return m_amazonArr; }
	const array<Amazon*, NUM_OF_AMAZONS>& getAmazonArr() const { return m_amazonArr; }
	void InsertAmazonToPlayerArr(Amazon* amazon);
	bool areThereAvailableMoves() override;

private:
	array<Amazon*,NUM_OF_AMAZONS> m_amazonArr;
	int m_amazonArrInd;
};

