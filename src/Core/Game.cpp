#include "Core/Game.hpp"

namespace Core
{
Game::Game(const GameSpecification& specification)
    : specification(specification)
{
    if (specification.windowSpec.title.empty())
    {
        this->specification.windowSpec.title = specification.name;
    }

    window = new Window(specification.windowSpec);
    window->Create();
}

Game::~Game()
{
    window->Destroy();
}

void Game::Run()
{
    running = true;

    // while (running)
    // {
    // // poll events
    // // update layers
    // // render layers
    // }
}
} // namespace Core