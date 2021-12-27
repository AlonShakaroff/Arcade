#include "Board.h"
#include "Position.h"

//-------------------------------------------------------------------------------------------------------------------------------------
Position::Position(int row, int col) : m_row(row), m_col(col)
{
}
//-------------------------------------------------------------------------------------------------------------------------------------
bool Position::isInBoard(int size) const
{
	if (m_row < 0 || m_row >= size || m_col < 0 || m_col >= size)
		return false;
	else return true;
}
//-------------------------------------------------------------------------------------------------------------------------------------
Position Position::getPosFromDirection(const DIRECTION& direction) const
{
	Position newPos;
	switch (direction)
	{
	case DIRECTION::UP_LEFT:
		newPos.setRow(getRow() + 1);
		newPos.setCol(getCol() - 1);
		break;
	case DIRECTION::UP_RIGHT:
		newPos.setRow(getRow() + 1);
		newPos.setCol(getCol() + 1);
		break;
	case DIRECTION::DOWN_LEFT:
		newPos.setRow(getRow() - 1);
		newPos.setCol(getCol() - 1);
		break;
	case DIRECTION::DOWN_RIGHT:
		newPos.setRow(getRow() - 1);
		newPos.setCol(getCol() + 1);
		break;
	case DIRECTION::UP:
		newPos.setRow(getRow() + 1);
		newPos.setCol(getCol());
		break;
	case DIRECTION::DOWN:
		newPos.setRow(getRow() - 1);
		newPos.setCol(getCol());
		break;
	case DIRECTION::LEFT:
		newPos.setRow(getRow());
		newPos.setCol(getCol() - 1);
		break;
	case DIRECTION::RIGHT:
		newPos.setRow(getRow());
		newPos.setCol(getCol() + 1);
		break;
	}

	return newPos;
}
//-------------------------------------------------------------------------------------------------------------------------------------
Position Position::getPosFromDirection(const KNIGHT_DIRECTION& direction) const
{
	Position newPos;
	switch (direction)
	{
	case KNIGHT_DIRECTION::LEFT_DOWN:
		newPos.setRow(getRow() - 1);
		newPos.setCol(getCol() - 2);
		break;
	case KNIGHT_DIRECTION::LEFT_UP:
		newPos.setRow(getRow() + 1);
		newPos.setCol(getCol() - 2);
		break;
	case KNIGHT_DIRECTION::UP_LEFT:
		newPos.setRow(getRow() + 2);
		newPos.setCol(getCol() - 1);
		break;
	case KNIGHT_DIRECTION::UP_RIGHT:
		newPos.setRow(getRow() + 2);
		newPos.setCol(getCol() + 1);
		break;
	case KNIGHT_DIRECTION::RIGHT_UP:
		newPos.setRow(getRow() + 1);
		newPos.setCol(getCol() + 2);
		break;
	case KNIGHT_DIRECTION::RIGHT_DOWN:
		newPos.setRow(getRow() - 1);
		newPos.setCol(getCol() + 2);
		break;
	case KNIGHT_DIRECTION::DOWN_RIGHT:
		newPos.setRow(getRow() - 2);
		newPos.setCol(getCol() + 1);
		break;
	case KNIGHT_DIRECTION::DOWN_LEFT:
		newPos.setRow(getRow() - 2);
		newPos.setCol(getCol() - 1);
		break;
	}

	return newPos;
}
//-------------------------------------------------------------------------------------------------------------------------------------
bool Position::operator==(const Position& other)
{
	return ((getRow() == other.getRow()) && (getCol() == other.getCol()));
}
//-------------------------------------------------------------------------------------------------------------------------------------
bool Position::operator!=(const Position& other)
{
	return ((getRow() != other.getRow()) || (getCol() != other.getCol()));
}
//-------------------------------------------------------------------------------------------------------------------------------------
Position::DIRECTION Position::checkOppositeDirection(const Position& from, const Position& to)
{
	int fromRow, fromCol, toRow, toCol;
	fromRow = from.getRow();
	fromCol = from.getCol();
	toRow = to.getRow();
	toCol = to.getCol();

	if (fromRow - toRow < 0)
	{
		if (fromCol - toCol > 0)
			return Position::DIRECTION::DOWN_RIGHT;
		if (fromCol - toCol < 0)
			return Position::DIRECTION::DOWN_LEFT;
	}
	else
	{
		if (fromCol - toCol > 0)
			return Position::DIRECTION::UP_RIGHT;
		if (fromCol - toCol < 0)
			return Position::DIRECTION::UP_LEFT;
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------
void Position::save(ostream& out) const
{
	out.write(rcastcc(&m_row), sizeof(m_row));
	out.write(rcastcc(&m_col), sizeof(m_col));
}
//-------------------------------------------------------------------------------------------------------------------------------------
void Position::load(istream& in)
{
	in.read(rcastc(&m_row), sizeof(m_row));
	in.read(rcastc(&m_col), sizeof(m_col));
}
//-------------------------------------------------------------------------------------------------------------------------------------