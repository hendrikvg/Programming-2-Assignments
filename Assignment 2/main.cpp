#include <iostream>
#include <string>
#include <cstring>
#include <array>

using namespace std;

const int boardSize = 12;

// array<array<bool, boardSize>, boardSize> booleanBoard{
//         1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 
//         1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1,
//         0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1,
//         1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1,
//         1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0,
//         1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1,
//         1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
//         1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
//         1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
//         1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1,
//         1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
//         1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

// void showBoard()
// {
//     for (int row = 0; row < boardSize; row++)
//     {
//         for (int column = 0; column < boardSize; column++)
//         {
//             if (column == boardSize - 1)
//             {
//                 if (booleanBoard[row][column] == 1)
//                 {
//                     cout << " # " << endl;
//                 } else {
//                     cout << " . " << endl;
//                 }

//             } else
//             {
//                 if (board[row][column] == 1)
//                 {
//                     cout << " # ";
//                 } else {
//                     cout << " . ";
//                 }
                
//             }
            
//         }
//     }
// }

array<array<char, boardSize>, boardSize> characterBoard{
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

void showBoard()
{
    for (int row = 0; row < boardSize; row++)
    {
        for (int column = 0; column < boardSize; column++)
        {
            if (column == boardSize - 1)
            {
                cout << " " << characterBoard[row][column] << endl;
            } else {
                cout << " " << characterBoard[row][column] << " ";              
            }
            
        }
    }
}

int main()
{
    cout << "Hello world!" << endl;
    showBoard();    
    return 0;
}
