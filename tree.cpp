#include "tree.h"


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
		root->print();
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
		root->insert(value)->repair(); // repairing from the newly added node - which the insert function returns
		root = root->getRoot(); // gives me new root
	}
	
}
