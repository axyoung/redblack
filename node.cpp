#include "node.h"

// constructor
Node::Node(int value) {
	data = value;
	left = NULL;
	right = NULL;
}

// destructor
Node::~Node() {
	if (left != NULL) {
		delete left;
		left = NULL;
	}

	if (right != NULL) {
		delete right;
		right = NULL;
	}
}
// use infix to print out
void Node::print() const {
	if (left != NULL) {
		left->print();
	}
	
	cout << data << " ";
	
	if (right != NULL) {
		right->print();
	}
	
	return;
}

// uses prefix to print out visually
void Node::visual() const {
	// print current data
	cout << "[Address] " << this << " [Data] " << data;
	// print left child
	if (left != NULL) {
		cout << " [Left Child] " << left << " " << left->data;
	}
	// print right child
	if (right != NULL) {
		cout << " [Right Child] " << right << " " << right->data;
	}
	
	cout << endl;
	
	// repeat for rest of tree
	if (left != NULL) {
		left->visual();
	}
	
	if (right != NULL) {
		right->visual();
	}
	
	return;
}

// method to insert values into tree
void Node::insert(int value) {

	// if the value is smaller it is left
	if (value < data) {
		
		// if get to the end, make a new node
		if (left == NULL) {
			left = new Node(value);
		} else {
			left->insert(value);
		}
	} else {
		
		if (right == NULL) {
			right = new Node(value);
		} else {
			right->insert(value);
		}
	}
	
	return;
}
