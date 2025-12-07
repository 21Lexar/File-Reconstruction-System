#include "include/DataStructures.h" 
#include <iostream>
#include <string>
#include <filesystem>
using namespace std;

namespace fs = std::filesystem;

const string PATH = (fs::current_path() / "Temp").string();

int main() {
    
    // Object contain AVLTree and RecoveryStack
    FileManager manager;

    cout << "Digital Forensic File Reconstruction System (FRS) Initialized." << endl;
    cout << "Scanning directory for files: " << PATH << endl;
    
    // Scan directory and load files into AVL tree
    manager.scanDirectory(PATH);
    
    // Display initial menu
    manager.clear();
    manager.menu();
    
    // Call menu loop
    manager.getUserChoice();
    
    return 0;
}