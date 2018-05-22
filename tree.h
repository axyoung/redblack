#ifndef RedBlackTree_H
#define RedBlackTree_H
#include <iostream>
#include "node.h"

// header file for RedBlackTree class

using namespace std;

class RedBlackTree {

	// in the RedBlackTree class function will remove insert and print the RedBlackTree
	public:
		RedBlackTree();
		~RedBlackTree();
		
		void insert(int value);
		void print() const;
		void visual() const;
		void search(int value);
		void remove(int value);

	
	// each RedBlackTree has data and a left and right RedBlackTree
	private:
		Node* root;

};
#endif