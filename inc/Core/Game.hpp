#pragma once

#include "Window.hpp"
#include <string>

namespace Core
{
struct GameSpecification
{
    std::string name = "Game";
    WindowSpecification windowSpec;
};

class Game
{
  public:
    Game(const GameSpecification& specification);
    ~Game();

    void Run();

  private:
    GameSpecification specification;
    Window *window;
    bool running = false;
};
} // namespace Core