#include <src/Core/game.h>
#include "CardGame/cardScene.h"

int main(void)
{
    Game game;
    CardScene* cardScene = new CardScene();
    do
    {
        game.Run(cardScene);
    }
    while (game.IsRunning());

    return 0;
}
