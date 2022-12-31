#include "game_player.h"


GamePlayer::GamePlayer() {
    game = nullptr;
}

GamePlayer::~GamePlayer() {
    if (game != nullptr) {
        delete game;
    }
}

void GamePlayer::play() {

    MenuCommand command;

    while (1) {
        clearScreen();
        command = parseMenuInput();

        if (command == MenuCommand(menu_command_start_game)) {
            configureGame();
            playGame();
        } else if (command == MenuCommand(menu_command_exit)) {
            exitGame();
        }
    }
}

void GamePlayer::exitGame() {
    clearScreen();
    showGoodbyeScreen();
    exit(0);
}

void GamePlayer::showGoodbyeScreen() {
    std::cout << "|------------------------------------------|" << std::endl;
    std::cout << "|---Thank you for playing tick tack toe!---|" << std::endl;
    std::cout << "|------------See you next time!------------|" << std::endl;
    std::cout << "|------------------------------------------|" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
}

void GamePlayer::clearScreen() {
    //this is supposedly a bad idea...
    // Oh no! Anyway...

    if (system("cls")) {
        system("clear");
    }
}

void GamePlayer::showMenu() {
    showMenu("");
}


void GamePlayer::showMenu(std::string errorToShow) {
    std::cout << "||===============================||" << std::endl;
    std::cout << "||         TICK TACK TOE         ||" << std::endl;
    std::cout << "||===============================||" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Choose, what you want do do:" << std::endl;
    std::cout << std::endl;
    std::cout << "1 - Begin new game" << std::endl;
    std::cout << "2 - Exit" << std::endl;
    std::cout << std::endl;
    if (errorToShow == "") {
        std::cout << "Type a number and confirm by [ENTER]: ";
    } else {
       std::cout << errorToShow;
    }
}


MenuCommand GamePlayer::parseMenuInput() {
    std::string input;

    while (1)  {
        clearScreen();
        showMenu();

        std::cin >> input;

        if (input == "1") {
            return MenuCommand(menu_command_start_game);
        } else if (input == "2") {
            return MenuCommand(menu_command_exit);
        } else {
            std::cin.clear();
            clearScreen();
            showMenu("Incorrect input!");
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }
}

void GamePlayer::configureGame() {

    clearScreen();

    if (game != nullptr) {
        delete game;
    }
    game = new Game();

    std::string gameMode;
    int boardSize;
    int winningLength;

    std::cout << "Choose Game mode" <<std::endl;

    while (1) {
        std::cout << "1 - player vs player; 2 - player vs computer" << std::endl;
        std::cout << "Your choice: ";
        std::cin >> gameMode;
        std::cin.clear();
        if (gameMode == "1") {
          break;
        } else if (gameMode == "2") {
            std::cout << "Unfortunately, this mode is not yet available :(" <<std::endl;
        } else {
            std::cout << "Incorrect mode!" <<std::endl;
        }
    }

    std::cout << "Choose board size" <<std::endl;

    while (1) {
        std::cout << "Valid sizes are from 2 to 10. Enter 0 to get default 3x3" << std::endl;
        std::cout << "Your choice: ";
        std::cin >> boardSize;
        std::cin.clear();
        if (boardSize == 0) {
          boardSize = 3;
          break;
        } else if (boardSize < 2 || boardSize > 10) {
            std::cout << "Incorrect size!" <<std::endl;
        } else {
            break;
        }
    }

    if (boardSize != 3) {
        std::cout << "Choose winning length" <<std::endl;

        while (1) {
            std::cout << "Your choice: ";
            std::cin >> winningLength;
            std::cin.clear();
            try {
                game -> createNewGame(boardSize, winningLength);
                break;
            } catch (BoardException& ex) {
                std::cout << std::endl;
                std::cout << ex.what();
                std::cout << std::endl;
            }
        }
    } else {
        game -> createNewGame();
    }

}

void GamePlayer::playGame() {

    int moveInt, row, col;
    int afterGameChoice;

    while (1) {
    start:
        moveInt = -1;

        clearScreen();

        std::cout << std::endl;
        std::cout << std::endl;

        game -> drawTable();

        std::cout << std::endl;
        std::cout << std::endl;

        if (game -> isGameOver()) {
            std::cout << std::endl;
            std::cout << "Press 1 to play again. Press 2 to exit to main menu." << std::endl;

            while (1) {
                std::cout << "Your choice: ";
                std::cin >> afterGameChoice;
                std::cin.clear();

                if (afterGameChoice == 1) {
                    game -> createNewGameLikeCurrent();
                    goto start;
                } else if (afterGameChoice == 2) {
                    return;
                }
            }
        }

        std::cout << "Current player: " << game -> getCurrentPlayer() << std::endl;
        std::cout << std::endl;

        while (1) {
            std::cout << "Row: ";
            std::cin >> row;
            std::cin.clear();
            std::cout << std::endl;
            std::cout << "Column: ";
            std::cin >> col;
            std::cin.clear();

            try {
                game -> makeMove(row, col);
                break;
            } catch (GameException ex) {
                std::cout << std::endl;
                std::cout << ex.what();
                std::cout << std::endl;
            }
        }

    }
}
