#ifndef DSA_H
#define DSA_H

#include<string>
using namespace std;

struct node{
    string data;
    node* next;
};

void append(string,node* &);

void printList(node*);

#endif