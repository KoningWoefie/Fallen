#include <src/Core/game.h>
#include "Tetris/gamescene.h"
#include "src/Core/scenemanager.h"

int main(void)
{
    Game game;
    GameScene* gameScene = new GameScene();

    SceneManager::GetInstance()->AddScene(gameScene);

    do
    {
        game.Run(SceneManager::GetInstance()->GetLoadedScene());
    }
    while (game.IsRunning());

    return 0;
}
