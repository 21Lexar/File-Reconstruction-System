#pragma once //So the file is only included *once*
#include <iostream>
#include <string>
#include <vector> 
using namespace std;

struct File {
    string name;
    string path;
    string status; // "Active", "Deleted" or "Recovered" 
    
    // Default Constructor
    File(string n, string p, string s = "Active") 
        : name(n), path(p), status(s) {}
};


struct node {
    // Later data will hold a 'File' structure instead of a simple string
    string data; 
    node* next;
};

class RecoveryStack {
private:
    vector<File> stackData; 
    //Using a vector since its best for LIFO models
    
public:
    void push(const File& f);
    File pop();
    bool isEmpty() const;
    void displayHistory() const;
    //All constant to tell the compiler thse functions are purely observational 
    //and won't change the Stack entries
};


class FileManager {
private:
    //Stack and list objects will be here
    
public:
    //Core functions
    void printActiveList();
    bool logicalDelete(const string& filename);
    bool recoverLastFile();
};