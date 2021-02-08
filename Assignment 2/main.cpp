#include <iostream>
#include <string>
#include <cstring>
#include <array>

using namespace std;

const int boardSize = 12;

struct RowAndColumn {
    int row;
    int column;
};

array<array<char, boardSize>, boardSize> mazeToSolve{
        '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#' ,'#', 
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
        
array<array<bool, boardSize>, boardSize> visited;

RowAndColumn mazeExit{2,0};

void showBoard(array<array<char, boardSize>, boardSize> maze) // input geven
{
    for (int row = 0; row < boardSize; row++)
    {
        for (int column = 0; column < boardSize; column++)
        {
            if (column == boardSize - 1)
            {
                cout << " " << maze[row][column] << endl;
            } else {
                cout << " " << maze[row][column] << " ";              
            }
            
        }
    }
}

void showBoolBoard(array<array<bool, boardSize>, boardSize> boolBoard) // input geven
{
    for (int row = 0; row < boardSize; row++)
    {
        for (int column = 0; column < boardSize; column++)
        {
            if (column == boardSize - 1)
            {
                cout << " " << boolBoard[row][column] << endl;
            } else {
                cout << " " << boolBoard[row][column] << " ";              
            }
            
        }
    }
}

RowAndColumn linearSearch(char key, array<array<char, boardSize>, boardSize> maze)
{
    for (int row = 0; row < boardSize; row++)
    {
        for (int column = 0; column < boardSize; column++)
        {
            if (maze[row][column] == key)
            {
            RowAndColumn rowAndColumn;
            rowAndColumn.row = row;
            rowAndColumn.column = column; 
            return rowAndColumn;
            }
        }
    }
    cout << "Key: \"" << key << "\" not found." << endl;
} 

bool traverseMaze(array<array<char, boardSize>, boardSize> maze, array<array<bool, boardSize>, boardSize> visited, RowAndColumn mazeExit) {
  showBoard(maze);
  RowAndColumn location = linearSearch('x', maze);
  if (location.row == mazeExit.row && location.column == mazeExit.column) {
    return true;
  }

  visited[location.row][location.column] = 1;
  // showBoolBoard(visited);
  
  if (location.column + 1 < (sizeof(maze[0])/sizeof(maze[0][0]))) // Right
  {
    if (maze[location.row][location.column + 1] != '#' && (visited[location.row][location.column + 1] == 0)) {
      maze[location.row][location.column + 1] = 'x';
      maze[location.row][location.column] = '.';
      cout << "went right" << endl;
      if (traverseMaze(maze, visited, mazeExit))
      {
          return true;
      } else {
        maze[location.row][location.column] = 'x';
        maze[location.row][location.column + 1] = '.';
        showBoard(maze);
      }
    }
  } 
  
  if (location.column - 1 < (sizeof(maze[0])/sizeof(maze[0][0]))) // Left. No else if(...) as it would cause the script to stop looking at other directions if it could go right just once
  {
    if (maze[location.row][location.column - 1] != '#' && (visited[location.row][location.column - 1] == 0)) {
      maze[location.row][location.column - 1] = 'x';
      maze[location.row][location.column] = '.';
      cout << "went left" << endl;
      if (traverseMaze(maze, visited, mazeExit))
      {
          return true;
      } else {
      maze[location.row][location.column] = 'x';
      maze[location.row][location.column - 1] = '.';
        showBoard(maze);
      }
    }
  } 
  
  if (location.row - 1 < (sizeof(maze)/sizeof(maze[0]))) // Up
  {
    if (maze[location.row - 1][location.column] != '#' && (visited[location.row - 1][location.column] == 0)) {
      maze[location.row - 1][location.column] = 'x';
      maze[location.row][location.column] = '.';
      cout << "went up" << endl;
      if (traverseMaze(maze, visited, mazeExit))
      {
          return true;
      } else {
      maze[location.row][location.column] = 'x';
      maze[location.row - 1][location.column] = '.';
        showBoard(maze);
      }
    }
  } 
  
  if (location.row + 1 < (sizeof(maze)/sizeof(maze[0]))) // Down
  {
    if (maze[location.row + 1][location.column] != '#' && (visited[location.row + 1][location.column] == 0)) {
      maze[location.row + 1][location.column] = 'x';
      maze[location.row][location.column] = '.';
      cout << "went down" << endl;
      if (traverseMaze(maze, visited, mazeExit))
      {
          return true;
      } else {
        maze[location.row][location.column] = 'x';
        maze[location.row + 1][location.column] = '.';
        showBoard(maze);
      }
    }
  }

  // no direction was succesful, we hit a dead end thus we return false (and print the board)
  return false;
}

int main()
{
    cout << "Hello world!" << endl;
    traverseMaze(mazeToSolve, visited, mazeExit);
    // showBoard(maze);
    return 0;
}
