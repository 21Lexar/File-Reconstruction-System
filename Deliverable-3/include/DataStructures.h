#ifndef DSA_H
#define DSA_H

#pragma once //So the file is only included *once*
#include <iostream>
#include <string>
#include <vector> 
using namespace std;


struct File {
    string name;
    int id;
    string path;
    string status; // "Active", "Deleted" or "Recovered" 
    
    // Default Constructor
    File(string n, int i, string p, string s = "Active") 
        : name(n), path(p), status(s) {}
};

struct node{
    File file; 
    node* next;
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
    //Stack and list objects will be here
    
public:
    //Core functions
    void printActiveList();
    bool logicalDelete(const string& filename);
    bool recoverLastFile();
    void menu();
};

void append(string,node* &);

void printList(node*);

#endif