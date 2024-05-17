#include <iostream>
#include "TicTacToe.hpp"

int main()
{
    int size = 3, winCondition = 3;

    // std::cout << "Size of the board: ";
    // std::cin >> size;
    // std::cout << "\nWin condition (amount of marks in a row): ";
    // std::cin >> winCondition;

    TicTacToe TTT(size, winCondition);
    TTT.run();

    return 0;
}