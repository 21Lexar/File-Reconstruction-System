#ifndef DSA_H
#define DSA_H

#pragma once //So the file is only included *once*
#include <iostream>
#include <string>
#include <vector> 
using namespace std;

static int count = 0;

struct File {
    string name;
    int id;
    string path;
    string status; // "Active", "Deleted" or "Recovered" 
    
    // Default Constructor
    File(string n, int i = ++count,string p, string s = "Active",) 
        : name(n), path(p), status(s) {}
};

struct node{
    File file; 
    node* next;
};

class RecoveryStack {
    private:
        node* front;
        node* rear;
        
    public:
        void push(const File& f);
        File pop();
        bool isEmpty() const;
        void displayHistory() const;
        //All constant to tell the compiler thse functions are purely observational 
        //and won't change the queue entries
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