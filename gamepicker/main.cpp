#include <src/game.h>
#include "gamepickerScene.h"

int main(void)
{
    Game game;
    GamePickerScene* scene00 = new GamePickerScene();

    do
    {
        game.Run(scene00);
    } 
    while (game.IsRunning());
    
    delete scene00;

    return 0;
}