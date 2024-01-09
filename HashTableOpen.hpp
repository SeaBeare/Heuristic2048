#pragma once

#include <string>

/* Description: An Open HashTable for our leaderboard
 *
 */
template<typename Key, typename Val>
class HashTableOpen{
protected:
	struct Record{
		Key k;
		Val v;
		Record() : k(Key()), v(Val()){}
		Record(Key x, Val y) : k(x), v(y){}
	};
	struct Node{
		Record r;
		Node * next;
		Node(Record record = Record(), Node * node = nullptr) : r(record), next(node){}
	};

	int M;

	Node ** ht;

	virtual int hash(const Key&) const = 0;

public:
	HashTableOpen(int = 100);
	virtual ~HashTableOpen();

	virtual void clear();
	virtual Val find(Key&);
	virtual void insert(Key&, Val&);
	virtual void remove(Key&);

	void SortCity(std::string&, BST<LeaderBoard>*);
	void configRank(BST<LeaderBoard>*);

};
/* Description: Constructor
 *
 * Big O: O(n) n = maxSize
 */
template<typename Key, typename Val>
HashTableOpen<Key, Val>::HashTableOpen(int maxSize) {
	ht = new Node *[maxSize];
	M = maxSize;
	for(int i = 0; i < M; i++){
		ht[i] = nullptr;
	}
}

/* Description: Destructor
 *
 * Big O: O(n) inherits the clear
 * 			which might be O(mn) in worst case explained below.
 */
template<typename Key, typename Val>
HashTableOpen<Key, Val>::~HashTableOpen() {
	clear();
	delete [] ht;
}
/* Description: Destructs the linked lists in the array
 *
 * Big O: O(n) n = amount of data
 * 			   While it loops through the array then the linked lists
 * 			   I believe the math will keep it O(n) on average
 * 			   though worst case is O(mn) if n = Max array size and m = amount of data
 */
template<typename Key, typename Val>
void HashTableOpen<Key, Val>::clear() {
	Node * looper;
	Node * deleter;
	for(int i = 0; i < M; i++){
		if(ht[i] != nullptr){
			looper = ht[i];
			deleter = ht[i];
			while(looper != nullptr){
				looper = looper->next;
				delete deleter;
				deleter = looper;
				ht[i] = looper;
			}
		}
	}
}
/* Description: Takes a key to return a value in the hashtable
 *
 * Big O: O(1) on average but if the values are on all one hash location
 * 				it will be O(n) n = amount of data.
 */
template<typename Key, typename Val>
Val HashTableOpen<Key, Val>::find(Key &k){
	int hashed = hash(k) % M;
	if(ht[hashed] == nullptr){
		throw std::string("Find Error: Does not exist");
	}

	if(ht[hashed]->r.k == k){
		return ht[hashed]->r.v;
	}

	Node * looper = ht[hashed];
	while(looper->r.k != k){
		looper = looper->next;
		if(looper == nullptr){
			throw std::string("Find Error: location exists but no matching key");
		}
	}
	return looper->r.v;
}
/* Description: Takes a key and val and inserts into the hash table
 *
 * Big O: O(1) average
 * 			   though worst case O(n) n = the amount of data already in the list
 * 			   if they all have the same hash value
 */
template<typename Key, typename Val>
void HashTableOpen<Key, Val>::insert(Key &k,Val &v) {
	int hashed = hash(k) % M;
	if(ht[hashed] == nullptr){
		ht[hashed] = new Node;
		ht[hashed]->next = nullptr;
		ht[hashed]->r.v = v;
		ht[hashed]->r.k = k;
		return;
	}
	Node * looper = ht[hashed];
	while(looper->next != nullptr){
		looper = looper->next;
	}
	looper->next = new Node;
	looper = looper->next;
	looper->r.k = k;
	looper->r.v = v;
	looper->next = nullptr;
	return;

}
/* Description: Removes from the hash table by a given key
 *
 * Big O: O(1) average
 * 			   but if all hash values are the same, it will be
 * 			   O(n) n = all data
 */
template<typename Key, typename Val>
void HashTableOpen<Key, Val>::remove(Key &k) {
	int hashed = hash(k) % M;
	if(ht[hashed] == nullptr){
		throw std::string("Remove Error: Does not exist");
	}

	Node * deleter = ht[hashed];
	if(ht[hashed]->r.k == k){
		ht[hashed] = ht[hashed]->next;
		delete deleter;
		return;
	}

	Node * looper = ht[hashed];
	while(looper->next->r.k != k){
		if(looper->next == nullptr){
			throw std::string("Find Error: location exists but no matching key");
		}
		looper = looper->next;
	}
	deleter = looper->next;
	looper->next = deleter->next;
	delete deleter;
	return;
}

/* Description: Takes a city name and a BST to fill with that data
 *
 * Big O: O(n^2) is the worst case as insert for BST is O(n)
 * 				 or potentially O(mn^2) if the hash table is
 * 				 in worst case n = data to be inserted, m = array of hashtable
 * 	    O(nlogn) average given that O(logn) is BST insert() average;
 */
template<typename Key, typename Val>
void HashTableOpen<Key,Val>::SortCity(std::string& cit, BST<LeaderBoard>* ld){
	Node* looper = ht[0];
	for(int i = 0; i < M; i++){
		if(ht[i] != nullptr){
			looper = ht[i];
			while(looper != nullptr){
				if(looper->r.k.place == cit){
					ld->insert(looper->r.v);
				}
				looper = looper->next;
			}
		}
	}
	return;
}
/* Description: Takes a BST, fills it up from the hashtable
 * 				then calls a function to rerank everyone in the BST
 *
 * Big O: similiar to the above function but with the addition of a inorder recursion
 * 		  O(mn^2) in absolute worst case m = hashtable array size n = amount of data
 * 		  O(nlogn) for average
 * 		  the rankingNums() inorder recursion doesnt change big o as it would be
 * 		  O(n)+O(nlogn).
 */
template<typename Key, typename Val>
void HashTableOpen<Key,Val>::configRank(BST<LeaderBoard>* ld){
	Node* looper = ht[0];
	for(int i = 0; i < M; i++){
		if(ht[i] != nullptr){
			looper = ht[i];
			while(looper != nullptr){
				ld->insert(looper->r.v);
				looper = looper->next;
			}
		}
	}
	ld->rankingNums();
	return;
}

