#include <src/Core/game.h>
#include "CardGame/homescene.h"

int main(void)
{
    Game game;
    HomeScene* cardScene = new HomeScene();
    do
    {
        game.Run(cardScene);
    }
    while (game.IsRunning());

    return 0;
}
