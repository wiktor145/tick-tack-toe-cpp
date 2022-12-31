#ifndef TTT_GAMEPLAYER
#define TTT_GAMEPLAYER

#include "game.h"
#include <string>
#include <chrono>
#include <thread>
#include <stdlib.h>
#include <iostream>

enum MenuCommand {
    menu_command_exit = 0,
    menu_command_start_game = 1
};


class GamePlayer {
private:

    Game * game;

    void clearScreen();
    void showMenu();
    void showMenu(std::string);
    MenuCommand parseMenuInput();
    void configureGame();
    void playGame();
    void exitGame();
    void showGoodbyeScreen();

public:
    GamePlayer();
    ~GamePlayer();


    void play();
};

#endif // TTT_GAMEPLAYER
