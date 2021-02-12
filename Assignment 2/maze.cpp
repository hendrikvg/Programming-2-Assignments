#include <iostream>
#include <string>
#include <cstring>
#include <array>

using namespace std;

// -----------------  INIT VARIABLES: ------------------

const int boardSize = 12;
int startIndexI;
int startIndexJ;
bool startFound;




array<array<char, boardSize>, boardSize> mazeArray  {  '#','#','#','#','#','#','#','#','#','#','#','#',
                                                       '#','.','.','.','#','.','.','.','.','.','.','#', 
                                                       '.','.','#','.','#','.','#','#','#','#','.','#',
                                                       '#','#','#','.','#','.','.','.','.','#','.','#',
                                                       '#','.','.','.','.','#','#','#','.','#','.','x',
                                                       '#','#','#','#','.','#','.','#','.','#','.','#',
                                                       '#','.','.','#','.','#','.','#','.','#','.','#',
                                                       '#','#','.','#','.','#','.','#','.','#','.','#',
                                                       '#','.','.','.','.','.','.','.','.','#','.','#',
                                                       '#','#','#','#','#','#','.','#','#','#','.','#',
                                                       '#','.','.','.','.','.','.','.','.','.','.','#',
                                                       '#','#','#','#','#','#','#','#','#','#','#','#'};

array<array<bool, boardSize>, boardSize> mazeBool; // to be filled with zeros




// ---------------- CREATE FUNCTIONS: -------------------


// For printMaze() function the following site was referenced: https://www'.'codesdope'.'com/cpp-stdarray/

void printMaze(array<array<char, boardSize>, boardSize> mazeName) {

    //cout << "Printing Maze:\n\n";

    for(int i=0; i<boardSize; i++) // i is the index of the rows
    {
        for(int j=0; j<boardSize; j++) // j is the index of the columns
        {
            cout << " " << mazeName[i][j] << " ";   // print all elements of the 2D array, adding spaces before and after for formatting/layout reasons.
        }
        
        cout << "\n" ;

        if (i==boardSize-1) {cout << endl;} // add a line break at the end of the maze for formatting reasons

    }

}

// the findStart() function will iterate through the array to find the char "x", which is the starting point.

void findStart(array<array<char, boardSize>, boardSize> mazeName, int &startIndexI, int &startIndexJ, bool &startFound) 
{     
    char startSign = 'x';
    for(int i=0; i<12; i++) // i is the index of the rows
        {
            for(int j=0; j<12; j++) // j is the index of the columns
            {
                if (mazeName[i][j] == startSign) { 
                    startIndexI = i;
                    startIndexJ = j;
                    startFound = true;
                    return;
                }   // print all elements of the 2D array, adding spaces before and after for formatting/layout reasons.
            }
    }
}


bool mazeExit(int current_indexI, int current_indexJ, int startIndexI, int startIndexJ) {
    if (((current_indexI == 0 || current_indexI == boardSize-1) || (current_indexJ == 0 || current_indexJ == boardSize-1)))
    {
        if (current_indexI == startIndexI && current_indexJ == startIndexJ)
        {
            return false;
        }
        else {return true;}
    }
    else {return false;}
}

// recursive function solveMaze finds the path through the maze using the method where you place your right hand against the wall.

bool solveMaze(array<array<char, boardSize>, boardSize> mazeName, array<array<bool, boardSize>, boardSize> mazeBool,  int startIndexI, int startIndexJ, int current_indexI, int current_indexJ) {



    mazeBool[current_indexI][current_indexJ] = 1;

    if (mazeExit(current_indexI, current_indexJ, startIndexI, startIndexJ) == true) {
        //stop maze solving, you have arrived at the end
        cout << "DONE! Final result:" << endl;
        printMaze(mazeName);
        
        return true;
    }
    
    if (mazeName[current_indexI-1][current_indexJ] != '#' && mazeBool[current_indexI-1][current_indexJ] == 0) { // checks wether the char above current == ".", which would equal going up.
        
        current_indexI = current_indexI-1;              // set index i to new index i-1
        mazeName[current_indexI][current_indexJ] = 'X'; // set previous position to X
        cout << "moved up\n";
        printMaze(mazeName);

        if (solveMaze(mazeName, mazeBool, startIndexI, startIndexJ, current_indexI, current_indexJ)) {
            return true;
        }

        mazeName[current_indexI][current_indexJ] = '.'; // set previous position to .
        current_indexI = current_indexI+1;              // set index i to new index i-1
        cout << "moved back down\n";
        printMaze(mazeName);
    }

    if (mazeName[current_indexI][current_indexJ-1] != '#' && mazeBool[current_indexI][current_indexJ-1] == 0) { // checks wether the char to the right == ".", if so move left. 
        
        current_indexJ = current_indexJ-1;
        mazeName[current_indexI][current_indexJ] = 'X';
        cout << "moved left\n";
        printMaze(mazeName);

        if (solveMaze(mazeName, mazeBool, startIndexI, startIndexJ, current_indexI, current_indexJ)) {
            return true;
        }

        current_indexJ = current_indexJ+1; // set index i to new index i-1
        mazeName[current_indexI][current_indexJ] = '.'; // set previous position to .              
        cout << "moved back down\n";        
        printMaze(mazeName);

    }

    if (mazeName[current_indexI+1][current_indexJ] != '#' && mazeBool[current_indexI+1][current_indexJ] == 0) { // checks wether the char below current == ".", which would equal going down.
        
        current_indexI = current_indexI+1;              // set index i to new index i-1
        mazeName[current_indexI][current_indexJ] = 'X'; // set previous position to X
        cout << "moved down\n";
        printMaze(mazeName);
        if (solveMaze(mazeName, mazeBool, startIndexI, startIndexJ, current_indexI, current_indexJ)) {
            return true;
        }

        mazeName[current_indexI][current_indexJ] = '.'; // set previous position to .
        current_indexI = current_indexI-1;              // set index i to new index i-1
        cout << "moved back up\n";
        printMaze(mazeName);
    }

    if (mazeName[current_indexI][current_indexJ+1] != '#' && mazeBool[current_indexI][current_indexJ+1] == 0) { // checks wether the char below current == ".", which would equal going down.
        
        current_indexJ = current_indexJ+1;              // set index i to new index i-1
        mazeName[current_indexI][current_indexJ] = 'X'; // set previous position to X
        cout << "moved down\n";
        printMaze(mazeName);

        if (solveMaze(mazeName, mazeBool, startIndexI, startIndexJ, current_indexI, current_indexJ)) {
            return true;
        }

        mazeName[current_indexI][current_indexJ] = '.'; // set previous position to .
        current_indexJ = current_indexJ-1;              // set index i to new index i-1
        cout << "moved back up\n";
        printMaze(mazeName);
    }

    return false;

}


  
// ------------------- MAIN: ----------------------

int main()
{
    cout << "\n" << "Running assignment 2\n\n"; // notify that the program is running
    fill(&mazeBool[0][0], &mazeBool[0][0] +sizeof(mazeBool), 0); //fills mazeBool with zeros

    
    printMaze(mazeArray); // call function to print the maze
    findStart(mazeArray, startIndexI, startIndexJ, startFound);
    


    if (startFound == 0) {
        cout << "ERROR: start of maze has not been found!";
        return 0;
    }  // check whether the start has been found
    else {
        cout << "the index i and j of the start of the maze is: " << startIndexI << " and " << startIndexJ << endl;
        
    } // print indices of starting point


    int current_indexI = startIndexI;
    int current_indexJ = startIndexJ;

    solveMaze(mazeArray, mazeBool, startIndexI, startIndexJ, current_indexI, current_indexJ);

    //system("pause");  // press any key to continue prompt
    return 0;
}
