#include "Core/Game.hpp"
#include "Game/TestLevelLayer.hpp"
#include <memory>

int main()
{
    Core::GameSpecification gameSpec;
    gameSpec.name = "Cengaver";
    gameSpec.windowSpec.width = 1280;
    gameSpec.windowSpec.height = 720;

    Core::Game game(gameSpec);
    std::unique_ptr<Game::TestLevelLayer> testLevel =
        std::make_unique<Game::TestLevelLayer>();

    game.PushLayer(std::move(testLevel));

    game.Run();
}