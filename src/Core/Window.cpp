#include "Core/Window.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Window/VideoMode.hpp>

namespace Core
{
Window::Window(const WindowSpecification& specification)
    : specification(specification)
{}

Window::~Window()
{
    Destroy();
}

void Window::Create()
{
    renderWindow = new sf::RenderWindow(
        sf::VideoMode({specification.width, specification.height}), specification.title);
}

void Window::Destroy()
{
    if (renderWindow) { delete renderWindow; }

    renderWindow = nullptr;
}

} // namespace Core