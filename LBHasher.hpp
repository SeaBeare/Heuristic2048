#pragma once

#include "HashTableOpen.hpp"
#include "Hasher.hpp"
#include "LeaderBoard.hpp"
#include <string>

using namespace std;
/* Description: A hash calculator for our hashtable designed around our LeaderBoard obj
 *
 */
template<typename Val>
class LBHasher : public HashTableOpen <LeaderBoard::NamePlace, Val>{
protected:
	int hash(const LeaderBoard::NamePlace&) const override;

	int foldNum;

public:

	LBHasher(int maxSize = 100, int fold = 2);
};

/* Description: sets the number of folds we will do for our hash function
 *
 * Big O: O(1)
 */
template<typename Val>
LBHasher<Val>::LBHasher(int maxSize, int fold) : HashTableOpen<LeaderBoard::NamePlace, Val>(maxSize) {
	this->foldNum = fold;
}
/* Description: calls the hashing functions to give us a proper hash number for the table
 *
 * Big O: Technically its O(n^2) n = size of string which is inherited from hashString func
 * 		  but strings will be so short it might as well be O(1)
 */
template<typename Val>
int LBHasher<Val>::hash(const LeaderBoard::NamePlace& k) const{
	return hashString(k.name, foldNum) + hashString(k.place, foldNum);
}
