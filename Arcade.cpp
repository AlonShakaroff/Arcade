#include "Arcade.h"
#include "CheckersGame.h"
#include "AmazonGame.h"
#include "ChessGame.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


void Arcade::printMainMenu()
{
	cout << "1.  Add game" << endl;
	cout << "2.  Switch to next game" << endl;
	cout << "3.  Delete current game" << endl;
	cout << "4.  Display game" << endl;
	cout << "5.  Display valid moves for Stone (row,col)" << endl;
	cout << "6.  Display risks for cell (row,col)" << endl;
	cout << "7.  Make a move" << endl;
	cout << "8.  Exit" << endl;
	cout << "9.  Save Game" << endl;
	cout << "10. Load Game" << endl;
}

void Arcade::activateMainMenu()
{
	int x, y;
	MENU_OPTIONS choice = MENU_OPTIONS::ADD_GAME;
	Game::GAME_TYPE gameType;
	int choiceNum;

	int curBoardSize;

	Position curPos;
	Position from, to, arrow;
	Stone* curStone;
	string fileName;

	while (choice != MENU_OPTIONS::EXIT)
	{
		try
		{
			printMainMenu();
			cin >> choiceNum;
			choice = static_cast<MENU_OPTIONS>(choiceNum);
			while (choice > MENU_OPTIONS::LOAD || choice < MENU_OPTIONS::ADD_GAME)
			{
				cin >> choiceNum;
				choice = static_cast<MENU_OPTIONS>(choiceNum);
			}

			switch (choice)
			{
			case MENU_OPTIONS::ADD_GAME:
				cout << "Please choose game type:\n1. Checkers\n2. Amazons\n3. Chess" << endl;
				cin >> choiceNum;
				if (choiceNum < 1 || choiceNum > 3)
					throw(range_error("not a valid choice"));
				gameType = static_cast<Game::GAME_TYPE>(choiceNum);
				addNewGame(gameType);
				break;

			case MENU_OPTIONS::SWITCH_GAME:
				setCurrentGame(++getCurrentGame());
				if (getCurrentGame() == getGameList().end())
					setCurrentGame(getGameList().begin());
				break;

			case MENU_OPTIONS::DELETE_GAME:
				if (getGameList().empty()) 
					throw(logic_error("There are no games in play"));

				setCurrentGame(getGameList().erase(getCurrentGame()));
				if (getCurrentGame() == getGameList().end())
					setCurrentGame(getGameList().begin());
				break;

			case MENU_OPTIONS::DISPLAY_GAME:
				if (getGameList().empty()) 
					throw(logic_error("There are no games in play"));

				(*getCurrentGame())->displayGame();
				break;

			case MENU_OPTIONS::DISPLAY_MOVES:
				curBoardSize = (*(getCurrentGame()))->getBoard()->getSize();

				if (getGameList().empty())
					throw(logic_error("There are no games in play"));

				if ((*getCurrentGame())->getGameStatus() == Game::GAME_STATUS::over)
					throw(logic_error("The Game is already over"));

				cin >> x >> y;
				--x;
				--y;
				if (x < 0 || x >= curBoardSize || y < 0 || y >= curBoardSize)
					throw(range_error("Point not in bound"));
				

				curPos.setRow(x);
				curPos.setCol(y);
				curStone = (*getCurrentGame())->getBoard()->getStone(curPos);
				if (curStone)
				{
					curStone->displayValidMoves();
				}
				else 
				{
					throw(logic_error("no stone in point"));
				}
				break;
			case MENU_OPTIONS::DISPLAY_RISKS:

				curBoardSize = (*getCurrentGame())->getBoard()->getSize();

				if (getGameList().empty()) 
					throw(logic_error("There are no games in play"));

				if ((*getCurrentGame())->getGameStatus() == Game::GAME_STATUS::over)
					throw(logic_error("The Game is already over"));

				cin >> x >> y;
				--x;
				--y;
				if (x < 0 || x >(curBoardSize - 1) || y < 0 || y >(curBoardSize - 1)) // add exceptions
					throw(range_error("Point not in bound"));

				{
					vector<vector<Cell*>>& currentBoard = (*getCurrentGame())->getBoard()->getBoard();

					if ((*getCurrentGame())->getIsRiskByCell())
					{
						if (currentBoard[x][y]->getStoneP()) // add exception
							throw(logic_error("Cell is occupied"));

						else if (currentBoard[x][y]->isOccupied()) // add exception
							throw(logic_error("Cell is marked"));

						currentBoard[x][y]->displayThreats();
					}
					else
					{
						if (currentBoard[x][y]->getStoneP())
						{
							currentBoard[x][y]->getStoneP()->displayRisks();
						}
						else
							throw(logic_error("no stone in point"));
					}
				}
				break;

			case MENU_OPTIONS::MAKE_MOVE:
				if (getGameList().empty())
					throw(logic_error("There are no games in play"));

				if ((*getCurrentGame())->getGameStatus() == Game::GAME_STATUS::over)
					throw(logic_error("The Game is already over"));

				int fromX, fromY, toX, toY, arrowX, arrowY;
				cin >> fromX >> fromY >> toX >> toY;
				--fromX;
				--fromY;
				--toX;
				--toY;

				from.setRow(fromX); from.setCol(fromY); to.setRow(toX); to.setCol(toY);

				curBoardSize = (*getCurrentGame())->getBoard()->getSize();

				if ((*getCurrentGame())->getIsTwoStepMove())
				{
					cin >> arrowX >> arrowY;
					--arrowX;
					--arrowY;
					arrow.setRow(arrowX); arrow.setCol(arrowY);

					if (!arrow.isInBoard(curBoardSize))
						throw(range_error("One or more of the points not in bounds"));
				}

				if (!from.isInBoard(curBoardSize) || !to.isInBoard(curBoardSize))
					throw(range_error("One or more of the points not in bounds"));
				

				if (!(*getCurrentGame())->getBoard()->isOccupied(from))
					throw(logic_error("no Stone in position"));

				Stone::PLAYER_ID curPlayerId;
				curPlayerId = (*getCurrentGame())->getBoard()->getStone(from)->getPlayerId();

				if (!(curPlayerId == (*getCurrentGame())->getPlayersTurnId()))
					throw(logic_error("its not this players turn"));

				if ((*getCurrentGame())->getIsTwoStepMove())
				{
					if (!((*getCurrentGame())->getBoard()->getStone(from)->makeMoveTo(from, to, arrow, *(*getCurrentGame()))))
						throw(logic_error("This is not a valid move"));
				}
				else
				{
					if (!((*getCurrentGame())->getBoard()->getStone(from)->makeMoveTo(from, to, *(*(getCurrentGame())))))
						throw(logic_error("This is not a valid move"));
				}
				// A valid move was made
				(*getCurrentGame())->generateValidMovesAndRisks();
				(*getCurrentGame())->updateGameStatus();
				(*getCurrentGame())->displayGame();
				break;

			case MENU_OPTIONS::EXIT:
				cout << "Game terminated successfully";
				break;

			case MENU_OPTIONS::SAVE:
				cout << "Please enter file name: " << endl;;
				cin >> fileName;
				saveCurrentGame(fileName);
				break;
			case MENU_OPTIONS::LOAD:
				cout << "Please enter file name: " << endl;
				cin >> fileName;
				loadGame(fileName);
				break;
			}
		}
		catch (bad_alloc excep)
		{
			cout << "memory allocation failure" << endl;
			exit(1);
		}
		catch (logic_error excep)
		{
			cout << excep.what() << endl;
		}
		catch (range_error excep)
		{
			cout << excep.what() << endl;
		}
		catch (exception excep)
		{
			cout << excep.what() << endl;
		}
		catch (...)
		{
			cout << "unknown error" << endl;
			exit(2);
		}
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------
void Arcade::addNewGame(const Game::GAME_TYPE& gameType)
{
	list<Game*>& gameList = getGameList();

	Game* newGame;

	switch (gameType)
	{
	case Game::GAME_TYPE::CHECKERS:
		newGame = new CheckersGame;
		break;

	case Game::GAME_TYPE::AMAZONS:
		newGame = new AmazonGame;
		break;

	case Game::GAME_TYPE::CHESS:
		newGame = new ChessGame;
		break;
	}

	gameList.push_back(newGame);
	setCurrentGame(--gameList.end());
}
//-------------------------------------------------------------------------------------------------------------------------------------
Arcade::~Arcade()
{
	list<Game*>::iterator curGame = getGameList().begin();

	for (; curGame != getGameList().end(); ++curGame)
	{
		delete *curGame;
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------
void Arcade::saveCurrentGame(const string& filename) const
{
	ofstream out(filename,ios::binary);
	if (!out)
		throw std::exception("File failed to open!");
	(*getCurrentGame())->save(out);
	out.close();
}
//-------------------------------------------------------------------------------------------------------------------------------------
void Arcade::loadGame(const string& filename)
{
	ifstream in(filename, ios::binary);
	if (!in)
		throw std::exception("File failed to open!");
	
	Game::GAME_TYPE gameType;
	in.read(rcastc(&gameType), sizeof(gameType));
	Game* newGame;
	in.seekg(0);

	switch (gameType)
	{
	case Game::GAME_TYPE::CHECKERS:
		newGame = new CheckersGame(in);
		break;
	case Game::GAME_TYPE::AMAZONS:
		newGame = new AmazonGame(in);
		break;
	case Game::GAME_TYPE::CHESS:
		newGame = new ChessGame(in);
		break;
	}
	
	
	getGameList().push_back(newGame);
	setCurrentGame(--getGameList().end());

	newGame->restoreStoneList();
	if(newGame->getGameStatus() == Game::GAME_STATUS::running)
		newGame->generateValidMovesAndRisks();
}
//-------------------------------------------------------------------------------------------------------------------------------------