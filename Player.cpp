#pragma once
#include "Player.h"
#include <iostream>
using namespace std;

//-------------------------------------------------------------------------------------------------------------------------------------
void Player::save(ostream& out) const
{
	out.write(rcastcc(&m_id), sizeof(m_id));
	out.write(rcastcc(&m_isPlayersTurn), sizeof(m_isPlayersTurn));
	out.write(rcastcc(&m_didPlayerWin), sizeof(m_didPlayerWin));
}
//-------------------------------------------------------------------------------------------------------------------------------------
void Player::load(istream& in)
{
	in.read(rcastc(&m_id), sizeof(m_id));
	in.read(rcastc(&m_isPlayersTurn), sizeof(m_isPlayersTurn));
	in.read(rcastc(&m_didPlayerWin), sizeof(m_didPlayerWin));
}
//-------------------------------------------------------------------------------------------------------------------------------------