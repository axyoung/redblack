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
 * last updated: 5/4/2018
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include "tree.h"

using namespace std;


int main () {


	cout << "This program creates a red black tree which is a binary search tree that is roughly even." << endl;

	RedBlackTree tree;
	
	char choose[10] =  "xxxxxxxxx" ;
		
	cout << "You choose to start by inserting a file or starting with an empty tree. Type [F] to start with inserting a file and [E] for an empty tree." << endl;
	cin >> choose;
	cin.get();
	
	//when first opening the file the user can choose to open a file or start with an empty file
	if (strcmp(choose, "f") == 0 || strcmp(choose, "F") == 0 || strcmp(choose, "file") == 0 || strcmp(choose, "File") == 0) {
	
		char fileName[25];
		cout << "Please enter the name of the file you wish to read into the red black tree." << endl;
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
				inFile >> entry;
				
				if (inFile) {
					cerr << entry << " ";
					
					// when entering in numbers they will be removed if negative
					if (entry < 0) {
						tree.remove(-entry);
					} else {
						tree.insert(entry);
					}
					
					inFile.ignore();
				}	
			}
			cout << endl;
		}
		
		// if there is not a file then say so and quit
		else if (!inFile) {
			cout << "Unable to open file " << fileName << endl;// << ".txt" << endl;
			return 0;
		}

		inFile.close();
	} else {
		int n = 0;
		cout << "Enter a number to add: ";
		cin >> n;
		tree.insert(n);
		cout << endl;
	}
		
	
	// while not quitting, ask if they want to print add or quit
	while (true) {
		char input[10] =  "xxxxxxxxx" ;
		
		cout << "You can print [P], add [A], search [S], remove [R] or quit [Q]" << endl;
		cin >> input;
		
		//cout << "input is [" << input << "]";
		// if print...
		if (strcmp(input, "p") == 0 || strcmp(input, "P") == 0 || strcmp(input, "print") == 0 || strcmp(input, "Print") == 0) {
			
			// check if there is a tree then print out
		
			tree.print();
			cout << endl;
			tree.visual();
			
		}
		
		// if search...
		else if (strcmp(input, "s") == 0 || strcmp(input, "S") == 0 || strcmp(input, "search") == 0 || strcmp(input, "Search") == 0) {
			
			// read in a number to search
			int n = 0;
			cout << "Enter a number to search for: ";
			cin >> n;
			if (tree.search(n) == false) {
				cout << "The value " << n << " is not in the tree." << endl;
			} else {
				cout << "The value " << n << " is in the tree." << endl;
			}
		}
		
		// if remove...
		else if (strcmp(input, "r") == 0 || strcmp(input, "R") == 0 || strcmp(input, "remove") == 0 || strcmp(input, "Remove") == 0) {
			
			// read in a number to remove
			int n = 0;
			cout << "Enter a number to remove: ";
			cin >> n;
			tree.remove(n);
			cout << endl;
			
		}
		
		// if adding...
		else if (strcmp(input, "a") == 0 || strcmp(input, "A") == 0 || strcmp(input, "add") == 0 || strcmp(input, "Add") == 0){
			// read in a number to add
			int n = 0;
			cout << "Enter a number to add: ";
			cin >> n;
			tree.insert(n);
			cout << endl;
			
		} else {
			break;
		}

	}
	
	return 0;
}
