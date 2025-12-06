#include <iostream>
#include <string>
#include "../include/DataStructures.h"
using namespace std; 

RecoveryStack stackData;

void RecoveryStack::push(const File& f) {

    cout << " Metadata for " << f.name << " pushed to stack.\n";
}

File RecoveryStack::pop() {
    if (isEmpty()) {
        cerr << "Error! Recovery Stack is empty.\n";
        // we have to return a File object, for now we return a dummy one
        return File("NULL", "NULL", "NULL"); 
    }
    
    // First, use vector's basic array access [] to *get* the last element
    File lastDeleted = stackData[stackData.size() - 1];
    
    // Then, actually pop the element

    return lastDeleted;
}

bool RecoveryStack::isEmpty() const {

}

void RecoveryStack::displayHistory() const {
    
    if (isEmpty()) {
        cout << "\n- Recovery History -\n";
        cout << "[No Deleted Files in History]\n";
        return;
    }

    cout << "\n - Recovery History -\n";
    
    // 2. Loop from the top of stack to bottom
    for (int i = stackData.size() - 1; i >= 0; --i) {
        
        //The serial number 
        int sn = stackData.size() - i; 
        
        cout << "    " <<sn << ". " << stackData[i].name << " Path: " << stackData[i].path << "\n";
    }
}


// I moved linked list functions from main.cpp file

void append(string filePath, node* &head) { 
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

void printList(node* head){
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
