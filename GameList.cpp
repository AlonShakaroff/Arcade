#include "GameList.h"
#include "CheckersGame.h"
#include "AmazonGame.h"
#include "ChessGame.h"
#include <iostream>
using namespace std;

//-------------------------------------------------------------------------------------------------------------------------------------
void GameList::addNewGame(const Game::GAME_TYPE& gameType)
{
	ListNode<Game>* newNode = nullptr;
	try
	{
		newNode = new ListNode<Game>;
	}
	catch (bad_alloc ex)
	{
		cout << "memory allocation failure:" << ex.what() << endl;
		exit(1);
	}
	switch (gameType)
	{
	case Game::GAME_TYPE::CHECKERS:
		try
		{
			newNode->dataP = new CheckersGame;
		}
		catch (bad_alloc ex)
		{
			cout << "memory allocation failure:" << ex.what() << endl;
			exit(1);
		}
		break;

	case Game::GAME_TYPE::AMAZONS:
		try
		{
			newNode->dataP = new AmazonGame;
		}
		catch (bad_alloc ex)
		{
			cout << "memory allocation failure:" << ex.what() << endl;
		}
		break;

	case Game::GAME_TYPE::CHESS:
		try
		{
			newNode->dataP = new ChessGame;
		}
		catch (bad_alloc ex)
		{
			cout << "memory allocation failure:" << ex.what() << endl;
		}
		break; 
	}
	setCurrentGameListNode(newNode);
	insertNodeToEndList(newNode);
}
//-------------------------------------------------------------------------------------------------------------------------------------
void GameList::insertNodeToEndList(ListNode<Game>* newNode)
{
	if (getHead() == nullptr)
	{
		setHead(newNode);
		setTail(newNode);
	}

	newNode->prev = getTail();
	getTail()->next = newNode;
	setTail(newNode);
	getTail()->next = getHead();
	getHead()->prev = getTail();
}
//-------------------------------------------------------------------------------------------------------------------------------------
void GameList::removeCurrentGame()
{
	if (isEmptyList())
		return;

	if (getCurrentGameListNode() == getHead())
	{
		if (getCurrentGameListNode() == getTail())
		{
			setHead(nullptr);
			setTail(nullptr);
			getCurrentGameListNode()->next = nullptr;
			getCurrentGameListNode()->prev = nullptr;
		}

		else
		{
			setHead(getHead()->next);
			getHead()->prev = getTail();
			getTail()->next = getHead();
		}
	}
	else if (getCurrentGameListNode() == getTail())
	{
		setTail(getTail()->prev);
		getTail()->next = getHead();
		getHead()->prev = getTail();
	}

	else
	{
		getCurrentGameListNode()->prev->next = getCurrentGameListNode()->next;
		getCurrentGameListNode()->next->prev = getCurrentGameListNode()->prev;
	}

	ListNode<Game>* temp = getCurrentGameListNode();
	setCurrentGameListNode(temp->next);
	delete temp->dataP;
	delete temp;
}
//-------------------------------------------------------------------------------------------------------------------------------------
void GameList::moveToNextGame()
{
	if (isEmptyList())
		return;
	setCurrentGameListNode(getCurrentGameListNode()->next);
}
//-------------------------------------------------------------------------------------------------------------------------------------
bool GameList::isEmptyList()
{
	if (getHead() == nullptr)
		return true;
	else
		return false;
}
//-------------------------------------------------------------------------------------------------------------------------------------
const bool GameList::isEmptyList() const
{
	if (getHead() == nullptr)
		return true;
	else
		return false;
}
//-------------------------------------------------------------------------------------------------------------------------------------
GameList::~GameList()
{
	ListNode<Game>* curr = getCurrentGameListNode();

	while (curr)
	{
		removeCurrentGame();
		curr = getCurrentGameListNode();
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------
GameList::GameList(GameList&& other)
{
	*this = move(other);
}
//-------------------------------------------------------------------------------------------------------------------------------------
const GameList& GameList::operator =(GameList && other)
{
	if (this != &other)
	{
		delete m_currentGame;
		delete m_head;
		delete m_tail;

		m_currentGame = other.m_currentGame;
		m_head = other.m_head;
		m_tail = other.m_tail;

		other.m_currentGame = nullptr;
		other.m_head = nullptr;
		other.m_tail = nullptr;
	}

	return *this;
}
//-------------------------------------------------------------------------------------------------------------------------------------
