#include "List.h"

template <typename anyType>
// fillList() fills a list with an input.
// @param input The input that should be added to the list.
// @param list The list that the input should be added to.
void fillList(anyType input, List<char>& list)
{
    int nThCharacter{0}; // Initialise integer with 0.
    while (input[nThCharacter]) // While nThCharacter input character exists...
    {
        list.insertAtBack(input[nThCharacter]); // Insert the nTh input character at the back of the list.
        nThCharacter++; // Next character.
    }
}