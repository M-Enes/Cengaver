#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include <string>

namespace Core
{
struct WindowSpecification
{
    std::string title;
    uint32_t width = 1280;
    uint32_t height = 720;
};

class Window
{
  public:
    Window(const WindowSpecification& specification);
    ~Window();

    void Create();
    void Destroy();

  private:
    WindowSpecification specification;
    sf::RenderWindow *renderWindow = nullptr;
};
} // namespace Core