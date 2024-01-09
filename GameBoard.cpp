#include "GameBoard.hpp"
#include <forward_list>
#include <iostream>


/* Description: Constructor
 *
 * Big O = O(1) practically as the loop is a set nested loop
 */
using namespace std;
GameBoard::GameBoard(){
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			grid[i][j] = 0;
		}
	}
	placementX = 0;
	placementY = 0;
	grid[placementX][placementY] = 2;
}
/* Description:Destructor
 *
 * Big O = O(1) practically as the loop is a set nested loop
 */
GameBoard::~GameBoard(){
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			grid[i][j] = 0;
		}
	}
}

/* Description: Finds a location and fills it with a 2 on the game board
 *
 * Big O = O(1) practically as the nested loop is only going to be a 4 x 4 always.
 */
void GameBoard::fillSlot(){
	//We can make this random but for now I will have it fill the next slot available
//	if(loss()){
//		return;
//	}
	if(this->placementY == 4){
		this->placementX++;
		if(placementX == 4){
			placementX = 0;
		}
		this->placementY = 0;
	}

	int m = 0;
	for(int i = placementX; ; i++){
		for(int j = placementY; ; j = (j+1)%4){
			m++;
			if(m == 4){
				i = (i+1)%4;
				m = 0;
			}
			if(grid[i][j] == 0){
				grid[i][j] = 2;
				this->placementY++;
				return;
			}
		}
	}
}

/* Description: Directional input, fills the array based on direction
 * 				then combines numbers that are the same then finally
 * 				finishes by filling the direction again.
 *
 * Big O = O(1) practically as the nested loop operations are a known 4 x 4 each always.
 *
 * Logic of each move:
 * 		We must move into empty slots, do the math, then fill the new empty slots again
 * 		they could each be their own function but Im already in this architecture settup
 * 		so Im just going for the cost sunk fallacy strategy
 */
bool GameBoard::up(){
	bool moved = false;

//Fill
	for(int j = 0; j < 4; j++){
		for(int i = 0; i < 4; i++){
			if(grid[i][j] == 0){
				for(int t = i+1; t < 4; t++){
					if(grid[t][j] > 0){
						grid[i][j] = grid[t][j];
						grid[t][j] = 0;
						moved = true;
						break;
					}
				}
			}
		}
	}

//Update
	for(int j = 0; j < 4; j++){
		for(int i = 0; i < 3; i++){
			if(grid[i][j] != 0 && grid[i][j] == grid[i+1][j]){
				grid[i][j] += grid[i+1][j];
				grid[i+1][j] = 0;
				moved = true;
			}
		}
	}

//Fill
	for(int j = 0; j < 4; j++){
		for(int i = 0; i < 4; i++){
			if(grid[i][j] == 0){
				for(int t = i+1; t < 4; t++){
					if(grid[t][j] > 0){
						grid[i][j] = grid[t][j];
						grid[t][j] = 0;
						moved = true;
						break;
					}
				}
			}
		}
	}
	if(moved){
		fillSlot();
	}
	return moved;
}
/* Description: Directional input, fills the array based on direction
 * 				then combines numbers that are the same then finally
 * 				finishes by filling the direction again.
 *
 * Big O = O(1) practically as the nested loop operations are a known 4 x 4 each always.
 */
bool GameBoard::down(){
	bool moved = false;

//Fill
	for(int j = 0; j < 4; j++){
		for(int i = 3; i >= 0; i--){
			if(grid[i][j] == 0){
				for(int t = i-1; t >= 0; t--){
					if(grid[t][j] > 0){
						grid[i][j] = grid[t][j];
						grid[t][j] = 0;
						moved = true;
						break;
					}
				}
			}
		}
	}

//Update
	for(int j = 0; j < 4; j++){
		for(int i = 3; i > 0; i--){
			if(grid[i][j] != 0 && grid[i][j] == grid[i-1][j]){
				grid[i][j] += grid[i-1][j];
				grid[i-1][j] = 0;
				moved = true;
			}
		}
	}

//Fill
	for(int j = 0; j < 4; j++){
		for(int i = 3; i >= 0; i--){
			if(grid[i][j] == 0){
				for(int t = i-1; t >= 0; t--){
					if(grid[t][j] > 0){
						grid[i][j] = grid[t][j];
						grid[t][j] = 0;
						moved = true;
						break;
					}
				}
			}
		}
	}
	if(moved){
		fillSlot();
	}
	return moved;
}
/* Description: Directional input, fills the array based on direction
 * 				then combines numbers that are the same then finally
 * 				finishes by filling the direction again.
 *
 * Big O = O(1) practically as the nested loop operations are a known 4 x 4 each always.
 */
bool GameBoard::left(){
	bool moved = false;

//Fill
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			if(grid[i][j] == 0){
				for(int t = j+1; t < 4; t++){
					if(grid[i][t] > 0){
						grid[i][j] = grid[i][t];
						grid[i][t] = 0;
						moved = true;
						break;
					}
				}
			}
		}
	}

//Update
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 3; j++){
			if(grid[i][j] != 0 && grid[i][j] == grid[i][j+1]){
				grid[i][j] += grid[i][j+1];
				grid[i][j+1] = 0;
				moved = true;
			}
		}
	}

//Fill
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			if(grid[i][j] == 0){
				for(int t = j+1; t < 4; t++){
					if(grid[i][t] > 0){
						grid[i][j] = grid[i][t];
						grid[i][t] = 0;
						moved = true;
						break;
					}
				}
			}
		}
	}
	if(moved){
		fillSlot();
	}
	return moved;
}
/* Description: Directional input, fills the array based on direction
 * 				then combines numbers that are the same then finally
 * 				finishes by filling the direction again.
 *
 * Big O = O(1) practically as the nested loop operations are a known 4 x 4 each always.
 */
bool GameBoard::right(){
	bool moved = false;

//Fill
	for(int i = 0; i < 4; i++){
		for(int j = 3; j >= 0; j--){
			if(grid[i][j] == 0){
				for(int t = j-1; t >= 0; t--){
					if(grid[i][t] > 0){
						grid[i][j] = grid[i][t];
						grid[i][t] = 0;
						moved = true;
						break;
					}
				}
			}
		}
	}

//Update
	for(int i = 0; i < 4; i++){
		for(int j = 3; j > 0; j--){
			if(grid[i][j] != 0 && grid[i][j] == grid[i][j-1]){
				grid[i][j] += grid[i][j-1];
				grid[i][j-1] = 0;
				moved = true;
			}
		}
	}

//Fill
	for(int i = 0; i < 4; i++){
		for(int j = 3; j >= 0; j--){
			if(grid[i][j] == 0){
				for(int t = j-1; t >= 0; t--){
					if(grid[i][t] > 0){
						grid[i][j] = grid[i][t];
						grid[i][t] = 0;
						moved = true;
						break;
					}
				}
			}
		}
	}

	if(moved){
		fillSlot();
	}
	return moved;
}

/* Description: Checks for if 2048 is in the game board
 *
 * Big O = O(1) practically as the nested loop operation are a known 4 x 4 always.
 */
bool GameBoard::win(){
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			if(grid[i][j] == 2048){
				return true;
			}
		}
	}
	return false;
}
/* Description: Checks if the game is in a loss state
 *
 * Big O = O(1) practically as the nested loop operation are a known 4 x 4 always.
 */
bool GameBoard::loss(){
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			if(grid[i][j] == 0){
				return false;
			}
			if(i < 3){
				if(grid[i][j] == grid[i+1][j]){
					return false;
				}
			}
			if(j < 3){
				if(grid[i][j] == grid[i][j+1]){
					return false;
				}
			}
		}
	}
	return true;
}

/* Description: Totals the numbers on the game board and returns the number
 *
 * Big O = O(1) practically as the nested loop operation are a known 4 x 4 always.
 */
int GameBoard::score(){
	int score = 0;
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			score += grid[i][j];
		}
	}
	return score;
}
/* Description: Goes through the board and incentives certain board states based on a weight value provided
 * 				each individual variable we are measuring
 *
 * Big O = O(1) practically as the nested loop operation are a known 4 x 4 each always.
 */
int GameBoard::scoreError(){
	int scoreErr = 0;
	int absCol = 0;
	int absRow = 0;
	int maxTile = 0;
	int maxTileRow, maxTileCol = 0;
	int emptyTiles = 0;
	int edgePenalty = 0;

	//Loop through the graph to compute penalty for adjacent numbers
	for(int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			if(grid[i][j] != 0){

				//Gathering max tile
				if(grid[i][j] > maxTile) {
					maxTile = grid[i][j];
					maxTileRow = i;
					maxTileCol = j;
				}

				//Gathering empty tiles
				if(grid[i][j] == 0) {
					emptyTiles++;
				}

				//Gathering penalty for lesser adjacent numbers
				if(i != 3 && grid[i+1][j] != 0){
					absRow = grid[i+1][j] - grid[i][j];
				}
				if(j != 3 && grid[i][j+1] != 0){
					absCol = grid[i][j+1] - grid[i][j];
				}

			}
			scoreErr += (abs(absRow) + abs(absCol))*4;
		}
	}
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			// Calculate edge row penalty
			if(i == maxTileRow && j == maxTileCol){
				continue;
			}else if(i == maxTileRow || j == maxTileCol) {
				if(grid[i][j] < maxTile / 2) {
					edgePenalty += (maxTile - grid[i][j]) * 2;
				}
			}
		}
	}
    scoreErr += edgePenalty;
	// Reward for having the max tile in a corner
	bool isMaxTileInCorner = ((maxTileRow == 0 && maxTileCol == 0) || (maxTileRow == 3 && maxTileCol == 0) ||
							(maxTileRow == 0 && maxTileCol == 3) || (maxTileRow == 3 && maxTileCol == 3));
	if(isMaxTileInCorner) {
		scoreErr -= maxTile * 50;
	}

	// Reward for empty tiles
	scoreErr -= emptyTiles * 60;



	return scoreErr;
}

/* Description: prints the 2048 game board
 *
 * Big O = O(1) practically as the nested loop operation are a known 4 x 4 always.
 */
void GameBoard::print(){
	std::cout << "Score: " << score() << endl;
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			std::cout << grid[i][j] << "\t";
		}
		std::cout << std::endl;
	}
}
