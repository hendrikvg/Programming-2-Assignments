/*
==============================================================
 Filename    :  main.cpp
 Authors     :  Hendrik van Gils    (s1920677)      h.vangils@student.utwente.nl
                Deniz Ugurlu        (s1797735)      d.a.ugurlu@student.utwente.nl
 Version     :  1.0
 License     :  None.
 Description :  The aims op this file are to solve a supplied maze and display the solution.
==============================================================
*/

#include <iostream>
#include <array>

using namespace std;

const int boardSize = 12; // Global variable board size gets initiated

template <class anyType>                                    // Used as a placeholder so the type for the matrix can be defined later.
using Matrix = array<array<anyType, boardSize>, boardSize>; // Defining "Matrix" as a 2D array with the dimensions of boardSize×boardSize

typedef Matrix<bool> BoolMatrix;      // Here the type gets defined as character
typedef Matrix<char> CharacterMatrix; // "" as boolean

struct RowAndColumn // Define struct "RowAndColumn" so functions can return both row and column of a matrix
{
  int row;
  int column;
};

// Function prototypes:
template <class anyType>                                                                                    // Used as a placeholder so the type for the matrix can be defined later.
void showMatrix(Matrix<anyType> matrix);                                                                    // showMatrix() prints an overview of a 2D matrix with spaces between the columns.
template <class anyType>                                                                                    // Used as a placeholder so the type for the key and matrix can be defined later.
RowAndColumn linearSearch2DArray(anyType key, Matrix<anyType> matrix);                                      // linearSearch2DArray() seaches a 2D array linearly for a given key value and returns the row and column of where that key value was found.
RowAndColumn locateMazeExit(CharacterMatrix maze);                                                          // locateMazeExit() locates the exit of the maze and returns the row and column of where the exit was found.
bool traverseMaze(CharacterMatrix maze, BoolMatrix &visited, RowAndColumn mazeExit, RowAndColumn location); // traverseMaze() traverses the maze by depth first search, showing every move and the path that was taken.
bool traverseMaze(CharacterMatrix maze);                                                                    // overload traverseMaze() such that it can be initiated with less arguments: just the maze.

// Main:
int main()
{
  cout << "Hello world!"
       << "\n";
  CharacterMatrix mazeToSolve{// Initiate the maze that needs to be solved
                              '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
                              '#', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '#',
                              '.', '.', '#', '.', '#', '.', '#', '#', '#', '#', '.', '#',
                              '#', '#', '#', '.', '#', '.', '.', '.', '.', '#', '.', '#',
                              '#', '.', '.', '.', '.', '#', '#', '#', '.', '#', '.', 'x',
                              '#', '#', '#', '#', '.', '#', '.', '#', '.', '#', '.', '#',
                              '#', '.', '.', '#', '.', '#', '.', '#', '.', '#', '.', '#',
                              '#', '#', '.', '#', '.', '#', '.', '#', '.', '#', '.', '#',
                              '#', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.', '#',
                              '#', '#', '#', '#', '#', '#', '.', '#', '#', '#', '.', '#',
                              '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#',
                              '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'};

  traverseMaze(mazeToSolve); // solve the maze that needs to be solved
  return 0;                  // quit program
}

// @param matrix the 2D matrix that needs to be printed
template <class anyType>                // Used as a placeholder so the type for the matrix can be defined later.
void showMatrix(Matrix<anyType> matrix) // input geven
{
  for (int row = 0; row < boardSize; row++) // go through all rows, one by one
  {
    for (int column = 0; column < boardSize; column++) // go through all columns, one by one
    {
      if (column == boardSize - 1) // start new line after last column
      {
        cout << " " << matrix[row][column] << "\n"; // start new line after last column
      }
      else
      {
        cout << " " << matrix[row][column] << " "; // spaces between columns
      }
    }
  }
}

// @param key the key value that has to be found
// @param matrix the 2D matrix that is being searched for the key value
// @returns RowAndColumn struct with the row and column where the key value was found
template <class anyType> // Used as a placeholder so the type for the key and matrix can be defined later.
RowAndColumn linearSearch2DArray(anyType key, Matrix<anyType> matrix)
{
  for (int row = 0; row < boardSize; row++) // go through all rows, one by one
  {
    for (int column = 0; column < boardSize; column++) // go through all columns, one by one
    {
      if (matrix[row][column] == key) // if the contents of matrix(row,column) match the key value
      {
        RowAndColumn rowAndColumn;    // define rowAndColumn as a RowAndColumn struct
        rowAndColumn.row = row;       // enter row
        rowAndColumn.column = column; // enter column
        return rowAndColumn;          // return the row and column
      }
    }
  }
  cout << "Key: \"" << key << "\" not found."
       << "\n"; // if key value can not be found return error message
}

// @param maze the maze that we want to solve, and thus find the exit of
// @returns RowAndColumn struct whith the row and column of the maze exit
RowAndColumn locateMazeExit(CharacterMatrix maze)
{
  for (int i = 0; i < 1; i++) // go through both first and last value of row and column
  {
    RowAndColumn rowAndColumn;
    for (int column = 0; column < boardSize; column++) // go through all columns when looking at first and last row
    {
      if (maze[i * boardSize][column] == '.') // check whether maze(row,column) is a path
      {
        rowAndColumn.row = i * boardSize;
        rowAndColumn.column = column;
        return rowAndColumn; // store and return exit location
      }
    }
    for (int row = 0; row < boardSize; row++) // go through all rows when looking at first and last column
    {
      if (maze[row][i * boardSize] == '.') // check whether maze(row,column) is a path
      {
        rowAndColumn.row = row;
        rowAndColumn.column = i * boardSize;
        return rowAndColumn; // store and return exit location
      }
    }
  }
  cout << "No maze exit was found\n";
}

// @param maze 2D character array of the maze that needs to be solved
// @param visited 2D boolean array of where the x has been while trying to solve the maze
// @param mazeExit the row and column of the exit of the maze
// @param location the row and column where the character currently is
// @returns boolean of whether the exit of the maze was found and a visual representation of the solution
bool traverseMaze(CharacterMatrix maze, BoolMatrix &visited, RowAndColumn mazeExit, RowAndColumn location) // visited is passed by reference because it does not have to be copied every time traverseMaze() is called
{
  showMatrix(maze);                                                       // display the current state of solving the maze
  if (location.row == mazeExit.row && location.column == mazeExit.column) // if the character is currently on the exit
  {
    return true; // return true
  }

  visited[location.row][location.column] = 1; // note that the character has been on this spot in the visited matrix

  if (location.column + 1 < boardSize) // Right
  {
    if (maze[location.row][location.column + 1] != '#' && (visited[location.row][location.column + 1] == 0)) // if there is no wall on the right and the character has not been there yet
    {
      location.column++;                         // move to the right
      maze[location.row][location.column] = 'x'; // visually move to the right
      cout << "went right"
           << "\n";                                        // state that the character moved to the right
      if (traverseMaze(maze, visited, mazeExit, location)) // repeat this function, if it returns true that means the exit of the maze was found by the character
      {
        return true; // and thus return true
      }
      maze[location.row][location.column] = '.'; // if the exit of the maze was not found then revert the step that was taken
      location.column--;                         // ""
      cout << "reversed left"
           << "\n";     // state that the character moved back
      showMatrix(maze); // show the character going back
    }
  }

  if (location.column - 1 < boardSize) // Left. No else if(...) as it would cause the script to stop looking at other directions if it could go right just once
  {
    if (maze[location.row][location.column - 1] != '#' && (visited[location.row][location.column - 1] == 0)) // if there is no wall on the left and the character has not been there yet
    {
      location.column--;                         // move to the left
      maze[location.row][location.column] = 'x'; // visually move to the left
      cout << "went left"
           << "\n";                                        // state that the character moved to the left
      if (traverseMaze(maze, visited, mazeExit, location)) // repeat this function, if it returns true that means the exit of the maze was found by the character
      {
        return true; // and thus return true
      }
      maze[location.row][location.column] = '.'; // if the exit of the maze was not found then revert the step that was taken
      location.column++;                         // ""
      cout << "reversed right"
           << "\n";     // state that the character moved back
      showMatrix(maze); // show the character going back
    }
  }

  if (location.row + 1 < (boardSize)) // Down
  {
    if (maze[location.row + 1][location.column] != '#' && (visited[location.row + 1][location.column] == 0)) // if there is no wall below the character and the character has not been there yet
    {
      location.row++;                            // move down
      maze[location.row][location.column] = 'x'; // visually move down
      cout << "went down"
           << "\n";                                        // state that the character moved down
      if (traverseMaze(maze, visited, mazeExit, location)) // repeat this function, if it returns true that means the exit of the maze was found by the character
      {
        return true; // and thus return true
      }
      maze[location.row][location.column] = '.'; // if the exit of the maze was not found then revert the step that was taken
      location.row--;                            // ""
      cout << "reversed up"
           << "\n";     // state that the character moved back
      showMatrix(maze); // show the character going back
    }
  }

  if (location.row - 1 < (boardSize)) // Up
  {
    if (maze[location.row - 1][location.column] != '#' && (visited[location.row - 1][location.column] == 0)) // if there is no wall above the character and the character has not been there yet
    {
      location.row--;                            // move up
      maze[location.row][location.column] = 'x'; // visually move up
      cout << "went up"
           << "\n";                                        // state that the character moved up
      if (traverseMaze(maze, visited, mazeExit, location)) // repeat this function, if it returns true that means the exit of the maze was found by the character
      {
        return true; // and thus return true
      }
      maze[location.row][location.column] = '.'; // if the exit of the maze was not found then revert the step that was taken
      location.row++;                            // ""
      cout << "reversed down"
           << "\n";     // state that the character moved back
      showMatrix(maze); // show the character going back
    }
  }

  return false; // no direction was succesful, we hit a dead end thus we return false
}

// @param maze 2D character array of the maze that needs to be solved
// @returns boolean of whether the exit of the maze was found, a visual representation of the solution and an error message if no solution was found.
bool traverseMaze(CharacterMatrix maze) // overloaded function, allows it to be called with less arguments
{
  BoolMatrix visited;                                        // define visited matrix
  fill(&visited[0][0], &visited[0][0] + sizeof(visited), 0); // -courtesy of a friend from Delft: fills the array "visited" 0's, this initiation is needed for it to be passed by reference. This is the clean solution, before we just manually filled it with 0's.
  RowAndColumn mazeExit = locateMazeExit(maze);              // find mazeExit
  RowAndColumn location = linearSearch2DArray('x', maze);    // find start location
  if (traverseMaze(maze, visited, mazeExit, location))       // call traverseMaze function with proper arguments
  {
    return true;
  }
  else
  {
    cout << "No path from start to exit was found for this maze.\n";
    return false;
  }
}