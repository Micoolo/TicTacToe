#include <iostream>
#include <vector>
#include "TicTacToe.hpp"
#include <stdlib.h>
TicTacToe::TicTacToe(int size, int NumbersInRow) : board(size, std::vector<char>(size, ' '))
{
    this->size = size;
    this->NumbersInRow = NumbersInRow;
    this->maxDepth = (100/(size * size)) + 1;
}

void TicTacToe::run()
{
    bool exit = false;
    while (!exit) {
        int row, col;
        std::cout << "Player 1 turn: ";
        std::cin >> row >> col;
        if(isValidMove(row, col)) {
            board[row][col] = 'O';
        }  
        show();
        if (checkDraw() || checkWin('X') || checkWin('O')) {
            std::cout << "game ended" << std::endl;
            break;
        }


        std::cout << "Player 2 turn: ";
        std::cin >> row >> col;
        if(isValidMove(row, col)) {
            board[row][col] = 'X';
        } 
        show();
        if (checkDraw() || checkWin('X') || checkWin('O')) {
            std::cout << "game ended" << std::endl;
            exit = true;
        }
    }
}
const void TicTacToe::show() {
    system("CLS");
    for (int i = 0; i < size; i++) {
        std::cout << "-------------------------" << std::endl;
                                // a       a       a                                
        for (int j = 0; j < size; j++) {
            std::cout << "|" <<  "   " << board[i][j] << "   "; 
        }
        std::cout << "|" << std::endl;
    }
    std::cout << "-------------------------" << std::endl << std::endl;
}
// const void TicTacToe::show() {
//     for (int i = 0; i < size; i++) {
//         std::cout <<    "---------" << std::endl;
//                                 // a       a       a                                
//         for (int j = 0; j < size; j++) {
//             std::cout << "|" <<  "   " << board[i][j] << "   "; 
//         }
//         std::cout << "|" << std::endl;
//     }
//     std::cout << "-------------------------" << std::endl << std::endl;
// }
bool TicTacToe::isValidMove(int row, int col)
{
    return row >= 0 && row < size && col >= 0 && col < size && board[row][col] == ' ';
}


bool TicTacToe::checkWin(char sign)
{
    // check rows
    for (size_t i = 0; i < size; i++)
    {
        int count = 0;
        for (size_t j = 0; j < size; j++)
        {
            if (board[i][j] == sign) {
                count++;
                if (count == NumbersInRow)
                    return true;
            }
            else {
                count = 0;
            }
        }
    }

    // check columns
    for (size_t j = 0; j < size; j++)
    {
        int count = 0;
        for (size_t i = 0; i < size; i++)
        {
            if (board[i][j] == sign) {
                count++;
                if (count == NumbersInRow)
                    return true;
            }
            else {
                count = 0;
            }
        }
    }
    
    // check diagonal down to right
    for (size_t i = 0; i <= size - NumbersInRow; i++)
    {
        for (size_t j = 0; j <= size - NumbersInRow; j++) {
            int count = 0;
            for (size_t k = 0; k < NumbersInRow; k++)
            {
                if (board[i + k][j + k] == sign) {
                    count++;
                    if (count == NumbersInRow)
                        return true;
                }
                else {
                    count = 0;
                }
            }
        }
    }

    // check diagonal down to left
    for (size_t i = 0; i <= size - NumbersInRow; i++)
    {
        for (size_t j = NumbersInRow - 1; j < size; j++) {
            int count = 0;
            for (size_t k = 0; k < NumbersInRow; k++)
            {
                if (board[i + k][j - k] == sign) {
                    count++;
                    if (count == NumbersInRow)
                        return true;
                }
                else {
                    count = 0;
                }
            }
        }
    }

    return false;
}

bool TicTacToe::checkDraw()
{
    int count = 0;
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++) {
            if (board[i][j] == ' ')
                return false;
        }
    }

    return true;
}
