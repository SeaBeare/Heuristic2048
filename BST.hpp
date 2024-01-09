#pragma once

#include <fstream>
#include <iostream>
#include "Tree.hpp"
/* Description: Binary Search Tree designed around our leaderboards object
 *
 */
template<typename T>
class BST{
private:
	Tree<T> * root;
	//Private overloads so the caller doesnt have to worry about specifics
	void inorderPrint(Tree<T> *, int&);
	void insert(Tree<T> *, T &);
	void rankingNums(Tree<T>*, int&);
	void fillFile(Tree<T> * , std::ofstream&, int&);
public:
	BST();
	BST(const BST<T>&);
	BST<T>& operator=(BST<T>&);
	~BST();


	void inorderPrint(); //Prints from max to min score // min rank to max rank
	void insert(T&); 	 //Fills left with higher score and right with lower score
	bool isEmpty();		 //Checks if tree is empty (I dont think I ended up using this)
	void rankingNums();  //Reranks the list so that when a new play comes in, it will fix the ranks
	void fillFile(string, int); //fills the file given with the leaderboard. Will fix the ranks as well.
};
/* Description: Constructor
 *
 * Big O: O(1)
 */
template<typename T>
BST<T>::BST(){
	root = nullptr;
}
/* Description:Copy constructor
 *
 * Big O: O(n) it inherits from the Tree copy.
 * 		  n = amount in the copyObj
 */
template<typename T>
BST<T>::BST(const BST<T>& copyObj){
	if(copyObj.root == nullptr){
		root = nullptr;
	}
	else{
		root = new Tree<T>(&copyObj.root);
	}
}
/* Description: = operator overload, just copies right BST to left BST
 *
 * Big O: O(n) inherits from Tree copy construct;
 * 		  n = the amount of data in rightObj
 */
template<typename T>
BST<T>& BST<T>::operator=(BST<T>& rightObj){
	if (this != &rightObj) {
		delete root;
		if (rightObj.root == nullptr) {
			root = nullptr;
		} else {
			root = new Tree<T>(*rightObj.root);
		}
	}
	return *this;
}
/* Description: Deletes the Tree
 *
 * Big O: O(n) inherits from the Tree deletion.
 */
template<typename T>
BST<T>::~BST(){
	delete root;
}

/* Description: inserts data into the Tree
 *
 * Big O: inherits from the called private function
 * 		  Worst case: O(n) Average: O(logn)
 */
template<typename T>
void BST<T>::insert(T &d){
	if(root == nullptr){
		root = new Tree<T>(d);
	}
	else{
		insert(root, d);
	}
}

/* Description: Inserts into the tree from max on the left to the min on the right
 * 				as the min in rank would be the max in score
 *
 * Big O: O(n) in a worst case scenario, practically creating a linked list
 * 		  O(logn) in average case
 */
template<typename T>
void BST<T>::insert(Tree<T> * tree, T &d){

	//We are doing a max tree.
	if(d < tree->data){
		if(tree->right == nullptr){
			tree->right = new Tree<T>(d);
		}
		else{
			insert(tree->right, d);
		}
	}
	else if(d >= tree->data){
		if(tree->left == nullptr){
			tree->left = new Tree<T>(d);
		}
		else{
			insert(tree->left, d);
		}
	}
}


/* Description: Prints a ranking of the binary search tree
 *
 * Big O: O(n) inherited from the called private function
 */
template<typename T>
void BST<T>::inorderPrint(){
	int i = 1;
	inorderPrint(root, i);
}
/* Description: recurses though the binary search tree
 * 				and feeds us a rank of the tree
 *
 * Big O: O(n) as it will go through the entire list
 */
template<typename T>
void BST<T>::inorderPrint(Tree<T> * tree, int& i){
	if(tree != nullptr){
		inorderPrint(tree->left, i);
		std::cout << i++ << ": " << tree->data << std::endl;
		inorderPrint(tree->right, i);
	}
}
/* Description: Checks if the BST is empty
 *
 * Big O: O(1)
 */
template<typename T>
bool BST<T>::isEmpty(){
	if(root == nullptr){
		return true;
	}
	return false;
}

/* Description: Keeps the ranks in order of score.
 * 				Calls the private function to do the work
 *
 * Big O: inherits the called private function's big O
 * 		  O(n)
 */
template<typename T>
void BST<T>::rankingNums(){
	int i = 1; //number for the rank
	rankingNums(root, i);
}

/* Description: This function changes the rank based on score
 * 				it should be used after adding a new player to keep
 * 				rank integrity through the entire list
 *
 * Big O: O(n) always as it will go through the entire tree.
 *
 * Notes:
 * 		  While if I used a sorted array the average would be n/2
 * 		  but the big O would not have changed. Or even perhaps
 * 		  worse as you would have to find the right position first
 * 		  Also I noticed I created this function with the intention
 * 		  to re-rank the user while in program, but I have run out of
 * 		  time, that feature will be added in DLC
 */
template<typename T>
void BST<T>::rankingNums(Tree<T> * tree, int & i){
	if(tree != nullptr){
		rankingNums(tree->left, i);
		root->data.pointRank.rank = i;
		i++;
		rankingNums(tree->right, i);
	}
}

/* Description: Takes in the file location and current amount of players
 * 				then fills the player count before calling a function to
 * 				finish filling the file with the BST data
 *
 * Big O: O(n) n = the data in BST
 *
 */
template<typename T>
void BST<T>::fillFile(string fileName, int players){
	int rankNum = 1;
	ofstream file;
	file.open(fileName);
	if(!file){
		throw std::string("Cant record to a file that doesnt exist!!!");
	}
	file << players << endl;
	fillFile(root, file, rankNum);
	file.close();
}
/* Description: fills the file by highest score to lowest score while also placing the correct rank
 *
 * Big O: O(n) n = amount of players we are storing
 *
 */
template<typename T>
void BST<T>::fillFile(Tree<T> * tree, std::ofstream& file, int& rankNum){
	if(tree != nullptr){
		fillFile(tree->left, file, rankNum);
		file << rankNum << ' ' << tree->data.namePlace.name << ' ' << tree->data.namePlace.place
				<< ' ' << tree->data.pointRank.point << endl;
		rankNum++;
		fillFile(tree->right, file, rankNum);

	}
}
