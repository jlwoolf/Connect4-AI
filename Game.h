//
// Created by jlwoolf on 3/4/21.
//

#ifndef MINIMAX_GAME_H
#define MINIMAX_GAME_H

#include "Board.h"
#include <vector>

class Game {
private:
    Board gameBoard;
    bool interactiveGame;
    bool computerStart;
    int currentPlayer;
    int depth;
    std::string output;

    std::array<int,7> order = {3,2,4,1,5,0,6};
public:
    Game();
    Game(bool interactiveGame, const std::string& filename, bool computer, int depth);
    Game(bool interactiveGame, const std::string& input, const std::string& output, int depth);

    void interactive(bool computerNext);
    void one_move();

    int minimaxDecision(Board board, int depth);
    int minValue(Board board, int depth, int alpha, int beta);
    int maxValue(Board board, int depth, int alpha, int beta);
    int utility(Board board, int player);
    int oppositePlayer();
};


#endif //MINIMAX_GAME_H
