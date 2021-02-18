#include <ctime>   // for random seed (srand()), and thus fillTreeRandomly()
#include <vector>  // for fillTreeRandomly() and binarySearch()
#include <numeric> // for iota()
#include <string>  // for getLine()
#include <sstream> // for getLine()
#include "Tree.h"

using namespace std;

/*
getInteger() makes sure the input string is an integer the minimum and the maximum input. 
If it isn't then the user will be asked to correct their input. 
If it is then the input string will be converted to an integer and returned.

@param minimum The minimum value of the integer that will be recieved
@param maximum The maximum value of the integer that will be recieved
@returns An integer from user input between the minimum and maximum
*/
int getInteger(int minimum, int maximum) // From assignment 1
{
    int outputInteger;
    string inputString;

    while (1)
    {
        getline(cin, inputString);                                                                                             // gets user input as a string
        stringstream convert(inputString);                                                                                     // makes string into a stream
        if (convert >> outputInteger && !(convert >> inputString) && (outputInteger >= minimum) && (outputInteger <= maximum)) // checking for valid conversion and any rejects if any unconverted input left
        {
            return outputInteger;
        }
        else
        {
            cin.clear(); // clear the input
            cout << "ERROR!\nwrong input\nPlease enter an INTEGER between " << minimum << " and " << maximum << endl;
        }
    }
}

// searchTree() searches a (binary search) tree for a key integer value from user input.
// @param inputTree The tree that needs to be searched.
// @param min The minimim value that the user can enter.
// @param max The maximum value that the user can enter.
void searchTree(Tree<int> &inputTree, int min, int max)
{
    if (inputTree.search(getInteger(min, max)) != nullptr) // Get user input and check whether the key value was found.
    {
        cout << "Key has been found.\n"; // The member function already states if the key could not be found, so it only states if it has been found.
    }
}

// binarySearch() uses the binary search algorithm to search for a given key integer in an ordered integer vector with a known min and max.
// @param inputVector The ORDERED vector that needs to be searced for the key value.
// @param min The minimum index that should be searched from.
// @param max The maximum index until where the vector should be searched.
// @param key The key value that is being searched for.
// @returns integer specifying the index of the key in the vector.
int binarySearch(vector<int> inputVector, int min, int max, int key)
{
    if (max >= min)
    {
        int middle = (min + max) / 2;
        if (inputVector[middle] == key) // Checking if the element is present at middle location.
        {
            return middle + 1;
        }
        else if (inputVector[middle] < key) // Checking if the search element is present in greater half.
        {
            return binarySearch(inputVector, middle + 1, max, key); // If so, search in greater half.
        }
        else // Checking if the search element is present in lower half.
        {
            return binarySearch(inputVector, min, middle - 1, key); // If so, search is lower half.
        }
    }
    return -1;
}

// Overloaded binarySearch() such that it can be first called with just the vector and key.
// @param inputVector The ORDERED vector that needs to be searced for the key value.
// @param key The key value that is being searched for.
// @returns integer specifying the index of the key in the vector.
int binarySearch(vector<int> inputVector, int key)
{
    return binarySearch(inputVector, 0, inputVector.size(), key);
}

// filltreeRandomly() randomly fills a (binary search) tree to a certain size with values between min and max.
// @param inputTree The tree that is about to be filled.
// @param size The amount of integers that should be added to the tree.
// @param min The minimum value that can be added to the tree.
// @param max The maximum value that can be added to the tree.
void fillTreeRandomly(Tree<int> &inputTree, int size, int min, int max)
{
    srand(time(NULL));     // generate seed with time, in order to generate random numbers.
    if (max - min <= size) // To avoid duplicates, check whether there are less integers than the amount of values that should be added.
    {
        cout << "The range of numbers is too small for this size.";
        return;
    }
    vector<int> possibleIntegers(max - min);                   // Construct vector.
    iota(begin(possibleIntegers), end(possibleIntegers), min); // Fill with all possible integers.
    int counter{0};
    while (counter < size)
    {
        int randomInteger = rand() % (max - min) + min;                    // Generate random integer.
        int possibleIndex = binarySearch(possibleIntegers, randomInteger); // See if the random integer is a possible integer.
        if (possibleIndex != -1)                                           // If it is...
        {
            inputTree.insertNode(randomInteger);                                  // Insert the random integer in the tree.
            possibleIntegers.erase(possibleIntegers.begin() + possibleIndex - 1); // Erase the random integer from the possible integer list. -1 needed to remove the actual integer instead of the one above that.
            counter++;                                                            // Note that the size has increased.
        }
    }
}