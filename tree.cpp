#include "tree.h"

// constructor
RedBlackTree::RedBlackTree() {
	root = NULL;
}

// destructor
RedBlackTree::~RedBlackTree() {
	delete root;
}
// use infix to print out
void RedBlackTree::print() const {
	
	if (root != NULL) {
		cout << "[Infix] ";
		root->print();
	} else {
		cout << "The tree is empty." << endl;
	}
}

// uses prefix to print out visually
void RedBlackTree::visual() const {
	if (root != NULL) {
		root->visual();
	}
}

// method to insert values into tree
void RedBlackTree::insert(int value) {
	
	if (root == NULL) {
		root = new Node(value, NULL);
	} else {
		root->insert(value)->repairInsert(); // repairing from the newly added node - which the insert function returns
		root = root->getRoot(); // gives me new root
	}
	
	root->validate(root);
}

// method to search the tree
bool RedBlackTree::search(int value) const {

	if (root != NULL) {
		if (root->search(value) == NULL) {
			return false;
		} else {
			return true;
		}
	} else {
		return false;
	}
		
}

// method to remove a node from tree
void RedBlackTree::remove(int value) {
	
	if (root != NULL) {
		
		Node* node = root->search(value);
		if (node != NULL) {
			node->remove(root);
			
			if (root != NULL) {
				root->validate(root);
			}
		}
	}	
}