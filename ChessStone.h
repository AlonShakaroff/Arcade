#pragma once
#include "Stone.h"
#include <array>
using namespace std;

class ChessBoard;
class ChessStone : public Stone
{
public:
	static constexpr int MAX_RISKS = 12;
	ChessStone(int row, int col) : Stone(row, col) {}																													// ctor
	ChessStone(const ChessStone& other) : Stone(other) { for (int i = 0; i < MAX_RISKS; i++) { m_risks[i] = other.m_risks[i]; } m_risks_index = other.m_risks_index; }
	ChessStone(istream& in);																																			 // load ctor
	virtual ~ChessStone() {};																																			 // dtor

	virtual	void save(ostream& out) const { Stone::save(out); }
	//virtual void load(istream& in);

	void displayRisks() override;
	void addRisk(Position newRisk);
	void setRisksIndex(int newInd) { m_risks_index = newInd; }
	const int getRisksIndex() const { return m_risks_index; }
	int getRisksIndex() { return m_risks_index; }
	virtual void generateValidMoves(ChessBoard& board) = 0;
	bool simulateIsMoveValid(ChessBoard& board, const Position& from, const Position& to); // simulates a move and checks if king is exposed
	virtual bool makeMoveTo(const Position& from, const Position& to, Game& game) override;

protected:
	array<Position, MAX_RISKS>& getRisks() { return m_risks; }
	const array<Position, MAX_RISKS>& getRisks() const { return m_risks; }

	array<Position, MAX_RISKS> m_risks;
	int m_risks_index = 0;
};

