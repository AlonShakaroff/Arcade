#pragma once
#include "Game.h"
#include <iostream>
#include <list>
using namespace std;

class Arcade
{
public:
	~Arcade();

	enum class MENU_OPTIONS { ADD_GAME = 1, SWITCH_GAME, DELETE_GAME, DISPLAY_GAME, DISPLAY_MOVES, DISPLAY_RISKS, MAKE_MOVE, EXIT, SAVE, LOAD };

	list<Game*>& getGameList() { return m_gameList; }
	const list<Game*>& getGameList() const { return m_gameList; }
	void activateMainMenu();
	void addNewGame(const Game::GAME_TYPE& gameType);
	list<Game*>::iterator& getCurrentGame() { return m_currentGame; }
	const list<Game*>::iterator& getCurrentGame() const { return m_currentGame; }
	void setCurrentGame(list<Game*>::iterator currentGame) { m_currentGame = currentGame; }

	void saveCurrentGame(const string& fileName) const;
	void loadGame(const string& fileName);

private:
	list<Game*> m_gameList;
	list<Game*>::iterator m_currentGame;
	void printMainMenu();
};
