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
		// http://www.stolerman.net/studies/cs521/red_black_trees.pdf
		// https://en.wikipedia.org/wiki/Red%E2%80%93black_tree
		// http://pages.cs.wisc.edu/~paton/readings/Red-Black-Trees/
		void case_1(int value);
		void case_2(int value);
		void case_3(int value);
		void case_4(int value);
	
	// each node has data and a left and right node
	private:
		int data;
		Node* left;
		Node* right;
		bool black;

};
#endif