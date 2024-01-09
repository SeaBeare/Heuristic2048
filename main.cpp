#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <forward_list>
#include "CommandHandler.hpp"
#include "GameBoard.hpp"
#include "LeaderBoard.hpp"
#include "LBHasher.hpp"
#include "BST.hpp"
#include "SolveGame.hpp"

using namespace std;
void testLB();
void testBoard();


int main(){
	CommandHandler gaming;
	string fileLoc = "cs20-final-project-SeaBeare/outputTest.txt";
	try{
	gaming.main(fileLoc);
	} catch(string e){
		cout << e << endl;
	}
	return 0;
}




//IGNORE LEFT FOR POSTERITY SAKE || THESE FUNCTIONS ARE NOT USED.
void testLB(){
	ifstream file;
	file.open("cs20-final-project-SeaBeare/testLB.txt");
	if(!file){
		cout << "nope" << endl;
		return;
	}
	LeaderBoard bufferLB;
	string bufferS;
	string test;
	HashTableOpen<LeaderBoard::NamePlace, LeaderBoard> * f = new LBHasher<LeaderBoard>(10, 2);
	BST<LeaderBoard> * t = new BST<LeaderBoard>;

	while(file >> bufferLB.pointRank.rank >> bufferLB.namePlace.name
			>> bufferLB.namePlace.place >> bufferLB.pointRank.point){
		f->insert(bufferLB.namePlace, bufferLB);
		t->insert(bufferLB);
	}
	LeaderBoard::NamePlace testFind;
	testFind.name = "CBeare";
	testFind.place = "Tracy";
	bufferLB = f->find(testFind);

	//cout << bufferLB << endl;
	t->inorderPrint();

}


void testBoard(){
GameBoard Test;
	char input;
	while(input != '0'){
		Test.print();
		cout << endl;
		cout << "Gimme: ";
		cin >> input;
		switch(input){
		case 'w':
			Test.up();
			break;
		case 's':
			Test.down();
			break;
		case 'd':
			Test.right();
			break;
		case 'a':
			Test.left();
			break;

		}
	}
}



