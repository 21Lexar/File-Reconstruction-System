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
// Formula:- left height - right height
int AVLTree::getBalanceFactor(AVLNode* node) const {
    if (!node) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}


RecoveryStack stackData;

// Implementation using Linked List instead of Stack

bool RecoveryStack::isEmpty() const {
    return top == nullptr; // O(1) complexity
}

// PUSH: Add at head of list
void RecoveryStack::push(const File& f) {
    node* newNode = new node;
    newNode->file = f;
    newNode->next = top; // newNode points to current top
    top = newNode;       // newNode becomes new top
    cout << " Metadata for " << f.name << " pushed to recovery stack.\n";
}

// POP: Remove from head of list
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