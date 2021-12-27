#pragma once
#include "Position.h"
#include <vector>

using namespace std;

class Board;
class Game;

class Stone
{
public:
	Stone(istream& in);								//load ctor
	Stone(const Stone& other);						//cpy ctor
	Stone(Stone&& other);							//move ctor
	virtual ~Stone() {};							// dtor
	const Stone& operator=(const Stone& other);
	const Stone& operator=(Stone&& other);

	virtual	void save(ostream& out) const;
	virtual void load(istream& in);

	enum class PLAYER_ID { black, white };
	enum class STONE_TYPE { CHECKERS_STONE, AMAZON, BISHOP, KING, KNIGHT, PAWN, QUEEN, ROOK, NO_STONE };

	PLAYER_ID& getPlayerId() { return m_playerID; }
	const PLAYER_ID& getPlayerId() const { return m_playerID; }
	void setPlayerId(const PLAYER_ID& playerId) { m_playerID = playerId; }
	Position& getPosition() { return m_position; }
	const Position& getPosition() const { return m_position; }
	void setPosition(const Position& position) { m_position = position; }
	void addValidMove(const Position& newPos);
	vector<Position>& getValidMoves() { return m_valid_moves; }
	const vector<Position>& getValidMoves() const { return m_valid_moves; }
	void displayValidMoves();
	void setValidMovesIndex(int newInd) { m_valid_moves_index = newInd; }
	const int getValidMovesIndex() const { return m_valid_moves_index; }
	int getValidMovesIndex() { return m_valid_moves_index; }
	const int getAmountOfValidMoves() const;
	int getAmountOfValidMoves();
	const char getSymbol() { return m_symbol; }
	void setSymbol(char symbol) { m_symbol = symbol; }
	STONE_TYPE& getStoneType() { return m_stoneType; }
	const STONE_TYPE& getStoneType() const { return m_stoneType; }
	virtual void moveStoneTo(const Position& to);
	virtual bool makeMoveTo(const Position& from, const Position& to, Game& game) { return false; }
	virtual bool makeMoveTo(const Position& from, const Position& to, const Position& arrow, Game& game) { return false; }

	virtual void displayRisks() {}

protected:
	Stone(int row, int col); // ctor
	
	Position m_position;
	vector<Position> m_valid_moves;
	int m_valid_moves_index = 0;
	PLAYER_ID m_playerID;
	char m_symbol;
	STONE_TYPE m_stoneType;
};

