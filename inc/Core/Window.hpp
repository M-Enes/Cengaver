#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include <cstdint>
#include <string>

namespace Core
{
struct WindowSpecification
{
    std::string title;
    uint32_t width = 1280;
    uint32_t height = 720;

    /* Frames Per Second Limit
    make it 0 to not limit FPS */
    uint32_t fpsLimit = 60;

    /* enabling VSync while fpsLimit is different than 0 could
    cause weird behavior */
    bool vsyncEnabled = false;

    bool fullScreen = true;
};

class Game;

class Window
{
  public:
    Window(const WindowSpecification& specification);
    ~Window();

    void Create();
    void Destroy();
    void Close();

    bool ShouldClose() const;
    void PollEvents(Game *game);

  private:
    WindowSpecification specification;
    sf::RenderWindow *renderWindow = nullptr;
};
} // namespace Core