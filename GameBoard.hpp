#pragma once

#include <cmath>
/* Description: Our 2048 game
 *
 */
class GameBoard{
private:
	//For the filling of the new number after a move
	int placementX;
	int placementY;
	void fillSlot();

	//The gameboard itself
	int grid[4][4];

public:
	GameBoard();
	~GameBoard();
	//Moves
	bool up();
	bool down();
	bool left();
	bool right();
	//GameState
	bool win();
	bool loss();
	//Display the game board
	void print();
	//Score totals the amount on board
	int score();
	//The error to be used for our heuristics
	int scoreError();
};
