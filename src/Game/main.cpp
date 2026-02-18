#include "Core/Game.hpp"
#include "Game/TestLevelLayer.hpp"

int main()
{
    Core::GameSpecification gameSpec;
    gameSpec.name = "Cengaver";
    gameSpec.windowSpec.width = 1280;
    gameSpec.windowSpec.height = 720;

    Core::Game game(gameSpec);
    Game::TestLevelLayer testLevel = Game::TestLevelLayer();
    game.PushLayer(testLevel);

    game.Run();
}