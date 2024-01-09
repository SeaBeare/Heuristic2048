#pragma once

#include "GameBoard.hpp"
#include "LeaderBoard.hpp"
#include "BST.hpp"
#include "LBHasher.hpp"
#include <iostream>
#include <forward_list>
#include <string>
#include "SolveGame.hpp"

/* Description: Handles the commands for the user, main driver of the program
 *
 */
class CommandHandler{
private:
	GameBoard * game;//2048 game board
	LeaderBoard topTen[10];//Top ten from the file
	BST<LeaderBoard> * leadCity;//for when the user wants to sort by their city
	BST<LeaderBoard> * leadFileFiller;//the buffer for when we want to save to file
	HashTableOpen<LeaderBoard::NamePlace, LeaderBoard> * leadHash;//The hashtable of players
	std::forward_list<GameBoard> boardStack;//The stack to allow undo/restarts
	SolveGame * solver;//The heuristics for solving the game for the user
	int solveMoves;//How many moves the heuristics will take
	int players;//The amount of players in our leaderboards. It will help set the max size for the hashtable
	bool gameStateMessage = true;//This is so the user can turn off the game won/loss message
	string fileLoc;//location of our player leaderboard

	//Main game loop
	void gameLoop();
	void gameState();

	//For the game loop
	bool getCommand();
	void handleMove(char);
	void handleUndo();
	void handleReset();
	void printHotKeys();

	//Leaderboard, brings user out of game so that they can search, sort, and browse the list
	void handleDisplayLBLoop();
	bool LBLoopCommand();
	void handleCity();
	void handleName();
	void addScore();
	void reConfigRank();//saves to file as well

	//Our heuristic functions
	void handleSolve();
	void changeSolve();//number of moves the solve does

public:
	CommandHandler();
	void main(std::string);
	~CommandHandler();

};
