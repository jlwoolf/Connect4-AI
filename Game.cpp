//
// Created by jlwoolf on 3/4/21.
//

#include "Game.h"

Game::Game() {
    gameBoard.clear();
}

Game::Game(bool interactiveGame, const std::string& filename, bool computerStart, int depth) {
    std::ifstream fin(filename);
    int player = 1;
    if(fin.fail()) {
        gameBoard = Board();
    } else {
        gameBoard.loadFromFile(fin);
        fin >> player;
    }

    currentPlayer = player;

    this->interactiveGame = interactiveGame;
    this->computerStart = computerStart;
    this->depth = depth;

    interactive(computerStart);
}

int Game::minimaxDecision(Board board, int depth) {
    int utility = INT32_MIN;
    std::vector<int> col;
    int alpha = INT32_MIN, beta = INT32_MAX;
    for(int i : order) {
        Board childBoard = board;
        if(childBoard.makeMove(i, currentPlayer)) {
            int tempUtility = minValue(childBoard, depth - 1, alpha, beta);
            if(tempUtility > utility) {
                utility = tempUtility;
                col.clear();
                col.push_back(i);
            } else if(tempUtility == utility) {
                col.push_back(i);
            }
        }
    }
    return col[rand() % col.size()];
}

int Game::minValue(Board board, int depth, int alpha, int beta) {
    if(depth == 0 || board.endGame())
        return utility(board, currentPlayer);

    int utility = INT32_MAX;
    for(int i : order) {
        Board childBoard = board;
        if(childBoard.makeMove(i, oppositePlayer())) {
            utility = std::min(utility, maxValue(childBoard, depth - 1, alpha, beta));
            if(utility <= alpha) {
                return utility;
            }
            beta = std::min(alpha, utility);
        }
    }
    return utility;
}

int Game::maxValue(Board board, int depth, int alpha, int beta) {
    if(depth == 0 || board.endGame())
        return utility(board, currentPlayer);

    int utility = INT32_MIN;
    for(int i : order) {
        Board childBoard = board;
        if(childBoard.makeMove(i, currentPlayer)) {
            utility = std::max(utility, minValue(childBoard, depth - 1, alpha, beta));
            if(utility >= beta) {
                return utility;
            }
            alpha = std::max(alpha, utility);
        }
    }
    return utility;
}

int Game::utility(Board board, int player) {
    if(player == 1)
        return board.score(1) - board.score(2);
    else
        return board.score(2) - board.score(1);
}

int Game::oppositePlayer() {
    if(currentPlayer == 1)
        return 2;
    else
        return 1;
}

void Game::interactive(bool computerNext) {
    while (!gameBoard.endGame()) {
        gameBoard.print();
        std::cout << gameBoard.score(1) << "-" << gameBoard.score(2) << std::endl;
        if (computerNext) {
            gameBoard.makeMove(minimaxDecision(gameBoard, this->depth), currentPlayer);
            computerNext = false;
            currentPlayer = oppositePlayer();
            gameBoard.save("computer.txt", currentPlayer);
        } else {
            int humanInput = -1;
            do {
                if(humanInput != -1)
                    std::cout << "Invalid move. Try again: " << std::endl;
                else
                    std::cout << "Make a move (1-7): ";
                std::cin >> humanInput;
            } while (!gameBoard.makeMove(humanInput - 1, currentPlayer));
            std::cout << std::endl;
            computerNext = true;
            currentPlayer = oppositePlayer();
            gameBoard.save("human.txt", currentPlayer);
        }
    }
    gameBoard.print();
    std::cout << gameBoard.score(1) << "-" << gameBoard.score(2) << std::endl;
}

void Game::one_move() {
    gameBoard.print();
    std::cout << gameBoard.score(1) << "-" << gameBoard.score(2) << std::endl;
    if(gameBoard.endGame())
        return;
    gameBoard.makeMove(minimaxDecision(gameBoard, this->depth), currentPlayer);
    gameBoard.print();
    std::cout << gameBoard.score(1) << "-" << gameBoard.score(2) << std::endl;
    gameBoard.save(output, oppositePlayer());
}

Game::Game(bool interactiveGame, const std::string &input, const std::string &output, int depth) {
    std::ifstream fin(input);
    int player = 1;
    if(fin.fail()) {
        gameBoard = Board();
    } else {
        gameBoard.loadFromFile(fin);
        fin >> player;
    }

    currentPlayer = player;

    this->interactiveGame = interactiveGame;
    this->output = output;
    this->depth = depth;

    one_move();
}
