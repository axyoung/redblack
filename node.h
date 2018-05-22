#ifndef NODE_H
#define NODE_H
#include <iostream>

// header file for node class

using namespace std;

class Node {
	// http://www.stolerman.net/studies/cs521/red_black_trees.pdf
	// https://en.wikipedia.org/wiki/Red%E2%80%93black_tree
	// http://pages.cs.wisc.edu/~paton/readings/Red-Black-Trees/
	// in the node class function will remove insert and print the nodes in the search tree
	public:
		Node();
		Node(int value, Node* p);
		~Node();
		
		Node* insert(int value);
		void print() const;
		void visual() const;
		int validate(Node* root) const;
		Node* getRoot();
		
		
		void repair();
		
		void case_4();
		
	
	// each node has data and a left and right node
	private:
		enum Color {RED, BLACK}; // Father showed me enums, way to create a data type
		int data;
		Node* child[2]; // this will hold the left and right children
		const int L = 0;
		const int R = 1;
		Node* parent;
		Color color;
		
		static Node* LEAF; // one variable named leaf that will be pointed to
		
		int getChild();
		Node* sibling();
		Node* uncle();
		
		void rotate(int c1, int c2);
		void rotate2(int c1, int c2);
};
#endif