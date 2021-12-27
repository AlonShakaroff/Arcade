#include "CheckersBoard.h"
#include "CheckersCell.h"

//-------------------------------------------------------------------------------------------------------------------------------------
CheckersBoard::CheckersBoard() : Board(SIZE)
{
	m_boardType = Board::BOARD_TYPE::CHECKERS;
	int row, col;

	for (row = 0; row < SIZE; row++)
	{
		for (col = 0; col < SIZE; col++)
		{
			m_board[row][col] = new CheckersCell(row, col);
		}
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------
CheckersBoard::CheckersBoard(const CheckersBoard& other) : Board(other)
{
	*this = other;
}
//-------------------------------------------------------------------------------------------------------------------------------------
const CheckersBoard& CheckersBoard::operator=(const CheckersBoard& other)
{
	if (this != &other)
	{
		int size = m_size;
		m_board.resize(size);

		int row, col;

		for (row = 0; row < size; ++row)
		{
			m_board[row].resize(size);
			for (col = 0; col < size; ++col)
			{
				m_board[row][col] = new CheckersCell(static_cast<const CheckersCell&>(*(other.m_board[row][col])));
			}
		}
	}

	return *this;
}
//-------------------------------------------------------------------------------------------------------------------------------------

