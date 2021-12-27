#pragma once
#include "Game.h"
#include "ListNode.h"

class GameList
{
public:

	GameList() : m_head(nullptr), m_tail(nullptr), m_currentGame(nullptr) {}	// ctor
	GameList(GameList&& other);												// move ctor
	~GameList();																// dtor
	const GameList& operator=(GameList&& other);

	ListNode<Game>* getHead() { return m_head; }
	const ListNode<Game>* getHead() const { return m_head; }
	void setHead(ListNode<Game>* newHead) { m_head = newHead; }
	ListNode<Game>* getTail() { return m_tail; }
	const ListNode<Game>* getTail() const { return m_tail; }
	void setTail(ListNode<Game>* newTail) { m_tail = newTail; }
	Game& getCurrentGame() { return *m_currentGame->dataP; }
	const Game& getCurrentGame() const { return *m_currentGame->dataP; }
	ListNode<Game>* getCurrentGameListNode() { return m_currentGame; }
	const ListNode<Game>* getCurrentGameListNode() const { return m_currentGame; }
	void setCurrentGameListNode(ListNode<Game>* newCurrentGame) { m_currentGame = newCurrentGame; }
	void addNewGame(const Game::GAME_TYPE& gameType);
	void removeCurrentGame();
	void moveToNextGame();
	const bool isEmptyList() const;
	bool isEmptyList();

private:
	ListNode<Game>* m_head;
	ListNode<Game>* m_tail;
	ListNode<Game>* m_currentGame;

	void insertNodeToEndList(ListNode<Game>* node);
};
