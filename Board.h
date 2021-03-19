//
// Created by jlwoolf on 3/4/21.
//

#ifndef MINIMAX_BOARD_H
#define MINIMAX_BOARD_H
#include <string>
#include <array>
#include <fstream>
#include <iostream>

class Board {
public:
    static const int ROWS = 6;
    static const int COLS = 7;

private:
    std::array<std::array<int, COLS>, ROWS> grid{};
    bool verticalWin(int i, int j, int player);
    bool horizontalWin(int i, int j, int player);
    bool diagonalRightWin(int i, int j, int player);
    bool diagonalLeftWin(int i, int j, int player);
public:


    Board();
    explicit Board(const std::string& filename);
    explicit Board(std::ifstream& fin);

    void loadFromFile(const std::string& filename);
    void loadFromFile(std::ifstream& fin);
    void clear();
    void print();
    void save(const std::string& filename, int player);
    bool makeMove(int column, int player);
    bool detectWin(int player);
    bool endGame();
    int score(int player);
};


#endif //MINIMAX_BOARD_H
