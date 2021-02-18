#include <iostream>
#include <ctime>
#include <vector>
#include <numeric> // for iota
#include "Tree.h"
#include "TreeNode.h"

using namespace std;

int binarySearch(vector<int> inputVector, int min, int max, int key);
void fillTreeRandomly(Tree<int>& inputTree, int size, int min, int max);

int main()
{
    srand(time(NULL)); // generate seed with time, in order to generate random numbers
    Tree<int> tree1;
    fillTreeRandomly(tree1, 10, 0, 100);
    cout << "\n\n Tree:";
    tree1.inOrderTraversal();
    return 0;
}

int binarySearch(vector<int> inputVector, int min, int max, int key)
{
    if (max >= min)
    {
        int middle = (min + max) / 2;
        if (inputVector[middle] == key)                                // Checking if the element is present at middle location
        {
            return middle + 1;
        }
        else if (inputVector[middle] < key)                            // Checking if the search element is present in greater half
        {
            return binarySearch(inputVector, middle + 1, max, key);
        }
        else                                                           // Checking if the search element is present in lower half
        {
            return binarySearch(inputVector, min, middle - 1, key);
        }
    }
    return -1;
}

void fillTreeRandomly(Tree<int>& inputTree, int size, int min, int max)
{
    if (max - min < size)
    {
        cout << "The range of numbers is too small for this size.";
        return;
    }
    vector<int> possibleIntegers(max - min);
    iota(begin(possibleIntegers), end(possibleIntegers), min);
    int counter {0};
    while(counter < size)
    {
        int randomInteger = rand() % max + min;
        int possibleIndex = binarySearch(possibleIntegers, min, max, randomInteger);
        if (possibleIndex != -1)
        {
            inputTree.insertNode(randomInteger);
            possibleIntegers.erase(possibleIntegers.begin() + possibleIndex - 1); // -1 needed to remove the actual integer instead of the one above that.
            counter++;
        }
    }  
}