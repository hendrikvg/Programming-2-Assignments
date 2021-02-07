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

array<array<char, boardSize>, boardSize> maze{
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

void showBoard()
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

RowAndColumn linearSearch(char key)
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

bool traverseMaze(array<array<char, boardSize>, boardSize> walls, array<array<bool, boardSize>, boardSize> visited, RowAndColumn rowAndColumn) {
  showBoard();
  RowAndColumn location = linearSearch('x');
  if (location.row == mazeExit.row && location.column == mazeExit.column) {
    return true;
  }

  visited[location.row][location.column] = 1;
  
  if (walls(location + right) != wall && !visited(location + right)) {
    if (path(walls, visited, location+right) {
        return true;
    } else {
      showBoard();
    }
  }

  if (walls(location + left) != wall && !visited(location + left)) {
    if (path(walls, visited, location+left) {
        return true;
    } else {
    showBoard();
  }

  if (walls(location + up) != wall && !visited(location + up)) {
    if (path(walls, visited, location+up) {
        return true;
    } else {
    showBoard();
  }

  if (walls(location + down) != wall && !visited(location + down)) {
    if (path(walls, visited, location+down) {
        return true;
    } else {
    showBoard();
  }

  // no direction was succesful, we hit a dead end thus we return false (and print the board)
  return false;
}

int main()
{
    cout << "Hello world!" << endl;
    showBoard();
    RowAndColumn rowAndColumn = linearSearch('x');
    cout << "Row:" << mazeExit.row << endl;
    cout << "Column:" << mazeExit.column << endl;
    return 0;
}
