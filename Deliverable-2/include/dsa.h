#ifndef DSA_H
#define DSA_H

#include<string>
using namespace std;

struct node{
    string data;
    node* next;
};

void append(string filePath,node* &head);

void printList(node* head);

#endif