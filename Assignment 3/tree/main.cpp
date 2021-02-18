#include <iostream>
#include "Tree.h"
#include "functions.cpp"

using namespace std;

int main()
{
    Tree<int> tree1; // Make tree called "tree1".
    int size{20};    // Define size of the tree.
    int min{-40};    // Define minimum value of the tree.
    int max{40};     // Define maximum value of the tree.

    fillTreeRandomly(tree1, size, min, max); // Fill tree with random integers.
    cout << "Tree1: ";
    tree1.inOrderTraversal(); // Show the data in "tree1" from low to high.
    cout << "\n";
    searchTree(tree1, min, max); // Use user input to search for specific value in "tree1".
    tree1.outputTree();          // Output the tree in a horizontal tree-like structure.
    
    return 0;
}