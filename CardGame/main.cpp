#include <src/Core/game.h>
#include "CardGame/homescene.h"
#include "CardGame/cardScene.h"
#include "src/Core/scenemanager.h"

int main(void)
{
    Game game;
    HomeScene* homeScene = new HomeScene();
    CardScene* cardScene = new CardScene();

    SceneManager::GetInstance()->AddScene(homeScene);
    SceneManager::GetInstance()->AddScene(cardScene);

    do
    {
        game.Run(SceneManager::GetInstance()->GetLoadedScene());
    }
    while (game.IsRunning());

    return 0;
}
