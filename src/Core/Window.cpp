#include "Core/Window.hpp"
#include "Core/Game.hpp"
#include <optional>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowEnums.hpp>


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
        sf::VideoMode({specification.width, specification.height}), specification.title,
        specification.fullScreen ? sf::State::Fullscreen : sf::State::Windowed);

    renderWindow->setVerticalSyncEnabled(specification.vsyncEnabled);
    renderWindow->setFramerateLimit(specification.fpsLimit);
}

void Window::Destroy()
{
    if (renderWindow) { delete renderWindow; }

    renderWindow = nullptr;
}

void Window::Close()
{
    renderWindow->close();
}

bool Window::ShouldClose() const
{
    return !renderWindow->isOpen();
}

void Window::PollEvents(Game *game)
{
    while (const std::optional event = renderWindow->pollEvent())
    {
        if (event.has_value()) { game->RaiseEvent(event.value()); }
    }
}

} // namespace Core