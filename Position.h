#pragma once
#include <iostream>
using namespace std;
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

class Position
{
public:
	enum class DIRECTION { UP_LEFT, UP_RIGHT, DOWN_LEFT, DOWN_RIGHT, UP, DOWN, LEFT, RIGHT };
	enum class KNIGHT_DIRECTION { LEFT_DOWN, LEFT_UP, UP_LEFT, UP_RIGHT, RIGHT_UP, RIGHT_DOWN, DOWN_RIGHT, DOWN_LEFT };

	Position() = default;
	Position(int row, int col);
	virtual ~Position() {}

	void save(ostream& out) const;
	void load(istream& in);

	bool operator==(const Position& other);
	bool operator!=(const Position& other);

	const int& getRow() const { return m_row; }
	int& getRow() { return m_row; }
	int& getCol() { return m_col; }
	const int& getCol() const { return m_col; }
	void setRow(int row) { m_row = row; }
	void setCol(int col) { m_col = col; }

	Position getPosFromDirection(const DIRECTION& direction) const;
	Position getPosFromDirection(const KNIGHT_DIRECTION& direction) const;
	static DIRECTION checkOppositeDirection(const Position& from, const Position& to);

	bool isInBoard(int size) const;

private:
	int m_row;
	int m_col;
};
