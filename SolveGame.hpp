#pragma once
#include "GameBoard.hpp"
#include <iostream>
using namespace std;
/* Description: A Quadtree of 2048 game boards that contain all potential moves
 *
 * Notes: I messed up with the branches leading to a memory leak as I was only using one
 * 		  branch.
 * 		  For some reason that made the heuristics work perfectly.
 * 		  If I had time I would dive deeper into why as I have theories
 * 		  but I have to submit this project soon.
 */

class SolveGame{
private:
	//Four branches for each direction
	SolveGame * rootUp;
	SolveGame * rootDown;
	SolveGame * rootLeft;
	SolveGame * rootRight;
	//The four potential game boards that a single vertex will hold
	GameBoard * up;
	GameBoard * down;
	GameBoard * left;
	GameBoard * right;

	//For our highscore board and its moves to get there
	static GameBoard highScore;
	static string moves;

	//Amount of moves we will take
	int max = 4;

	void destroy();
	void buildSolve(GameBoard*, int i, string m = "");

public:
	SolveGame();
	SolveGame(int);
	~SolveGame();
	//Will build the tree
	void buildSolve(GameBoard*);
	//returns the highscore board
	GameBoard findSolve();
	//couts the moves to get to the current highscore board
	void printMoves();

	//void printTest(); Test function
};

