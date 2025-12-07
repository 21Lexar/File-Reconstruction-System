#ifndef DSA_H
#define DSA_H

#pragma once //So the file is only included *once*
#include <iostream>
#include <string>
#include <vector> 
#include <filesystem>
namespace fs = std::filesystem;
using namespace std;


struct File {
    string name;
    int id;
    string path;
    string status; // "Active", "Deleted" or "Recovered" 
    File(string n, int i, string p, string s = "Active") : name(n), id(i), path(p), status(s) {}
};

struct node{
    File file; 
    node* next;
};

// AVL Tree Node Structure 
struct AVLNode {
    File data; 
    AVLNode* left;
    AVLNode* right;
    int height; // Important for avl self balancing mechanism

    AVLNode(const File& f) 
        : data(f), left(nullptr), right(nullptr), height(1) {} //A leaf node with no children has height 1
};

// AVL Tree class defined
class AVLTree {
private:
    AVLNode* root; //Only one primary pointer

    //helping functions
    int getHeight(AVLNode* node) const;
    void updateHeight(AVLNode* node);
    int getBalanceFactor(AVLNode* node) const;

    // to self-balance
    AVLNode* rotateLeft(AVLNode* a);
    AVLNode* rotateRight(AVLNode* b);

    // Recursive insert function -> the most exhaustively used function
    AVLNode* insert(AVLNode* node, const File& f);

public:
    AVLTree() : root(nullptr) {} 

    void insert(const File& f);
    AVLNode* search(int id); // has O (log(n)) complexity
    AVLNode* getRoot() const { return root; } // for traversing
};

class RecoveryStack {
    private:
        node* top; // for simple stack implementation

    public:
        RecoveryStack() : top(nullptr) {} 
        void push(const File& f); // O(1) complexity
        File pop(); // O(1) complexity as well
        bool isEmpty() const;
        void displayHistory() const;
        //All constant to tell the compiler thse functions are purely observational 
        //and won't change the stack entries
};


class FileManager {
private:
    // 1. Added stack and tree objects
    AVLTree activeFiles;     
    RecoveryStack deleteHistory; 

    int nextFileID = 1; // 2. This is to generate unique IDs (will be used in File constructor)

    // 3. private function for display
    void inOrderTraversal(AVLNode* node) const;

public:
    // Added Core function prototypes 
    void scanDirectory(const std::string& path); 
    void printActiveList();
    bool logicalDelete(const int& id);
    bool recoverLastFile();
    void menu();
    void getUserChoice();
    void clear();
};

#endif

