#include "include/DataStructures.h" 
#include <iostream>
#include <string>
#include <filesystem>
#include <stdexcept> 

namespace fs = std::filesystem;
using namespace std;

// The Link List's starting pointer must be defined here.
//This is so we can make global changes across all 3 files. 
node *activeHead = NULL; 

const string PATH = (fs::current_path() / "Temp").string();

//Function prototypes for compiler
void append(string filePath, node*& head);
void printList(node* head);

int main() {
	
	//Stack object
	RecoveryStack recoveryStack; 

	cout << "Scanning directory for files: " << PATH << endl;
	// Iterator inside directory 
	for (const auto & entry : fs::directory_iterator(PATH)){
		append(entry.path().string(), activeHead); 
	}
	
	printList(activeHead); 
	
	// To run the program, run build.sh and then run FRS

	
}