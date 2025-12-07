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
    // Base case: create new node
    if (!node) {
        return new AVLNode(f);
    }

    // Insert based on file ID
    if (f.id < node->data.id) {
        node->left = insert(node->left, f);
    } else if (f.id > node->data.id) {
        node->right = insert(node->right, f);
    } else {
        // if Duplicate ID, do not insert
        return node;
    }

    // Update height of current node
    updateHeight(node);

    // Get balance factor
    int bf = getBalanceFactor(node);

    // Left-Left case
    if (bf > 1 && f.id < node->left->data.id) {
        return rotateRight(node);
    }

    // Right-Right case
    if (bf < -1 && f.id > node->right->data.id) {
        return rotateLeft(node);
    }

    // Left-Right case
    if (bf > 1 && f.id > node->left->data.id) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right-Left case
    if (bf < -1 && f.id < node->right->data.id) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

//public function
void AVLTree::insert(const File& f) {
    root = insert(root, f);
}

AVLNode* AVLTree::search(int id) {
    AVLNode* current = root;
    
    while (current != nullptr) {
        if (id == current->data.id) {
            return current;
        } else if (id < current->data.id) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    
    return nullptr; // ID not found
}


// ~ Stack Implementation ~
RecoveryStack stackData;
bool RecoveryStack::isEmpty() const {
    return top == nullptr; // O(1) complexity
}

// Inserts at head of list
void RecoveryStack::push(const File& f) {
    node* newNode = new node{f, top};
    // newNode already points to current top via aggregate init
    top = newNode;       // newNode becomes new top
    cout << " Metadata for " << f.name << " pushed to recovery stack.\n";
}

// Removes from head of list
File RecoveryStack::pop() {
    if (isEmpty()) {
        cerr << "Error! Recovery Stack is empty.\n";
        // Returns dummy object (this must include the ID)
        return File("NULL", 0, "NULL", "NULL"); 
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
    int id = 1;
    cout << "Scanning directory: " << path << "\n";
    
    try {
        for (const auto& entry : fs::directory_iterator(path)) {
            if (entry.is_regular_file()) {
                string filename = entry.path().filename().string();
                string fullPath = entry.path().string();
                File f(filename, id, fullPath, "Active");
                activeFiles.insert(f);
                id++;
            }
        }
        cout << "Files scanned successfully!\n";
    } catch (const exception& e) {
        cerr << "Error scanning directory: " << e.what() << "\n";
    }
}

void FileManager::printActiveList() {
    AVLNode* root = activeFiles.getRoot();
    if (!root) {
        cout << "No active files found.\n";
        return;
    }

    cout << "\n~ Active Files ~\n";
    inOrderTraversal(root);
}

bool FileManager::logicalDelete(const int& id) {
    AVLNode* node = activeFiles.search(id);
    if (!node) {
        return false;
    }

    node->data.status = "Deleted";
    deleteHistory.push(node->data);
    return true;
}

bool FileManager::recoverLastFile() {
    if (deleteHistory.isEmpty()) {
        return false;
    }

    File recovered = deleteHistory.pop();
    recovered.status = "Recovered";

    // If the file still exists in the tree, update its status; otherwise insert it back
    AVLNode* node = activeFiles.search(recovered.id);
    if (node) {
        node->data.status = "Recovered";
    } else {
        activeFiles.insert(recovered);
    }

    return true;
}

void FileManager::clear(){
	cout << "\033[2J\033[1;1H"; //ANSI Sequence to clear screen
}

void FileManager::menu(){
	cout << "File Reconstruction System\n";
	cout << "1. Delete\n";
	cout << "2. Recover\n";
	cout << "3. List\n";
	cout << "4. Quit\n";
}

void FileManager::getUserChoice(){
	string input;
	while (true) {
		cout << "Enter your choice: "; 
		getline(cin, input);
		int choice = stoi(input);
		switch(choice){
			case 1: {
                clear();
                printActiveList();
				int f_id;
				cout << "Enter file ID to delete: ";
				string id_input;
				getline(cin, id_input);
				f_id = stoi(id_input);
				if (logicalDelete(f_id)) {
					cout << "File deleted successfully!\n";
				} else {
					cout << "File not found or deletion failed.\n";
				}
				menu();
				break;
			}
			case 2: {
                clear();
                printActiveList();
				if (recoverLastFile()) {
					cout << "File recovered successfully!\n";
				} else {
					cout << "No files to recover.\n";
				}
				menu();
				break;
			}
			case 3: {
                clear();
				printActiveList();
				menu();
				break;
			}
			case 4: {
				cout << "\nExiting File Reconstruction System.\n";
				exit(0);
				break;
			}
			default: {
				clear();
				menu();
			}
		}
	}
}
