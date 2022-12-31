#include "game.h"

Game::Game() {
    board = nullptr;
}

Game::~Game() {
    if (board != nullptr) {
        delete board;
    }
}

void Game::createNewGame() {
    createNewGame(defaultSize, defaultWinningLength);
}

void Game::createNewGame(int boardSize1, int winningLength1) {
    if (boardSize1 > MAX_BOARD_SIZE) {
        throw BoardException("Provided board size is greater than maximum allowed.");
    }

    if (winningLength1 > boardSize1) {
        throw BoardException("Winning length can not be longer than board size.");
    }


    if (board != nullptr) {
        delete board;
    }

    currentMove = MoveOrder(move_order_x);

    winningLength = winningLength1;

    board = new Board;

    board -> boardSize = boardSize1;
    board -> T = new Field[boardSize1 * boardSize1];

    for (int i = 0; i < boardSize1 * boardSize1; i++) {
       board -> T[i] = Field(field_free);
    }

}

void Game::createNewGameLikeCurrent() {
    createNewGame(getBoardSize(), winningLength);
}


void Game::drawTable() {
    drawHeader(getBoardSize());
    drawLine(getBoardSize());

    for (int row = 0; row < getBoardSize(); row++) {
        drawFieldLine(row, getBoardSize());
        drawLine(getBoardSize());
    }
}

void Game::drawHeader(int boardSize) {
    std::cout << "   ";

    for (int i = 0; i < boardSize; i++) {
        std::cout << " " << i << "  ";
    }

    std::cout << std::endl;
}

void Game::drawLine(int boardSize) {
    std::cout << "  +";

    for (int i = 0; i < boardSize; i++) {
        std::cout << " - +";
    }

    std::cout << std::endl;
}

void Game::drawFieldLine(int row, int boardSize) {
    std::cout << row << " +";

    for (int col = row * boardSize; col < (row + 1) * boardSize; col++) {
        std::cout << " " << fieldToChar(board -> T[col]) << " |";
    }

    std::cout << std::endl;
}

void Game::makeMove(int moveInt) {
    validateMove(moveInt);

    board -> T[moveInt] = currentMove == MoveOrder(move_order_o) ? Field(field_o) : Field(field_x);
    currentMove = currentMove == MoveOrder(move_order_o) ? MoveOrder(move_order_x) : MoveOrder(move_order_o);
}

void Game::makeMove(int row, int col) {
    if (row < 0 || row >= getBoardSize()) {
        throw GameException("Invalid move - exceeded board size in row");
    }

    if (col < 0 || col >= getBoardSize()) {
        throw GameException("Invalid move - exceeded board size in column");
    }
    makeMove(col + row * getBoardSize());
}

void Game::validateMove(int moveInt) {
    if (moveInt < 0 || moveInt > getBoardSize() * board -> boardSize) {
        throw GameException("Invalid move - exceeded board size");
    }

    if (board -> T[moveInt] != Field(field_free)) {
        throw GameException("Invalid move - field is already taken");
    }
}

bool Game::isGameOver() {
    if (isDecisiveResult()) {
        std::cout << "Game Over!" << std::endl << "Game won by " << (currentMove == MoveOrder(move_order_o) ? "x" : "o") << std::endl;
        return true;
    }

    bool boardFull = true;

    for (int i = 0; i < getBoardSize() * getBoardSize(); i++) {
        if (board -> T[i] == Field(field_free)) {
            boardFull = false;
            break;
        }
    }

    if (boardFull) {
        std::cout << "Game Over!" << std::endl << "Game ended in a draw." << std::endl;
        return true;
    }

    return false;
}


bool Game::isDecisiveResult() {
    //checking rows
    bool isWinning = false;

    for (int row = 0; row < getBoardSize(); row++) {
        for (int a = 0; a < getBoardSize() - winningLength + 1; a++) {
            if (board -> T[row * getBoardSize()  + a] == Field(field_free)) {
                continue;
            }
            isWinning = true;
            for (int i = 1; i < winningLength; i++) {
                if (board -> T[row * getBoardSize()  + a] != board -> T[row * getBoardSize()  + a + i]) {
                    isWinning = false;
                    break;
                }
            }
            if (isWinning) {
                return true;
            }
        }
    }

    //checking columns
    for (int col = 0; col < getBoardSize(); col++) {
        for (int a = 0; a < getBoardSize() - winningLength + 1; a++) {
            if (board -> T[(a) * getBoardSize() + col] == Field(field_free)) {
                continue;
            }
            isWinning = true;
            for (int i = 1; i < winningLength; i++) {
                if (board -> T[(a) * getBoardSize() + col] != board -> T[(a + i) * getBoardSize()  + col]) {
                    isWinning = false;
                    break;
                }
            }
            if (isWinning) {
                return true;
            }
        }
    }


    //checking diagonals right down
    for (int row = 0; row < getBoardSize(); row++) {
        for (int col = 0; col < getBoardSize(); col++) {
            if (row < getBoardSize() - winningLength + 1 && col < getBoardSize() - winningLength + 1) {
                if (board -> T[row * getBoardSize() + col] == Field(field_free)) {
                    continue;
                }
                isWinning = true;

                for (int i = 1; i < winningLength; i++) {
                    if (board -> T[row * getBoardSize() + col] != board -> T[(row + i) * getBoardSize() + col + i]) {
                        isWinning = false;
                        break;
                    }
                }

                if (isWinning) {
                    return true;
                }
            }
        }
    }

    //checking diagonals right up
    for (int row = 0; row < getBoardSize(); row++) {
        for (int col = 0; col < getBoardSize(); col++) {
            if (row - winningLength + 1 >= 0 && col < getBoardSize() - winningLength + 1) {
                if (board -> T[row * getBoardSize() + col] == Field(field_free)) {
                    continue;
                }
                isWinning = true;

                for (int i = 1; i < winningLength; i++) {
                    if (board -> T[row * getBoardSize() + col] != board -> T[(row - i) * getBoardSize() + col + i]) {
                        isWinning = false;
                        break;
                    }
                }

                if (isWinning) {
                    return true;
                }
            }
        }
    }


    return false;
}

std::string Game::getCurrentPlayer() {
    return currentMove == MoveOrder(move_order_o) ? "O" : "X";
}

int Game::getBoardSize() {
    return board -> boardSize;
}


