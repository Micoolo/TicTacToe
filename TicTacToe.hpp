#pragma once 
#include <iostream>
#include <vector>

class TicTacToe {
private:
    int size;
    int NumbersInRow;
    int maxDepth;
    std::vector<std::vector<char>> board;

    bool isValidMove(int row, int column);

    bool checkWin(char sign);

    bool checkDraw();

    const void show();

    void AI(std::vector<std::vector<char>>& board, char sign, char opSign);

    int minimax(std::vector<std::vector<char>>& board, int depth, bool isMaximizingPlayer, char sign, char opSign, int alpha, int beta);

public:
    TicTacToe(int size, int NumbersInRow);
    void run();
};