#include<iostream>
#include<string>
#include "../include/dsa.h"
using namespace std;


struct node{
    string data;
    node* next;
};
node *head = NULL;

void append(string filePath,node* &head=head){
   node* ptr = new node;
   node* temp = head;
   ptr->data = filePath;
   ptr->next = NULL;    

   if (head == NULL) {
      head = ptr;
      return;
   }

   while (temp->next != NULL) {
      temp = temp->next;
   }
   temp->next = ptr;
}

void printList(node* head=head){
    if(!head) {
    cerr << "Error: Head is NULL\n";
    }else{
        node* ptr = head;
        while(ptr!=NULL){
            cout << ptr->data << endl;
            cout << "|\nv\n";
            ptr=ptr->next; 
        }
        cout << "END\n";
    }
}