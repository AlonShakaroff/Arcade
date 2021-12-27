#pragma once
#include "Cell.h"
#include "Amazon.h"
#include <array>

using namespace std;

class AmazonBoard;

class AmazonsCell : public Cell
{
public:
	AmazonsCell(int row, int col);			 // ctor
	AmazonsCell(const AmazonsCell& other);	 // cpy ctor
	AmazonsCell(istream& in);				 // load ctor
	const AmazonsCell& operator=(const AmazonsCell& other);

	virtual	void save(ostream& out) const;
	virtual void load(istream& in);

	static constexpr int MAX_VALID_MOVES = 36;
	static constexpr int MAX_THREATS = 36;

	
	void addThreat(const Position& newThreat);
	void displayThreats();
	void generateThreats(AmazonBoard& board);
	array<Position, MAX_THREATS>& getThreats() { return m_threats; }
	const array<Position, MAX_THREATS>& getThreats() const { return m_threats; }
	void setThreatsIndex(int newInd) { m_threats_index = newInd; }
	int getThreatsIndex() { return m_threats_index; }
	const int getThreatsIndex() const { return m_threats_index; }
	const Amazon* getAmazonP() const { return static_cast<const Amazon*>(getStoneP()); }
	Amazon* getAmazonP() { return static_cast<Amazon*>(getStoneP()); }

private:
	array<Position, MAX_THREATS> m_threats;
	int m_threats_index = 0;
};

