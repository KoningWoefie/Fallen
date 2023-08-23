#include <src/game.h>
#include "exampleScene00.h"

int main(void)
{
    Game game;
    ExampleScene00* scene00 = new ExampleScene00();

    do
    {
        game.Run(scene00);
    } 
    while (game.IsRunning());
    
    delete scene00;

    return 0;
}