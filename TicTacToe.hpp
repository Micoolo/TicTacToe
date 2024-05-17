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


public:
    TicTacToe(int size, int NumbersInRow);
    void run();
};