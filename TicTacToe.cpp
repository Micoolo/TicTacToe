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
    while (true) {
        int row, col; 

        std::cout << "Player 2 turn: ";
        std::cin >> row >> col;
        if(isValidMove(row, col)) {
            board[row][col] = 'X';
        } 
        show();
        if (checkDraw()) {
            std::cout << "Game ended. Result: DRAW! " << std::endl;
            break;
        }
        if (checkWin('X')) {
            std::cout << "Game ended. Result: PLAYER 2 WON! " << std::endl;
            break;
        }
        
        AI(board, 'O', 'X');
        show();
        if (checkDraw()) {
            std::cout << "Game ended. Result: DRAW! " << std::endl;
            break;
        }
        if (checkWin('O')) {
            std::cout << "Game ended. Result: PLAYER 1 WON! " << std::endl;
            break;
        }
    }
}
const void TicTacToe::show() {
    system("CLS");
    for (int i = 0; i < size; i++) {
        std::cout << "        " << i << "   ";
    }
    std::cout << std::endl;
    for (int i = 0; i < size; i++) {
        std::cout << " ";
        for (int j = 0; j < size; j++) {
            std::cout << "------------";
        }
        std::cout << std::endl;
        std::cout << i;
        for (int k = 0; k < size; k++) {
            std::cout << " |" << "     " << board[i][k] << "    ";
            if (k == size - 1) {
                std::cout << "|";
            }
        }
        std::cout << std::endl;
        if (i == size - 1) {
            for (int j = 0; j < size; j++) {
                std::cout << "------------";
            }    
        }       
    }
    std::cout << std::endl; 
}

bool TicTacToe::isValidMove(int row, int col)
{
    return row >= 0 && row < size && col >= 0 && col < size && board[row][col] == ' ';
}


bool TicTacToe::checkWin(char sign)
{
    // check rows
    for (int i = 0; i < size; i++)
    {
        int count = 0;
        for (int j = 0; j < size; j++)
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
    for (int j = 0; j < size; j++)
    {
        int count = 0;
        for (int i = 0; i < size; i++)
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
    //x
    // x
    //  x
    // check diagonal down to right
    for (int i = 0; i <= size - NumbersInRow; i++)
    {
        for (int j = 0; j <= size - NumbersInRow; j++) {
            int count = 0;
            for (int k = 0; k < NumbersInRow; k++)
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
    //  x
    // x
    //x
    // check diagonal down to left
    for (int i = 0; i <= size - NumbersInRow; i++)
    {
        for (int j = NumbersInRow - 1; j < size; j++) {
            int count = 0;
            for (int k = 0; k < NumbersInRow; k++)
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
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == ' ')
                return false;
        }
    }

    return true;
}

void TicTacToe::AI(std::vector<std::vector<char>>& board, char sign, char opSign)
{
    int bestScore = INT_MIN;
    int bestRow = -1;
    int bestCol = -1;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (isValidMove(i, j)) {
                board[i][j] = sign;
                int score = minimax(board, 0, false, sign, opSign, INT_MIN, INT_MAX);
                board[i][j] = ' ';
                if (score > bestScore) {
                    bestScore = score;
                    bestCol = j;
                    bestRow = i;
                }
            }
        }
    }
    if (bestRow != -1 && bestCol != -1) {
        board[bestRow][bestCol] = sign;
    }
}

int TicTacToe::minimax(std::vector<std::vector<char>>& board, int depth, bool isMaximizingPlayer, char sign, char opSign, int alpha, int beta)
{
    if (depth == maxDepth || checkWin(sign) || checkWin(opSign) || checkDraw()) {
        return staticEvaluation(board, sign, opSign);
    }

    if (isMaximizingPlayer) {
        int bestScore = INT_MIN;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if(isValidMove(i, j)) {
                    board[i][j] = sign;
                    int score = minimax(board, depth + 1, false, sign, opSign, alpha, beta);
                    board[i][j] = ' ';
                    bestScore = std::max(bestScore, score);
                    alpha = std::max(alpha, bestScore);
                    if (alpha >= beta)
                        break;
                }
            }
            if (alpha >= beta)
                break;
        }
        return bestScore;
    } else {
        int bestScore = INT_MAX;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if(isValidMove(i, j)) {
                    board[i][j] = opSign;
                    int score = minimax(board, depth + 1, true, sign, opSign, alpha, beta);
                    bestScore = std::min(bestScore, score);
                    board[i][j] = ' ';                    
                    beta = std::min(beta, bestScore);
                    if (alpha >= beta)
                        break;
                }
            }
            if (alpha >= beta)
                break;
        }
        return bestScore;        
    }
}

int TicTacToe::staticEvaluation(std::vector<std::vector<char>>& board, int sign, int opSign)
{
    if (checkWin(sign)) {
        return 10;
    } else if (checkWin(opSign)) {
        return -10;
    } else {
        return 0;
    }
}