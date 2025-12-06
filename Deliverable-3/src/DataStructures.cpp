#include <iostream>
#include <string>
#include "../include/DataStructures.h"
using namespace std; 


// ~ AVL Tree Implementation ~

// - Balancing functions -
// 1. Gets the height of a node
int AVLTree::getHeight(AVLNode* node) const {
    if (!node){
        return 0;
    } 
    return node->height;
}

// 2. Recalculates the new height
void AVLTree::updateHeight(AVLNode* node) {
    // height is 1 + the max height of its two children
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
}

// 3. Calculates balance
// Formula: left height - right height
int AVLTree::getBalanceFactor(AVLNode* node) const {
    if (!node) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

// - Rotation functions -
//Rotations needed when BF <-1 OR >1

//Left rotation for RR 
/* 8
    \
     9
      \
       10
*/
AVLNode* AVLTree::rotateLeft(AVLNode* x) {
    AVLNode* y = x->right; //y is right child of root x so 9
    AVLNode* st = y->right; //st is left subtree of y so 10

    // Anti clockwise rotation
    y->left = x; // 8 is left child of 9
    x->right = st;

    // Update heights (must be done in this order)
    updateHeight(x);
    updateHeight(y);

    return y; // new root
}


// LL or LR
AVLNode* AVLTree::rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    //Clock wise rotation
    x->right = y;
    y->left = T2;

    
    updateHeight(y);
    updateHeight(x);

    return x; //new root
}

//recursive helper function
AVLNode* AVLTree::insert(AVLNode* node, const File& f) {
    //Replace
}

//public function
void AVLTree::insert(const File& f) {
    // Replace
}

AVLNode* AVLTree::search(int id) {
    //Replace
}


// ~ Stack Implementation ~
RecoveryStack stackData;
bool RecoveryStack::isEmpty() const {
    return top == nullptr; // O(1) complexity
}

// Inserts at head of list
void RecoveryStack::push(const File& f) {
    node* newNode = new node;
    newNode->file = f;
    newNode->next = top; // newNode points to current top
    top = newNode;       // newNode becomes new top
    cout << " Metadata for " << f.name << " pushed to recovery stack.\n";
}

// Removes from head of list
File RecoveryStack::pop() {
    if (isEmpty()) {
        cerr << "Error! Recovery Stack is empty.\n";
        // Returns dummy object (this must include the ID)
        return File(0, "NULL", "NULL", "NULL"); 
    }

    node* oldTop = top;
    File lastDeleted = oldTop->file;

    top = top->next; // point top down to the next node 
    delete oldTop;   // free memory of the popped node

    return lastDeleted;
}


void RecoveryStack::displayHistory() const {
    if (isEmpty()) {
        cout << "\n--- Recovery History ---\n";
        cout << "[No Deleted Files in History Yet]\n";
        return;
    }

    cout << "\n ~ Recovery History ~\n";

    node* current = top;
    int sn = 1;

    // looping from top of stack to bottom
    while(current != nullptr) {

        cout << "    " << sn << ". " << current->file.name << " ID: " << current->file.id << " Path: " << current->file.path << "\n";
        current = current->next; 
        sn++;
    }
}

// ~ File Manager Implementation ~
void FileManager::inOrderTraversal(AVLNode* node) const {
    if (node) {
        inOrderTraversal(node->left);
        cout << "    ID: " << node->data.id << ", Name: " << node->data.name << "\n";
        inOrderTraversal(node->right);
    }
}

void FileManager::scanDirectory(const std::string& path) {
    //Use AVL tree for scan
}

void FileManager::printActiveList() {
    //Call getRoot 
}

bool FileManager::logicalDelete(const string& filename) {
    //AVL Search and Stack push
}

bool FileManager::recoverLastFile() {
    //Use stack pop and AVL update
}

void FileManager::menu() {
    //Menu
}