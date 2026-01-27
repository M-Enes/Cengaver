#include "Core/Game.hpp"

int main()
{
    Core::GameSpecification gameSpec;
    gameSpec.name = "Cengaver";
    gameSpec.windowSpec.width = 1920;
    gameSpec.windowSpec.height = 1080;

    Core::Game game(gameSpec);
    game.Run();
}