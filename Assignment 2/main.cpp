#include <iostream>
#include <string>
#include <cstring>
#include <array>

using namespace std;

const int boardSize = 12;

struct RowAndColumn
{
  int row;
  int column;
};

array<array<char, boardSize>, boardSize> mazeToSolve{
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

array<array<bool, boardSize>, boardSize> visited;

RowAndColumn mazeExit{2, 0};

void showBoard(array<array<char, boardSize>, boardSize> maze) // input geven
{
  for (int row = 0; row < sizeof(maze[0]) / sizeof(maze[0][0]); row++)
  {
    for (int column = 0; column < sizeof(maze) / sizeof(maze[0]); column++)
    {
      if (column == sizeof(maze) / sizeof(maze[0]) - 1)
      {
        cout << " " << maze[row][column] << endl;
      }
      else
      {
        cout << " " << maze[row][column] << " ";
      }
    }
  }
}

void showBoolBoard(array<array<bool, boardSize>, boardSize> boolBoard) // input geven
{
  for (int row = 0; row < sizeof(boolBoard[0]) / sizeof(boolBoard[0][0]); row++)
  {
    for (int column = 0; column < sizeof(boolBoard)/sizeof(boolBoard[0]); column++)
    {
      if (column == sizeof(boolBoard)/sizeof(boolBoard[0]) - 1)
      {
        cout << " " << boolBoard[row][column] << endl;
      }
      else
      {
        cout << " " << boolBoard[row][column] << " ";
      }
    }
  }
}

RowAndColumn linearSearch(char key, array<array<char, boardSize>, boardSize> maze)
{
  for (int row = 0; row < sizeof(maze[0]) / sizeof(maze[0][0]); row++)
  {
    for (int column = 0; column < sizeof(maze) / sizeof(maze[0]); column++)
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

bool traverseMaze(array<array<char, boardSize>, boardSize> maze, array<array<bool, boardSize>, boardSize> visited, RowAndColumn mazeExit, RowAndColumn location)
{
  showBoard(maze);
  if (location.row == mazeExit.row && location.column == mazeExit.column)
  {
    return true;
  }

  visited[location.row][location.column] = 1;

  if (location.column + 1 < (sizeof(maze[0]) / sizeof(maze[0][0]))) // Right
  {
    if (maze[location.row][location.column + 1] != '#' && (visited[location.row][location.column + 1] == 0))
    {
      location.column++;
      maze[location.row][location.column] = 'x';
      cout << "went right" << endl;
      if (traverseMaze(maze, visited, mazeExit, location))
      {
        return true;
      }
      else
      {
        maze[location.row][location.column] = '.';
        location.column--;
        cout << "reversed left" << endl;
        showBoard(maze);
      }
    }
  }

  if (location.column - 1 < (sizeof(maze[0]) / sizeof(maze[0][0]))) // Left. No else if(...) as it would cause the script to stop looking at other directions if it could go right just once
  {
    if (maze[location.row][location.column - 1] != '#' && (visited[location.row][location.column - 1] == 0))
    {
      location.column--;
      maze[location.row][location.column] = 'x';
      cout << "went left" << endl;
      if (traverseMaze(maze, visited, mazeExit, location))
      {
        return true;
      }
      else
      {
        maze[location.row][location.column] = '.';
        location.column++;
        cout << "reversed right" << endl;
        showBoard(maze);
      }
    }
  }

    if (location.row + 1 < (sizeof(maze) / sizeof(maze[0]))) // Down
  {
    if (maze[location.row + 1][location.column] != '#' && (visited[location.row + 1][location.column] == 0))
    {
      location.row++;
      maze[location.row][location.column] = 'x';
      cout << "went down" << endl;
      if (traverseMaze(maze, visited, mazeExit, location))
      {
        return true;
      }
      else
      {
        maze[location.row][location.column] = '.';
        location.row--;
        cout << "reversed up" << endl;
        showBoard(maze);
      }
    }
  }

  if (location.row - 1 < (sizeof(maze) / sizeof(maze[0]))) // Up
  {
    if (maze[location.row - 1][location.column] != '#' && (visited[location.row - 1][location.column] == 0))
    {
      location.row--;
      maze[location.row][location.column] = 'x';
      cout << "went up" << endl;
      if (traverseMaze(maze, visited, mazeExit, location))
      {
        return true;
      }
      else
      {
        maze[location.row][location.column] = '.';
        location.row++;
        cout << "reversed down" << endl;
        showBoard(maze);
      }
    }
  }

  // no direction was succesful, we hit a dead end thus we return false
  return false;
}

bool traverseMaze(array<array<char, boardSize>, boardSize> maze, array<array<bool, boardSize>, boardSize> visited, RowAndColumn mazeExit)
{
  RowAndColumn location = linearSearch('x', maze);
  traverseMaze(maze, visited, mazeExit, location);
}

int main()
{
  cout << "Hello world!" << endl;
  traverseMaze(mazeToSolve, visited, mazeExit);
  return 0;
}
