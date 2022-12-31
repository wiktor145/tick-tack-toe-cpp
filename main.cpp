#include <iostream>
#include <csignal>

#include "game_player.h"

void signalHandler( int signum ) {
   exit(0);
}

int main()
{
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);

    GamePlayer *player = new GamePlayer();
    player -> play();

    return 0;
}
