#include "Board.h"
#include "CheckersCell.h"
#include "AmazonsCell.h"
#include "ChessCell.h"
#include <iostream>
using namespace std;

//-------------------------------------------------------------------------------------------------------------------------------------
Board::Board(int size) : m_size(size)
{
	m_board.resize(size);

	int row;

	for (row = 0; row < size; row++)
	{
		m_board[row].resize(size);
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------
void Board::printBoard() const
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
			if (m_board[i][j]->getStoneP() == nullptr)
			{
				cout << "|   ";
			}
			else
				cout << "| " << m_board[i][j]->getStoneP()->getSymbol() << " ";
			
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
const bool& Board::isOccupied(Position pos) const
{
	return m_board[pos.getRow()][pos.getCol()]->isOccupied();
}
//-------------------------------------------------------------------------------------------------------------------------------------
Stone* Board::getStone(const Position& pos)
{
	if (!pos.isInBoard(getSize()) || !this->isOccupied(pos))
		return nullptr;
	else
		return m_board[pos.getRow()][pos.getCol()]->getStoneP();

}
//-------------------------------------------------------------------------------------------------------------------------------------
Board::Board(const Board& other) 
{
	*this = other;
}
//-------------------------------------------------------------------------------------------------------------------------------------
Board::Board(Board&& other)
{
	*this = move(other);
}
//-------------------------------------------------------------------------------------------------------------------------------------
const Board& Board::operator=(const Board& other)
{
	if (this != &other)
	{
		m_size = other.getSize();
		m_boardType = other.getBoardType();
	}

	return *this;
}
//-------------------------------------------------------------------------------------------------------------------------------------
const Board& Board::operator=(Board&& other)
{
	if (this != &other)
	{
		m_size = other.getSize();
		m_boardType = other.getBoardType();
		m_board = other.m_board;
	}

	return *this;
}
//-------------------------------------------------------------------------------------------------------------------------------------
Board::~Board()
{
	vector<vector<Cell*>> board = getBoard();

	int row,col;
	int size = getSize();

	for (row = 0; row < size; ++row)
	{
		for (col = 0; col < size; ++col)
		{
			delete board[row][col];
		}
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------
void Board::save(ostream& out) const
{
	Board::BOARD_TYPE boardType = getBoardType();
	out.write(rcastcc(&boardType), sizeof(boardType));
	out.write(rcastcc(&m_size), sizeof(m_size));

	for (int i = 0; i < m_size; ++i)
	{
		for (int j = 0; j < m_size; ++j)
		{
			getBoard()[i][j]->save(out);	
		}
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------
void Board::load(istream& in)
{
	in.read(rcastc(&m_boardType), sizeof(m_boardType));
	in.read(rcastc(&m_size), sizeof(m_size));

	m_board.resize(m_size);

	for (int i = 0; i < m_size; ++i)
	{
		m_board[i].resize(m_size);
		for (int j = 0; j < m_size; ++j)
		{
			switch (m_boardType)
			{
			case Board::BOARD_TYPE::CHECKERS:
				m_board[i][j] = new CheckersCell(in);
				break;
			case Board::BOARD_TYPE::AMAZONS:
				m_board[i][j] = new AmazonsCell(in);
				break;
			case Board::BOARD_TYPE::CHESS:
				m_board[i][j] = new ChessCell(in);
				break;
			}
		}
	}
	

}
//-------------------------------------------------------------------------------------------------------------------------------------
