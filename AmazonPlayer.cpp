#include "AmazonPlayer.h"
#include "Amazon.h"

//-------------------------------------------------------------------------------------------------------------------------------------
AmazonPlayer::AmazonPlayer(Stone::PLAYER_ID id) :  m_amazonArrInd(0)
{
	m_id = id;
	if (id == Stone::PLAYER_ID::white)
		m_isPlayersTurn = true;
	else
		m_isPlayersTurn = false;
}
//-------------------------------------------------------------------------------------------------------------------------------------
bool AmazonPlayer::areThereAvailableMoves()
{
	array<Amazon*, NUM_OF_AMAZONS>& amazonArr = getAmazonArr();

	int i;

	for (i = 0; i < NUM_OF_AMAZONS; ++i)
	{
		if (amazonArr[i]->getAmountOfValidMoves() > 0)
			return true;
	}

	return false;
}
//-------------------------------------------------------------------------------------------------------------------------------------
void AmazonPlayer::InsertAmazonToPlayerArr(Amazon* amazon)
{
	m_amazonArr[m_amazonArrInd] = amazon;
	increaseAmazonArrInd();
}
//-------------------------------------------------------------------------------------------------------------------------------------