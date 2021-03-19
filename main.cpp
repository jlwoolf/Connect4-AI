#include <iostream>
#include <cstring>
#include <ctime>
#include "Game.h"

int main(int argc, char** argv) {
    srand(time(NULL));
    if(argc != 5) {
        std::cerr << "Invalid arguments..." << std::endl;
        exit(-1);
    }

    bool interactive;
    std::string input, output;
    bool computerStart;
    int depth;

    if(strcmp(argv[1], "interactive") == 0) {
        interactive = true;
        if(strcmp(argv[3], "computer-next") == 0) {
            computerStart = true;
        } else if(strcmp(argv[3], "human-next") == 0){
            computerStart = false;
        } else {
            std::cerr << "Invalid arguments..." << std::endl;
            exit(-1);
        }
    } else if(strcmp(argv[1], "one-move") == 0) {
        interactive = false;
        output = argv[3];
    } else {
        std::cerr << "Invalid arguments..." << std::endl;
        exit(-1);
    }

    input = argv[2];

    depth = strtol(argv[4], nullptr, 10);

    if(interactive)
        Game game(interactive, input, computerStart, depth);
    else
        Game game(interactive, input, output, depth);
    return 0;
}
