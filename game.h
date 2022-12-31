#ifndef TTT_GAME
#define TTT_GAME

#include "board.h"
#include <exception>
#include <string>
#include <iostream>

enum MoveOrder {
move_order_x = 0,
move_order_o = 1
};

const int MAX_BOARD_SIZE = 10;

class Game {

private:
    Board * board;
    MoveOrder currentMove;
    int winningLength;

    const int defaultSize = 3;
    const int defaultWinningLength = 3;

    void validateMove(int);
    bool isDecisiveResult();

    void drawHeader(int);
    void drawLine(int);
    void drawFieldLine(int, int);

public:
    Game();
    ~Game();

    void createNewGame();
    void createNewGame(int, int);
    void createNewGameLikeCurrent();

    void drawTable();

    void makeMove(int);
    void makeMove(int, int);

    bool isGameOver();

    int getBoardSize();

    std::string getCurrentPlayer();
};


class GameException : std::exception {
    private:
    char * message;

    public:
    GameException(char * msg) : message(msg) {}
    char * what () {
        return message;
    }
};

class BoardException : std::exception {
    private:
    char * message;

    public:
    BoardException(char * msg) : message(msg) {}
    char * what () {
        return message;
    }
};

#endif // TTT_GAME
