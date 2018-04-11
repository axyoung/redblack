/*
 * Red Black Tree Insertion
 *
 * A program that creates a red black binary search tree from a series of numbers in a file.
 * The tree will be able to enter a single number which gets inserted into the tree.
 * It will also print out a representation of a tree
 *
 * class: C++, Galbraith
 * 
 * This code implements psuedo-code from https://en.wikipedia.org/wiki/Red%E2%80%93black_tree
 * 
 * made by: Alex Young
 * last updated: 4/11/2018
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include "node.h"

using namespace std;


int main () {

	char entry[10];
	cout << "This program creates a red black tree which is a binary search tree that is roughly even." << endl;

	char fileName[25];
	cout << "Please enter the name of the file you wish to read into the red black tree: ";
	cin.get(fileName, sizeof(fileName));
	cin.get();
	// use ifstream to open the file
	ifstream inFile;
	
	inFile.open(fileName);

	// if there is a file then read in the values separated by commas
	if (inFile.is_open()) {
		cout << "Opening file..." << endl;
		int entry;
		char number[20];
		//while (inFile >> entry) {}
		while (inFile.good()) {
			inFile.getline(number, 1000, ',');
		}
		
		tree[i] = 0;
	}
	
	// if there is not a file then say so and quit
	else if (!inFile) {
		cout << "Unable to open file " << fileName << endl;// << ".txt" << endl;
		return 0;
	}

	inFile.close();

	}
	

	return 0;
}
