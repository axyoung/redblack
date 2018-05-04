#include "node.h"

Node* Node::LEAF = new Node;

// this constructor is specifically used for the leaf node
Node::Node() {
	data = 0;
	child[L] = LEAF;
	child[R] = LEAF;
	color = BLACK; // leaves are all black
	parent = NULL;
}

// constructor
Node::Node(int value, Node* p) {
	data = value;
	parent = p;
	child[L] = LEAF;
	child[R] = LEAF;
	if (parent != NULL) {
		color = RED;
		//cout << "red" << endl;
	} else {
		color = BLACK; // this is the case of the root - the only place where the parent is null
		//out << "black" << endl;
	}
}

// destructor
Node::~Node() {
	if (child[L] != LEAF) {
		delete child[L];
		child[L] = LEAF;
	}

	if (child[R] != LEAF) {
		delete child[R];
		child[R] = LEAF;
	}
}
// use infix to print out
void Node::print() const {
	if (child[L] != LEAF) {
		child[L]->print();
	}
	
	cout << data << " ";
	
	if (child[R] != LEAF) {
		child[R]->print();
	}
	
	return;
}

// uses prefix to print out visually
void Node::visual() const {
	// print current data
	cout << "[Address] " << this << " [Data] " << data;
	
	if (color == BLACK) {
		cout << " [Black] ";
	} else {
		cout << " [Red] ";
	}
	// print parent
	if (parent != NULL) {
		cout << " [Parent] " << parent << ": " << parent->data;
	}
	// print left child
	if (child[L] != LEAF) {
		cout << " [Left Child] " << child[L] << ": " << child[L]->data;
	}
	// print right child
	if (child[R] != LEAF) {
		cout << " [Right Child] " << child[R] << ": " << child[R]->data;
	}
	
	cout << endl;
	
	// repeat for rest of tree
	if (child[L] != LEAF) {
		child[L]->visual();
	}
	
	if (child[R] != LEAF) {
		child[R]->visual();
	}
	
	return;
}

// method to insert values into tree, returns the new node
Node* Node::insert(int value) {

	// if the value is smaller it is left
	if (value < data) {
		
		// if get to the end, make a new node
		if (child[L] == LEAF) {
			child[L] = new Node(value, this);
			return child[L];
		} else {
			return child[L]->insert(value);
		}
	} else {
		
		if (child[R] == LEAF) {
			child[R] = new Node(value, this);
			return child[R];
		} else {
			return child[R]->insert(value);
		}
	}
}

Node* Node::getRoot() {
	Node* root = this;
	
	while (root->parent != NULL) {
		root = root->parent; // this will give me the new root
	}
	
	return root;
}

int Node::getChild() {
	// check if you are right or left child
	if (this == parent->child[L]) {
		return L;
	}
	
	return R;
}

Node* Node::sibling() {
	return parent->child[L + R - getChild()];
}

Node* Node::uncle() {
	return parent->sibling();
}

void Node::rotate() {
	Node* newNode = child[L + R - getChild()];
	
	if (newNode == LEAF) {
		return;
	}
	
	child[L + R - getChild()] = newNode->child[getChild()];
	newNode->child[getChild()] = this;
	newNode->parent = parent;
	parent = newNode;
}

void Node::repair() {
	// will go through the cases to repair the tree when adding in a node to the tree
	
	// case 1 - root,
	if (parent == NULL) {
		color = BLACK;
		return;
	}
	
	// case 2 - parent black
	if (parent->color == BLACK) {
		return;
	}
	
	// case 3, parent and uncle are red, but need to call recursively in case grandparent is the root
	if (uncle()->color == RED) {
		parent->color = BLACK;
		uncle()->color = BLACK;
		parent->parent->color = RED;
		parent->parent->repair();
		return;
	}
	
	// case 4 - NEED TO WRITE ROTATE FUNCTION AND CASE 4 CODE 
	if (this == parent->parent->child[L]->child[R]) {
		parent->rotate();
		child[L]->case_4();
	}
	
	if (this == parent->parent->child[R]->child[L]) {
		parent->rotate();
		child[R]->case_4();
	}
}

// wikipedia :)
void Node::case_4() {
	
	if (this == parent->child[L]) {
		parent->parent->rotate();
	} else {
		parent->parent->rotate();
		parent->color = BLACK;
		parent->parent->color = RED;
	}
	
}