#include <src/Core/game.h>
#include "exampleScene00.h"
#include "src/Core/scenemanager.h"

int main(void)
{
    Game game;
    ExampleScene00* scene00 = new ExampleScene00();

    SceneManager::GetInstance()->AddScene(scene00);

    do
    {
        game.Run(SceneManager::GetInstance()->GetLoadedScene());
    }
    while (game.IsRunning());

    delete scene00;

    return 0;
}
