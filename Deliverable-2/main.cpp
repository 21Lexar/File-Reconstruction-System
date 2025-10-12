#include <string>
#include <iostream>
#include <filesystem>
#include "include/dsa.h"
namespace fs = std::filesystem;
using namespace std;

const string PATH = fs::current_path() / "Temp";
node *head = NULL;

int main()
{   
    // Iterator inside directory
    for (const auto & entry : fs::directory_iterator(PATH)){
        append(entry.path(),head);
    }
    printList(head);
}
