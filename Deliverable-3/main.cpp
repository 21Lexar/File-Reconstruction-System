#include "include/DataStructures.h" 
#include <iostream>
#include <string>
using namespace std;

int main() {
    
    // Object contain AVLTree and RecoveryStack
    FileManager manager;

    cout << "Digital Forensic File Reconstruction System (FRS) Initialized." << endl;
    
    // Call menu loop
    manager.menu();
}