#include "Core/Window.hpp"
#include "Core/Game.hpp"
#include <memory>
#include <optional>

namespace Core
{
    Window::Window(const WindowSpecification& specification)
        : specification(specification)
    {}

    void Window::Create()
    {
        renderWindow = std::make_unique<sf::RenderWindow>(
            sf::VideoMode({specification.width, specification.height}),
            specification.title,
            specification.fullScreen ? sf::State::Fullscreen : sf::State::Windowed);

        renderWindow->setVerticalSyncEnabled(specification.vsyncEnabled);
        renderWindow->setFramerateLimit(specification.fpsLimit);
        renderWindow->setKeyRepeatEnabled(specification.keyRepeat);
    }

    void Window::Close()
    {
        if (renderWindow) { renderWindow->close(); };
    }

    bool Window::ShouldClose() const { return !renderWindow->isOpen(); }

    void Window::PollEvents(Game *game)
    {
        while (const std::optional event = renderWindow->pollEvent())
        {
            if (event.has_value()) { game->RaiseEvent(event.value()); }
        }
    }

    void Window::Clear() { renderWindow->clear(); }

    void Window::Display() { renderWindow->display(); }

    /* Do not call before Create() or after Destroy() */
    sf::RenderWindow& Window::GetRenderWindow() { return *renderWindow; }

} // namespace Core