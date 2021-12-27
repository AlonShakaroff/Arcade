#include "CheckersPlayer.h"
#include "Board.h"

//-------------------------------------------------------------------------------------------------------------------------------------
CheckersPlayer::CheckersPlayer(Stone::PLAYER_ID id, Board& board)
{
	m_id = id;
	
	initializeStoneList(board, id);

	if (id == Stone::PLAYER_ID::black)
		m_isPlayersTurn = true;
	else
		m_isPlayersTurn = false;
}
//-------------------------------------------------------------------------------------------------------------------------------------
void CheckersPlayer::initializeStoneList(Board& board, Stone::PLAYER_ID id)
{
	int row, col;
	int size = board.getSize();
	Stone::PLAYER_ID startingPlayer;
	
	startingPlayer = Stone::PLAYER_ID::black;

	if (id == startingPlayer)
	{
		for (row = 0; row < 3; row++)
		{
			for (col = 0; col < size; col++)
			{
				if (board.getBoard()[row][col]->getStoneP() != nullptr)
					getStoneList().push_back((board.getBoard()[row][col]->getStoneP()));
			}
		}
	}
	else
	{
		for (row = 5; row < size; row++)
		{
			for (col = 0; col < size; col++)
			{
				if (board.getBoard()[row][col]->getStoneP() != nullptr)
					getStoneList().push_back((board.getBoard()[row][col]->getStoneP()));
			}
		}
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------
bool CheckersPlayer::areThereAvailableMoves()
{
	list<Stone*>::iterator curr = getStoneList().begin();

	while (curr != getStoneList().end())
	{
		if ((*curr)->getAmountOfValidMoves() != 0)
			return true;
		++curr;
	}
	return false;
}
//-------------------------------------------------------------------------------------------------------------------------------------
