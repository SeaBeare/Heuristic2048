#include "SolveGame.hpp"

GameBoard SolveGame::highScore;
string SolveGame::moves = "";

/* Description: Constructors
 *
 * Big O: O(1) for both
 *
 */
SolveGame::SolveGame(){
	rootUp = nullptr;
	rootDown = nullptr;
	rootLeft = nullptr;
	rootRight = nullptr;
	up = nullptr;
	down = nullptr;
	left = nullptr;
	right = nullptr;

}
SolveGame::SolveGame(int m){
	rootUp = nullptr;
	rootDown = nullptr;
	rootLeft = nullptr;
	rootRight = nullptr;
	up = nullptr;
	down = nullptr;
	left = nullptr;
	right = nullptr;
	max = m;
}

/* Description: Destructor
 *
 * Big O:O(4^n) inherited from destroy()
 *
 */
SolveGame::~SolveGame(){
	destroy();
}
/* Description: Loops through the quadtree and destroys all the edges and vertices
 *
 * Big O: O(4^n) n = max height of the quadtree
 *
 */
void SolveGame::destroy(){
	if(rootUp != nullptr){
		rootUp->destroy();
		delete rootUp;
		rootUp = nullptr;
	}
	if(rootDown != nullptr){
		rootDown->destroy();
		delete rootDown;
		rootDown = nullptr;
	}
	if(rootLeft != nullptr){
		rootLeft->destroy();
		delete rootLeft;
		rootLeft = nullptr;
	}
	if(rootRight != nullptr){
		rootRight->destroy();
		delete rootRight;
		rootRight = nullptr;
	}

	if(up != nullptr){
		delete up;
		up = nullptr;
	}
	if(left != nullptr){
		delete left;
		left = nullptr;
	}
	if(down != nullptr){
		delete down;
		down = nullptr;
	}
	if(right != nullptr){
		delete right;
		right = nullptr;
	}
}
/* Description:builds the quadtree based on a given game board
 *
 * Big O: O(4^n) n = height of the tree given which is "max" here
 */
void SolveGame::buildSolve(GameBoard* g){
	int m = max;
	if(g->loss()){
		cout << "You lost, sorry the computer cant help you now" << endl;
		moves = "None";
		highScore = *g;
		return;
	}
	highScore = *g;
	moves = "";
	buildSolve(g, m);
}
/* Description: builds a quadtree based on a given game board then
 * 				at the leafs it will choose the best board position
 *
 * Big O: O(4^n) n = height of the tree given in the form of i here
 */
void SolveGame::buildSolve(GameBoard * game, int i, string mov){
	//This is for checking the raw output for score error adjustment
	//cout << "Score Error: " << game->scoreError() << endl;
	//game->print();


	if(i == 0){
		//This is for making our first leaf made our base highscore
		if(highScore.score() < game->score()){
			moves = mov;
			highScore = *game;
			//This is for the actual updating. scoreError gives best outcome in the lowest numbers.
		} else if(game->score() == highScore.score()){
			if(game->scoreError() < highScore.scoreError()){
				moves = mov;
				highScore = *game;
			}
		}
		return;
	}
	i--;

	//Our gameboards
	up = new GameBoard;
	down = new GameBoard;
	left = new GameBoard;
	right = new GameBoard;
	*up = *game;
	*down = *game;
	*right = *game;
	*left = *game;
	string moveBuffer;
	moveBuffer = moveBuffer + mov; //contains all the previous moves to get to this recursed state.

	//The move direction function passes a bool so we know if there was actual movement.
	//Otherwise this should end the recursion.
	if(up->up()){
		rootUp = new SolveGame;
		rootUp->buildSolve(up, i, moveBuffer + "up ");
	}else{
		rootUp = nullptr;
		delete up;
		up = nullptr;
	}
	if(down->down()){
		rootDown = new SolveGame;
		rootDown->buildSolve(down, i, moveBuffer + "down ");
	}else{
		rootDown = nullptr;
		delete down;
		down = nullptr;
	}
	if(left->left()){
		rootLeft = new SolveGame;
		rootLeft->buildSolve(left, i, moveBuffer + "left ");
	}else{
		rootLeft = nullptr;
		delete left;
		left = nullptr;
	}
	if(right->right()){
		rootRight = new SolveGame;
		rootRight->buildSolve(right, i, moveBuffer + "right ");
	}else{
		rootRight = nullptr;
		delete right;
		right = nullptr;
	}
	return;
}
/* Description: returns the highscore game board
 *
 * Big O: O(1)
 */
GameBoard SolveGame::findSolve(){
	return highScore;
}
/* Description: prints the moves for the highscore game board
 *
 * Big O: O(1)
 */
void SolveGame::printMoves(){
	cout << moves << endl;
}

// IGNORE, ANOTHER TEST FUNCTION KEPT FOR PROSTERITY
//void SolveGame::printTest(){
//	if(this == nullptr){
//		return;
//	}
//	cout << "Root: " << endl;
//	if(up != nullptr){
//		up->print();
//	}
//	if(down != nullptr){
//		down->print();
//	}
//	if(left != nullptr){
//		left->print();
//	}
//	if(right != nullptr){
//		right->print();
//	}
//	cout << "End root" << endl;
//	rootUp->printTest();
//	rootDown->printTest();
//	rootLeft->printTest();
//	rootRight->printTest();
//}
