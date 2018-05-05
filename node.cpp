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
	cout << /*"[Address] " << this <<*/ " [Data] " << data;
	
	if (color == BLACK) {
		cout << " [Black] ";
	} else {
		cout << " [Red] ";
	}
	// print parent
	if (parent != NULL) {
		cout << " [Parent] " /*<< parent << ": " */<< parent->data;
	}
	// print left child
	if (child[L] != LEAF) {
		cout << " [Left Child] " 	/*<< child[L] << ": " */<< child[L]->data;
	}
	// print right child
	if (child[R] != LEAF) {
		cout << " [Right Child] " /*<< child[R] << ": " */<< child[R]->data;
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

// return value is the number of black nodes on this subtree
// father helped me with this part of the code when I was having lots of trouble debugging my code
// this logic checks for errors according to the logic of a red black tree
int Node::validate(Node* root) const {
	
	int errorCount = 0;
	int leftNodeCount = 1;
	int rightNodeCount = 1;
	
	if (child[L] != LEAF) {
		if (child[L]->parent != this) {
			cerr << "left child parent mismatch" << endl;
			errorCount++;
		}
		
		if (child[L]->data > data) {
			cerr << "left child data larger" << endl;
			errorCount++;
		}
		
		leftNodeCount = child[L]->validate(root);
	}
	
	if (child[R] != LEAF) {
		if (child[R]->parent != this) {
			cerr << "right child parent mismatch" << endl;
			errorCount++;
		}
		
		if (child[R]->data < data) {
			cerr << "right child data smaller" << endl;
			errorCount++;
		}
		
		rightNodeCount = child[R]->validate(root);
	}
	
	if (leftNodeCount != rightNodeCount) {
		cerr << "node count mismatch  " << leftNodeCount << " " << rightNodeCount << endl;
		errorCount++;
	}
	
	if (parent == NULL && color == RED) {
		cerr << "red root" << endl;
		errorCount++;
	}
	
	if ((parent == NULL) != (root == this)) {
		cerr << "non root node with null parent" << endl;
		errorCount++;
	}
	
	if (parent != NULL && parent->color == RED && color != BLACK) {
		cerr << "red property X" << endl;
		errorCount++;
	}
	
	if (errorCount > 0) {
		cerr << "errors detected: " << errorCount << "  at: " << data << " address: " << this << endl;
		root->print();
		cout << endl;
		root->visual();
		exit(1);
	}
	
	if (color == BLACK) {
		leftNodeCount++;
	}
	
	return leftNodeCount;
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

// function returns the root
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
/*
void Node::rotate(int c1, int c2) {
	
	Node* newNode = child[c2];
	
	if (newNode == LEAF) {
		return;
	}
	
	child[c2] = newNode->child[c1];
	child[c2]->parent = this;
	newNode->child[c1] = this;
	newNode->parent = parent;
	parent->child[c1] = newNode;
	parent = newNode;
} */

// this uses the concept maps from CS WISC
void Node::rotate(int c1, int c2) {
	//LR->LR
	Node* k = this;
	Node* p = parent;
	Node* g = parent->parent;
	
	k->parent = g->parent;
	
	if (g->parent != NULL) {
		g->parent->child[g->getChild()] = k;
	}
	p->child[c2] = k->child[c1];
	g->child[c1] = k->child[c2];
	p->child[c2]->parent = p;
	g->child[c1]->parent = g;
	g->parent = k;
	p->parent = k;
	k->child[c1] = p;
	k->child[c2] = g;
	
}

// this uses the concept maps from CS WISC
void Node::rotate2(int c1, int c2) {
	//LL->RL
	Node* p = this;
	Node* g = parent;
	
	p->parent = g->parent;
	
	if (g->parent != NULL) {
		g->parent->child[g->getChild()] = p;
	}
	g->parent = p;
	p->child[c1]->parent = g;
	g->child[c2] = p->child[c1];
	p->child[c1] = g;
}

// repairs the node as it is inserted
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
	
	// case 4 - p red uncle black
	
	if (this == parent->parent->child[L]->child[R]) {
		//parent->rotate(L, R);
		rotate(L, R);
		//child[L]->case_4();
		child[R]->color = RED;
		child[R]->sibling()->color = RED;
		color = BLACK;
		/*
		if (parent != NULL && parent->parent != NULL) {
			parent->color = RED;
		}
		*/
		return;
	}
	
	if (this == parent->parent->child[R]->child[L]) {
		//parent->rotate(R, L);
		rotate(R, L);
		//child[R]->case_4();
		child[L]->color = RED;
		child[L]->sibling()->color = RED;
		color = BLACK;
		/*
		if (parent != NULL && parent->parent != NULL) {
			parent->color = RED;
		}
		*/
		return;
	}
	
	if (this == parent->parent->child[L]->child[L]) {
		parent->rotate2(R, L);
		color = RED;
		sibling()->color = RED;
		parent->color = BLACK;/*
		if (parent->parent != NULL && parent->parent->parent != NULL) {
			parent->parent->color = RED;
		}	*/
		return;
	}
	
	parent->rotate2(L, R);
	color = RED;
	sibling()->color = RED;
	parent->color = BLACK;
	/*
	if (parent->parent != NULL && parent->parent->parent != NULL) {
		parent->parent->color = RED;
	}
	*/
}

/*
void Node::case_4() {
	
	if (this == parent->child[L]) {
		parent->parent->rotate(R, L);
	} else {
		parent->parent->rotate(L, R);
	}
	
	color = RED;
	sibling()->color = RED;
	parent->color = BLACK;
	if (parent->parent != NULL && parent->parent->parent != NULL) {
		parent->parent->color = RED;
	}
}
*/