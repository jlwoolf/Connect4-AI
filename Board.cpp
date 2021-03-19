//
// Created by jlwoolf on 3/4/21.
//

#include "Board.h"

bool Board::detectWin(int player) {
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            if(j < COLS - 3 && horizontalWin(i,j, player))
                return true;
            if(i < ROWS - 3 && verticalWin(i,j, player))
                return true;
            if(i < ROWS - 3 && j < COLS - 3 && diagonalRightWin(i,j, player))
                return true;
            if(i >= ROWS - 3 && j < COLS - 3 && diagonalLeftWin(i,j, player))
                return true;
        }
    }

    return false;
}

bool Board::verticalWin(int i, int j, int player) {
    return grid[i][j] == grid[i+1][j] && grid[i+1][j] == grid[i+2][j] && grid[i+2][j] == grid[i+3][j] && grid[i][j] == player;
}

bool Board::horizontalWin(int i, int j, int player) {
    return grid[i][j] == grid[i][j+1] && grid[i][j+1] == grid[i][j+2] && grid[i][j+2] == grid[i][j+3] && grid[i][j] == player;
}

bool Board::diagonalRightWin(int i, int j, int player) {
    return grid[i][j] == grid[i+1][j+1] && grid[i+1][j+1] == grid[i+2][j+2] && grid[i+2][j+2] == grid[i+3][j+3] && grid[i][j] == player;
}

bool Board::diagonalLeftWin(int i, int j, int player) {
    return grid[i][j] == grid[i-1][j+1] && grid[i-1][j+1] == grid[i-2][j+2] && grid[i-2][j+2] == grid[i-3][j+3] && grid[i][j] == player;
}

Board::Board() {
    clear();
}

Board::Board(const std::string& filename) {
    loadFromFile(filename);
}

Board::Board(std::ifstream &fin) {
    loadFromFile(fin);
}


void Board::loadFromFile(const std::string& filename) {
    std::ifstream fin(filename);
    if(fin.fail()) {
        std::cerr << "Invalid input file..." << std::endl;
        exit(-1);
    }

    loadFromFile(fin);
}

void Board::loadFromFile(std::ifstream &fin) {
    std::string rowString;
    for(std::array<int, COLS> &row : grid) {
        fin >> rowString;
        for(int j = 0; j < row.size(); j++) {
            row.at(j) = (int)rowString[j] - 48;
        }
    }
}

void Board::clear() {
    for(std::array<int, COLS> &row : grid) {
        for(int &cell : row) {
            cell = 0;
        }
    }
}

void Board::print() {
    for(std::array<int, COLS> &row : grid) {
        for(int &cell : row) {
            std::cout << cell;
        }
        std::cout << std::endl;
    }
}
void Board::save(const std::string& filename, int player) {
    std::ofstream fout(filename);
    if(fout.fail()) {
        std::cerr << "Error creating file...";
        std::exit(-1);
    }

    for(std::array<int, COLS> &row : grid) {
        for(int &cell : row) {
            fout << cell;
        }
        fout << std::endl;
    }
    fout << player;
    fout.close();
}

bool Board::makeMove(int column, int player) {
    if(grid[0][column] != 0 || column < 0 || column >= grid[0].size()) {
        //std::cout << "Invalid move..." << std::endl;
        return false;
    }

    for(int i = 0; i < ROWS; i++) {
        if (i == ROWS - 1 || grid[i + 1][column] != 0) {
            grid.at(i).at(column) = player;
            return true;
        } else {
            continue;
        }
    }
    return false;
}

int Board::score(int player) {
    int score = 0;
    for(int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (j < COLS - 3 && horizontalWin(i, j, player))
                score++;
            if (i < ROWS - 3 && verticalWin(i, j, player))
                score++;
            if (i < ROWS - 3 && j < COLS - 3 && diagonalRightWin(i, j, player))
                score++;
            if (i >= ROWS - 3 && j < COLS - 3 && diagonalLeftWin(i, j, player))
                score++;
        }
    }
    return score;
}

bool Board::endGame() {
    for(int i = 0; i < COLS; i++) {
        if(grid[0][i] == 0) {
            return false;
        }
    }
    return true;
}

