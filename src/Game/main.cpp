#include "Core/Game.hpp"
// #include "Core/log.hpp"
#include "Game/TestLevelLayer.hpp"
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Window.hpp>

int main()
{
    // Core::logger.info("Init Start");
    Core::GameSpecification gameSpec;
    gameSpec.name = "Cengaver";
    gameSpec.windowSpec.width = 640;
    gameSpec.windowSpec.height = 360;

    Core::Game game(gameSpec);
    Game::TestLevelLayer testLevel = Game::TestLevelLayer();
    game.PushLayer(testLevel);
    // Core::logger.info("Init Finish");

    game.Run();
}