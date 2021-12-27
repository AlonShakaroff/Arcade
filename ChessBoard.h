#pragma once
#include "Board.h"
class Stone;

class ChessBoard : public Board
{
public:
	static constexpr int SIZE = 8;

	ChessBoard();									  // ctor
	ChessBoard(const ChessBoard& other);			  // cpy ctor
	ChessBoard(istream& in) : Board(in) { load(in); } // load ctor
	const ChessBoard& operator=(const ChessBoard& other);

	virtual	void save(ostream& out) const;
	virtual void load(istream& in);

	bool isKingSafe(Stone::PLAYER_ID playerId);
	Position& getCurKingPosWhite() { return m_curKingPosWhite; }
	const Position& getCurKingPosWhite() const { return m_curKingPosWhite; }
	Position& getCurKingPosBlack() { return m_curKingPosBlack; }
	const Position& getCurKingPosBlack() const { return m_curKingPosBlack; }
	void setCurKingPosWhite(Position newKingPosWhite) { m_curKingPosWhite = newKingPosWhite; }
	void setCurKingPosBlack(Position newKingPosBlack) { m_curKingPosBlack = newKingPosBlack; }

private:
	Position m_curKingPosWhite;
	Position m_curKingPosBlack;
};

