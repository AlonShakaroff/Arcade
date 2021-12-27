#pragma once
#include "Stone.h"

class Cell
{
public:

	Cell(int row,int col) : m_position(row,col) {}	// ctor
	Cell(const Cell& other);						// cpy ctor
	Cell(Cell&& other);								// move ctor
	Cell(istream& in) { load(in); }					// load ctor
	virtual ~Cell();								// dtor
	const Cell& operator=(const Cell& other);
	const Cell& operator=(Cell&& other);

	virtual	void save(ostream& out) const;
	virtual void load(istream& in);

	void setStoneP(Stone* StoneP) { m_StoneP = StoneP; }
	Stone* getStoneP() { return m_StoneP; }
	const Stone* getStoneP() const { return m_StoneP; }
	void setIsOccupied(bool isOccupied) { m_isOccupied = isOccupied; }
	bool isOccupied() { return m_isOccupied; }
	const Position& getPosition() const { return m_position; }
	Position& getPosition() { return m_position; }
	void setPosition(int row, int col) { m_position.setRow(row); m_position.setCol(col); }
	virtual void displayThreats() {}

protected:
	Position m_position;
	bool m_isOccupied = false;
	Stone* m_StoneP = nullptr;
};
