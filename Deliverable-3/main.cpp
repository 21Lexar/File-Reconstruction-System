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

void clearScreen(){
	cout << "\033[2J\033[1;1H";
}

void displayMenu(){
	cout << "File Reconstruction System\n";
	cout << "1. Delete\n";
	cout << "2. Recover\n";
	cout << "3. List\n";
	cout << "4. Quit\n";
}

void getUserChoice(){
	int choice;
	cout << "Enter your choice: "; cin >> choice;
	switch(choice){
		case 1:
			break;
		case 2:
			break;
		case 3: 
			break;
		case 4: 
			break;
		default:
			clearScreen();
			displayMenu();
			getUserChoice();
			break;
			
	}
}

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
