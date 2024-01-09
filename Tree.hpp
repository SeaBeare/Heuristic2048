#pragma once
/* Description: A tree thats designed for our LeaderBoard object.
 * Notes:
 * We will not be removing anyones records
 * though we could add that functionality later.
 *
 */
template<typename T>
class Tree{
private:
	void destroy();
	void copy(const Tree &copyObj);

public:
	T data;
	Tree * left;
	Tree * right;
	Tree(T);
	~Tree();
	Tree(const Tree&);
	Tree& operator=(const Tree&);
};

template<typename T>
Tree<T>::Tree(T d){
	data = d;
	left = nullptr;
	right = nullptr;
}

/* Description: Copy Constructor
 *
 * Big O: O(n) inherits from the copy function
 */
template<typename T>
Tree<T>::Tree(const Tree &copyObj){
	copy(copyObj);
}
/* Description: = operator overload. Copys rhs Tree to lhs Tree
 *
 * Big O: O(nm)
 * 			n = amount of data on the right tree
 * 			m = amount of data on left tree
 */
template<typename T>
Tree<T>& Tree<T>::operator=(const Tree &copyObj){
	if (this != &copyObj) { // avoid self-assignment
		destroy();
		copy(copyObj);
	}
	return *this;
}
/* Description: Copies a binary search tree into another
 *
 * Big O: O(n) as it is copying the entire tree
 */
template <typename T>
void Tree<T>::copy(const Tree<T> &copyObj) {
    data = copyObj.data;
    if (copyObj.left != nullptr) {
        left = new Tree<T>(copyObj.left);
    } else {
        left = nullptr;
    }
    if (copyObj.right != nullptr) {
        right = new Tree<T>(copyObj.right);
    } else {
        right = nullptr;
    }
}
/* Description: Calls the destroy() for data clean up
 *
 * Big O: O(n) inherits from destroy()
 */
template<typename T>
Tree<T>::~Tree(){
	destroy();
}
/* Description: Recurses through the tree for deletion
 *
 * Big O: O(n) as it is destroying the whole tree
 */
template<typename T>
void Tree<T>::destroy(){
	if(left != nullptr){
		left->destroy();
		delete left;
		left = nullptr;
	}
	if(right != nullptr){
		right->destroy();
		delete right;
		right = nullptr;
	}
}



