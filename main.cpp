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


	cout << "This program creates a red black tree which is a binary search tree that is roughly even." << endl;

	Node* root = NULL;
	
	
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
		//char number[20];
		//while (inFile >> entry) {}
		while (inFile.good()) {
			
			if (inFile) {
				
				if (root == NULL) {
					root = new Node(entry);
				} else {
					inFile >> entry;
					cout << entry << endl;
					root->insert(entry);
					inFile.ignore();
				}
			}
			
		}
		
	}
	
	// if there is not a file then say so and quit
	else if (!inFile) {
		cout << "Unable to open file " << fileName << endl;// << ".txt" << endl;
		return 0;
	}

	inFile.close();
	
	// while not quitting, ask if they want to print add or quit
	while (true) {
		char input[10] =  "xxxxxxxxx" ;
		
		cout << "You can print [P] or add [A] or quit [Q]" << endl;
		cin >> input;
		
		//cout << "input is [" << input << "]";
		// if print...
		if (strcmp(input, "p") == 0 || strcmp(input, "P") == 0 || strcmp(input, "print") == 0 || strcmp(input, "Print") == 0) {
			
			// check if there is a tree then print out
			
			if (root != NULL) {
				cout << "[Infix] ";
				root->print();
				cout << endl;
				root->visual();
			}
			
		}
		
		// if deleting...
		else if (strcmp(input, "a") == 0 || strcmp(input, "A") == 0 || strcmp(input, "add") == 0 || strcmp(input, "Add") == 0){
			// read in a number to add
			int n = 0;
			cout << "Enter a number to add: ";
			cin >> n;
			cout << endl;
			// here i need to actually add it into the tree
			
		} else {
			break;
		}

	}
	

	return 0;
}
