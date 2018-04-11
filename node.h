#ifndef NODE_H
#define NODE_H
#include <iostream>

// header file for node class

using namespace std;

class Node {

	// in the node class function will remove insert and print the nodes in the search tree
	public:
		Node(int value);
		~Node();
		
		void insert(int value);
		void print() const;
		void visual() const;
	
	// each node has data and a left and right node
	private:
		int data;
		Node* left;
		Node* right;
		bool black;

};
#endif