#include <iostream>
#include <ctime>
#include "Tree.h"
#include "TreeNode.h"

using namespace std;

int main()
{
    srand(time(NULL));  // generate seed with time, in order to generate random numbers
    // int v1 = rand() % 9;
    cout << rand() % 9 << "\n";
    return 0;
}
