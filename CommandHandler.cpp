#include "CommandHandler.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;
/* Description: The main game loop
 *
 * Big O: O(n) n = commands given until user gives p
 */
void CommandHandler::gameLoop(){
	cout << "=================" << " 2048 " << "=================" << endl;
	printHotKeys();
	while(getCommand()){
		gameState();//checks the game for win or loss
	}
}
/* Description: Checks if the game is in a loss or win state and tells the user
 *
 * Big O: O(1) as the functions inside are O(1)+O(1) (practically)
 */
void CommandHandler::gameState(){
	if(gameStateMessage){
		if(game->loss()){
			cout << "GAME OVER" << endl;
			cout << "Score: " << game->score() << endl;
			cout << "r to restart | p to quit" << endl;
		}
		else if(game->win()){
			cout << "GAME WIN!" << endl;
			cout << "Score: " << game->score() << endl;
			cout << "press y to continue playing | r to restart | p to quit" << endl;
		}
	}

}

/* Description: A menu system for the user to give a command to activate certain functionality
 *
 * Big O: This is a hard one as each individual call can be a different Big O
 * 		  All the gameboard operations should be practically O(1)
 * 		  While the handleSolve() will be O(4^n) n = max height of quadtree set by the user
 */
bool CommandHandler::getCommand(){
	cout << "Score Error: " << game->scoreError() << endl;
	game->print();
	char input;
	cout << "(h for HotKeys)Char: ";
	cin >> input;
	switch(input){
	case'w':
	case's':
	case'd':
	case'a':
		handleMove(input);
		break;
	case 'u':
		handleUndo();
		break;
	case 'r':
		handleReset();
		break;
	case 'h':
		printHotKeys();
		break;
	case 'l':
		handleDisplayLBLoop();
		break;
	case 'y':
		gameStateMessage = !gameStateMessage;//Toggles the win / loss couts
		break;
	case 'k':
		handleSolve(); //the heuristic
		break;
	case 'i':
		changeSolve(); //the height of the heuristic
		break;
	case 'p':
		return false;
		break;
	default:
		cout << "\nNot an input" << endl;
	}
	return true;
}
/* Description: disperses the move commands given by the user
 *
 * Big O: O(1) as the stacks and move functions are all practically O(1)
 */
void CommandHandler::handleMove(char m){
	switch(m){
	case 'w':
		if(game->up()){
			boardStack.push_front(*game);
		}
		break;
	case 's':
		if(game->down()){
			boardStack.push_front(*game);
		}
		break;
	case 'a':
		if(game->left()){
			boardStack.push_front(*game);
		}
		break;
	case 'd':
		if(game->right()){
			boardStack.push_front(*game);
		}
		break;
	}
}
/* Description: Undos the last move to a previous gameboard
 *
 * Big O: O(1) as Im assuming they did the stack correctly
 */
void CommandHandler::handleUndo(){
	if(boardStack.empty()){
		return;
	}
	boardStack.pop_front();
	*game = boardStack.front();
}
/* Description:Resets the board
 *
 * Big O: O(1) as Im assuming they did the stack correctly
 */
void CommandHandler::handleReset(){
	delete game;
	game = new GameBoard;
	boardStack.push_front(*game);
}
/* Description: The menu for the leaderboard.
 *
 * Big O: O(1) if we arent counting the user input
 * 		  O(n) if we are n being user input until p is given.
 */

void CommandHandler::handleDisplayLBLoop(){
	cout << "---TOP TEN PLAYERS---" << endl;
	for(int i =0; i < 10; i++){
		cout << topTen[i] << endl;
	}
	cout << "\n n: Find by name/city | f: Print city's leaderboard | p: exit"
			"\n a: add your score | r: reconfig your rank" << endl;
	while(LBLoopCommand()){
	cout << "\n n: Find by name/city | f: Print city's leaderboard | p: exit"
			"\n a: add your score | r: save to file (Rank will be configured, restart required to see)" << endl;
	}
}
/* Description: The menu loop for leader board interaction
 *
 * Big O: Depends on the choice by the user
 * 		  reConfigRank() will be the worst case
 * 		  at O(nlogn) average.
 *
 */
bool CommandHandler::LBLoopCommand(){
	char inp;
	cout << "Input: ";
	cin >> inp;
	switch(inp){
	case 'f':
		handleCity();
		break;
	case 'n':
		handleName();
		break;
	case 'a':
		addScore();
		break;
	case 'r':
		reConfigRank();
		break;
	case 'p':
		return false;
	default:
		cout << "Invalid key" << endl;
	}
	return true;
}
/* Description: Asks the user for their name and place then stores it in our hashtable
 *
 * Big O: Given the practical aspect of hashing should be O(1) on hashing, finding, and removing
 * 		  the average case will be O(1)
 * 		  but technically the length of the string can effect the big o if its somehow very very long
 * 		  O(n) if counting string length as n
 */
void CommandHandler::addScore(){

	LeaderBoard::NamePlace buffer;
	LeaderBoard finder;
	bool flag = true;
	players++;

	cout << "Username: ";
	cin.ignore();
	getline(std::cin, buffer.name);
	cout << "Place: ";
	getline(std::cin, buffer.place);

	try{
		finder = leadHash->find(buffer);
	}catch(string e){
		flag = false;
	}
	if(flag){
		leadHash->remove(buffer);
		players--;
	}
	finder.namePlace = buffer;
	finder.pointRank.point = game->score();
	finder.pointRank.rank = 999999;
	leadHash->insert(buffer, finder);
}
/* Description: fills a BST with the leaderboard from the hashtable then puts it in order in a txt file
 *
 * Big O: O(n) for the fillFile but the configRank() is average of O(nlogn) or O(mn^2) worst case
 * 		  O(mn^2) n = amount of data , m = max array of the hashtable
 * 		  O(nlogn) average case
 */
void CommandHandler::reConfigRank(){
	if(leadFileFiller != nullptr){
		delete leadFileFiller;
	}
	leadFileFiller = new BST<LeaderBoard>;
	leadHash->configRank(leadFileFiller);
	try{
		leadFileFiller->fillFile(fileLoc, players);
	}catch(string e){
		cout << e << endl;
	}
}
/* Description: Asks the user for their name and place to find
 * 				themselves in the leader boards
 *
 * Big O: Hopefully O(1) as it is calling a hash table find
 * 		  but if we are unlucky it will go through the entire
 * 		  hashtable if we are unlucky with all hash numbers being the same
 * 		  worst case O(n)
 */
void CommandHandler::handleName(){
	LeaderBoard::NamePlace dude; //Player's information for the hash table
	cout << "Username: ";
	cin.ignore();
	getline(std::cin,dude.name);
	cout << "City: ";
	getline(std::cin,dude.place);
	try{
		cout << leadHash->find(dude) << endl;
	}
	catch(string e){
		cout << "You are not in the leader boards" << endl;
	}
}
/* Description: Prompts the user to give a city then fills a BST with the data to be printed in order of
 * 				rank of the city.
 *
 * Big O: A lot of large big O but all of them are summing together
 * 		  SortCity() is the hardest hitter with
 * 		  O(nlogn) as average
 * 		  O(n^2) worst case
 * 		  O(mn^2) worstest case n = number of data values m = array size of the hashtable
 */
void CommandHandler::handleCity(){
	string cit;
	cout << "City: ";
	cin.ignore();
	getline(std::cin, cit);
	if(leadCity != nullptr){
		delete leadCity;
	}
	leadCity = new BST<LeaderBoard>;
	leadHash->SortCity(cit, leadCity);
	leadCity->inorderPrint();
}
/* Description: builds a new quadtree of all possible moves with a set height
 * 				then puts the best as our gameboard
 *
 * Big O: O(4^n) n = max tree height set by the user.
 * 		  Both deleting and building is O(4^n) + O(4^n)
 * 		  so its twice as much worse but the constant 2 is
 * 		  tossed.
 */
void CommandHandler::handleSolve(){
	if(solver != nullptr){
		delete solver;
	}
	solver = new SolveGame(solveMoves);
	solver->buildSolve(game);
	*game = solver->findSolve();
	boardStack.push_front(*game);
	cout << "Moves done: ";
	solver->printMoves();
}

/* Description: Changes the amount of moves our heuristic solver does
 *
 * Big O: O(1)
 */
void CommandHandler::changeSolve(){
	cout << "(WARNING: 4^x moves, keep it low or it will be VERY long)";
	cout << "Enter a number of moves: ";
	cin >> solveMoves;
}

/* Description:Fills our command variables
 *
 * Big O: O(1)
 */
CommandHandler::CommandHandler(){
	game = nullptr;
	leadCity = nullptr;
	leadHash = nullptr;
	players = 0;
	solveMoves = 4;
	solver = nullptr;
	leadFileFiller = nullptr;
}
/* Description: fills the leaderboard and then sets the gameboard up
 *
 * Big O: The gameloop is called here so its technically a much higher
 * 		  big O but waaay more complicated to calculate all the inherited Big Os
 * 		  I will focus on the file operations instead:
 * 		  we are filling a newly created open hash table so the average should be
 * 		  O(n) n = the amount of data in a file
 * 		  O(n^2) n = the amount of data in a file worst case if they all have the
 * 		  same hash value.
 */
void CommandHandler::main(string f){
	ifstream file;
	fileLoc = f;
	file.open(f);
	if(!file){
		throw std::string("File can't be found, sorry have to have an internet connection to play our offline game :)");
	}

	//Max is the number of players in the file and should be at the top with an endl
	string max;
	getline(file, max);
	players = stoi(max);
	leadHash = new LBHasher<LeaderBoard>(2*players, 2); //Hashtable of all our players


	LeaderBoard bufferLB; //Buffer to fill the hash table
	int i = 0;
	while(file >> bufferLB.pointRank.rank >> bufferLB.namePlace.name
				>> bufferLB.namePlace.place >> bufferLB.pointRank.point){
		leadHash->insert(bufferLB.namePlace, bufferLB);
		if(i < 10){
			topTen[i] = bufferLB; //This will be for just printing the top ten players in the world
		}
		i++;
	}
	file.close();
	//Now we start the game.
	game = new GameBoard;
	boardStack.push_front(*game);
	gameLoop();
}

/* Description: Just prints the hotkeys to the console
 *
 * Big O: O(1)
 */
void CommandHandler::printHotKeys(){
	cout << setw(0) << setfill(' ')
			<< "w: up | s: down | a: left | d: right | p: exit | k: quick solve | \n"
			<< "l: LeaderBoards | u: undo | h: help  | r: restart | i: change quick solve steps\n" << endl;
}



/* Description: Destructor
 *
 * Big O: O(1)
 */
CommandHandler::~CommandHandler(){
	delete game;
	delete leadCity;
	delete leadHash;
	players = 0;
}
