#include <cstdlib> // for exit(1) to work
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

// function searches the tree and returns the node with a value
Node* Node::search(int value) {

	// go through left side and call recursively
	if (value < data) {
		if (child[L] == LEAF) {
			return NULL;
		}
		
		return child[L]->search(value);
	}
	
	// go through right side and call itself
	if (value > data) {
		if (child[R] == LEAF) {
			return NULL;
		}
		
		return child[R]->search(value);
	}
	
	return this;
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


// this uses the concept maps from CS WISC - this is the second and fourth picture
// http://pages.cs.wisc.edu/~paton/readings/Red-Black-Trees/
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

// this uses the concept maps from CS WISC - this is the first and third picture
// this rotate function is similar to the one used by wikipedia except it need this to be equal to p in the wisc code
// in a left rotate - C1 is left and c2 is right
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
void Node::repairInsert() {
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
		parent->parent->repairInsert();
		return;
	}
	
	// case 4 - p red uncle black
	
	if (this == parent->parent->child[L]->child[R]) {
		
		rotate(L, R);
		
		child[R]->color = RED;
		child[R]->sibling()->color = RED;
		color = BLACK;
		return;
	}
	
	if (this == parent->parent->child[R]->child[L]) {
		
		rotate(R, L);
		
		child[L]->color = RED;
		child[L]->sibling()->color = RED;
		color = BLACK;
		return;
	}
	
	if (this == parent->parent->child[L]->child[L]) {
		parent->rotate2(R, L);
		color = RED;
		sibling()->color = RED;
		parent->color = BLACK;
		return;
	}
	
	parent->rotate2(L, R);
	color = RED;
	sibling()->color = RED;
	parent->color = BLACK;
}

// this function removes a node from the tree
void Node::remove(Node* &root) {
	
	// new root case - updating the root
	if (child[R] == LEAF && child[L] == LEAF && parent == NULL) {
		root = NULL;
		delete this;
		return;
	}
	
	// root one child - updating the root
	// in this case of one child of the root node -- there will only ever be two nodes in the entire tree
	// as such, we are just switching the data in the child to the root and deleting the child
	if ((child[R] == LEAF || child[L] == LEAF) && parent == NULL) {
		
		if (child[R] != LEAF) {
			data = child[R]->data;
			delete child[R];
			child[R] = LEAF;
		} else {
			data = child[L]->data;
			delete child[L];
			child[L] = LEAF;
		}
		return;
	}
	
	// no children just delete
	if (child[L] == LEAF && child[R] == LEAF) {
		
		if (color == BLACK) {
			case_1(root);
		}
		
		parent->child[getChild()] = LEAF;
		delete this;
		return;
	}
	
	// one child case deletion
	if (child[L] == LEAF || child[R] == LEAF) {
		// if the child is on the left then switch and delete
		if (child[L] != LEAF) {
			removeOne(root, L);
		} else { // if child on the right switch and delete
			removeOne(root, R);
		}
		return;
	}
	
	// even if this is root this will work because we aren't modifying the actual root node, but the data inside
	// if there are 2 children not leaves
	if (child[L] != LEAF && child[R] != LEAF) {
		Node* node = child[L]->findRightmostChild();
		data = node->data;
		node->remove(root);
		return;
	}

}

// this will find the rightmost child of this node
Node* Node::findRightmostChild() {
	
	if (child[R] != LEAF) {
		return child[R]->findRightmostChild();
	}
	
	return this;
}

void Node::removeOne(Node* &root, int c) {
	// one child case deletion - this covers the cases for when there is one non leaf child
	
	if (child[c]->color == RED) {
		child[c]->color = BLACK;
	}
	
	// if the child is on the left then switch and delete
	parent->child[getChild()] = child[c];
	child[c]->parent = parent;
	child[c] = LEAF; // so we don't delete it through recursive destructor
	
	
	delete this;
	return;
}

// using wikipedia code for black node being removed with 2 leaves as children
// case 1 is parent is not the root
void Node::case_1(Node* &root) {
	if (parent != NULL) {
		case_2(root);
	}
}

// case 2 is if the sibling is red
void Node::case_2(Node* &root) {
	
	if (sibling()->color == RED) {
		parent->color = RED;
		sibling()->color = BLACK;
		
		if (getChild() == L) { // rotate left
			sibling()->rotate2(L, R);
		} else { // rotate right
			sibling()->rotate2(R, L);
		}
		
		if (parent->parent->parent == NULL) {
			root = parent->parent;
		}
	}
	
	case_3(root);
}

// case 3 is if the parent, sibling and its children are all black
void Node::case_3(Node* &root) {
	
	Node* s = sibling();

	if (parent->color == BLACK && s->color == BLACK && s->child[R]->color == BLACK && s->child[L]->color == BLACK) {
		s->color = RED;
		parent->case_1(root);
	} else {
		case_4(root);
	}
}

// case 4 is for when the parent is red but sibling and children are black
void Node::case_4(Node* &root) {
	
	Node* s = sibling();
	
	if (parent->color == RED && s->color == BLACK && s->child[R]->color == BLACK && s->child[L]->color == BLACK) {
		s->color = RED;
		parent->color = BLACK;
	} else {
		case_5(root);
	}
}

// case 5 is for when left or right child of the sibling is black
void Node::case_5(Node* &root) {
	
	Node* s = sibling();
	if (s->color == BLACK) {
		if (getChild() == L && s->child[R]->color == BLACK && s->child[L]->color == RED) {
			s->color = RED;
			s->child[L]->color = BLACK;
			s->child[L]->rotate2(R, L); // rotate right
		}
		
		else if (getChild() == R && s->child[L]->color == BLACK && s->child[R]->color == RED) {
			s->color = RED;
			s->child[R]->color = BLACK;
			s->child[R]->rotate2(L, R); // rotate left
		}
	}
	
	case_6(root);
}

// case 6
void Node::case_6(Node* &root) {
	
	Node* s = sibling();
	
	s->color = parent->color;
	parent->color = BLACK;
	
	if (getChild() == L) {
		s->child[R]->color = BLACK;
		s->rotate2(L, R); // left rotate
	} else {
		s->child[L]->color = BLACK;
		s->rotate2(R, L); // right rotate
	}
	
	if (parent->parent->parent == NULL) {
		root = parent->parent;
	}
}