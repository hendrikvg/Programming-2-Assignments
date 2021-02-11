#include <iostream>
#include <array>

using namespace std;

const int boardSize = 12;

// Define commonly used types
template <class anyType> // Used as a placeholder so the type for the matrix can be defined later.
using Matrix = std::array<std::array<anyType, boardSize>, boardSize>;

typedef Matrix<bool> BoolMatrix; // Here the type gets defined
typedef Matrix<char> CharacterMatrix;

struct RowAndColumn
{
  int row;
  int column;
};

CharacterMatrix mazeToSolve{
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

template <class anyType>
void showMatrix(Matrix<anyType> matrix);
template <class anyType>
RowAndColumn linearSearch2DArray(anyType key, Matrix<anyType> matrix);
RowAndColumn locateMazeExit(CharacterMatrix maze);
bool traverseMaze(CharacterMatrix maze, BoolMatrix& visited, RowAndColumn mazeExit, RowAndColumn location);
bool traverseMaze(CharacterMatrix maze);

int main()
{
  cout << "Hello world!" << endl;
  traverseMaze(mazeToSolve);
  RowAndColumn mazeExit = locateMazeExit(mazeToSolve);
  return 0;
}

template <class anyType>
void showMatrix(Matrix<anyType> matrix) // input geven
{
  for (int row = 0; row < boardSize; row++)
  {
    for (int column = 0; column < boardSize; column++)
    {
      if (column == boardSize - 1)
      {
        cout << " " << matrix[row][column] << endl;
      }
      else
      {
        cout << " " << matrix[row][column] << " ";
      }
    }
  }
}

template <class anyType>
RowAndColumn linearSearch2DArray(anyType key, Matrix<anyType> matrix)
{
  for (int row = 0; row < boardSize; row++)
  {
    for (int column = 0; column < boardSize; column++)
    {
      if (matrix[row][column] == key)
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

RowAndColumn locateMazeExit(CharacterMatrix maze)
{
  RowAndColumn rowAndColumn;
  for (int i = 0; i < 1; i++)
  {
    for (int column = 0; column < boardSize; column++)
    {
      if (maze[i * (boardSize)][column] == '.')
      {
        rowAndColumn.row = i * boardSize;
        rowAndColumn.column = column;
        return rowAndColumn;
      }
    }
    for (int row = 0; row < sizeof(maze[0]) / sizeof(maze[0][0]); row++)
    {
      if (maze[row][i * (boardSize)] == '.')
      {
        rowAndColumn.row = row;
        rowAndColumn.column = i * (boardSize);
        return rowAndColumn;
      }
    }
  }
}

bool traverseMaze(CharacterMatrix maze, BoolMatrix& visited, RowAndColumn mazeExit, RowAndColumn location)
{
  showMatrix(maze);
  if (location.row == mazeExit.row && location.column == mazeExit.column)
  {
    return true;
  }

  visited[location.row][location.column] = 1;

  if (location.column + 1 < boardSize) // Right
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
      maze[location.row][location.column] = '.';
      location.column--;
      cout << "reversed left" << endl;
      showMatrix(maze);
    }
  }

  if (location.column - 1 < boardSize) // Left. No else if(...) as it would cause the script to stop looking at other directions if it could go right just once
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
      maze[location.row][location.column] = '.';
      location.column++;
      cout << "reversed right" << endl;
      showMatrix(maze);
    }
  }

  if (location.row + 1 < (boardSize)) // Down
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
      maze[location.row][location.column] = '.';
      location.row--;
      cout << "reversed up" << endl;
      showMatrix(maze);
    }
  }

  if (location.row - 1 < (boardSize)) // Up
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
      maze[location.row][location.column] = '.';
      location.row++;
      cout << "reversed down" << endl;
      showMatrix(maze);
    }
  }

  // no direction was succesful, we hit a dead end thus we return false
  return false;
}

bool traverseMaze(CharacterMatrix maze)
{
  BoolMatrix visited;
  std::fill(&visited[0][0], &visited[0][0] + sizeof(visited), 0); // fills the array "visited" 0's
  RowAndColumn mazeExit = locateMazeExit(maze);
  RowAndColumn location = linearSearch2DArray('x', maze);
  traverseMaze(maze, visited, mazeExit, location);
}