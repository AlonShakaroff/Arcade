#include "AmazonBoard.h"
#include "AmazonsCell.h"

//-------------------------------------------------------------------------------------------------------------------------------------
AmazonBoard::AmazonBoard() : Board(SIZE)
{
	m_boardType = Board::BOARD_TYPE::AMAZONS;
	int row, col;

	for (row = 0; row < SIZE; row++)
	{
		for (col = 0; col < SIZE; col++)
		{
			m_board[row][col] = new AmazonsCell(row,col);
		}
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------
void AmazonBoard::printBoard() const
{
	int size = getSize();

	int i, j, k;

	for (i = size - 1; i >= 0; --i)
	{
		cout << "_____";
		for (k = 0; k < size; ++k)
			cout << "____";
		cout << endl;

		if (i >= 9) // in case of double digit row
		{
			cout << "|" << i + 1 << " ";
		}
		else
		{
			cout << "| " << i + 1 << " ";
		}
		for (j = 0; j < size; j++)
		{
			if (getBoard()[i][j]->getStoneP() == nullptr)
			{
				if (getBoard()[i][j]->isOccupied() == true)
					cout << "| ! ";
				else
				{
					cout << "|   ";
				}
			}

			else
			{
				cout << "| " << getBoard()[i][j]->getStoneP()->getSymbol() << " ";
			}
		}
		cout << "|" << endl;
	}

	for (k = 0; k <= size; ++k)
		cout << "----";
	cout << "-";
	cout << endl;
	cout << "    ";
	for (k = 0; k < size; ++k)
		cout << "| " << k + 1 << " ";
	cout << "|";
	cout << endl;
}
//-------------------------------------------------------------------------------------------------------------------------------------
AmazonBoard::AmazonBoard(const AmazonBoard& other) : Board(other)
{
	*this = other;
}
//-------------------------------------------------------------------------------------------------------------------------------------
const AmazonBoard& AmazonBoard::operator=(const AmazonBoard& other)
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
				m_board[row][col] = new AmazonsCell(static_cast<const AmazonsCell&>(*(other.m_board[row][col])));
			}
		}
	}

	return *this;
}
//-------------------------------------------------------------------------------------------------------------------------------------

