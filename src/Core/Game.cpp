#include "Core/Game.hpp"
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include "Core/Layer.hpp"

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

    sf::Clock clock;
    sf::Time previous = clock.restart();
    while (running)
    {
        if (window->ShouldClose())
        {
            Stop();
            break;
        }

        int32_t elapsed = clock.restart().asMilliseconds();

        window->PollEvents(this);

        window->Clear();

        for (Layer *layer : layerStack) { layer->OnUpdate(elapsed); }
        for (Layer *layer : layerStack) { layer->OnRender(*window); }

        window->Display();
    }
}

void Game::RaiseEvent(const sf::Event& event)
{
    // events like sf::Event::Closed should also be handled here
    if (event.is<sf::Event::Closed>())
    {
        window->Close();
        return;
    }

    // traverse layers from front to back and send the event to them,
    // if event is handled, do not send the event to other layers, just break the loop

    Layer *layer;
    for (auto it = layerStack.rbegin(); it != layerStack.rend(); it++)
    {
        layer = *it;
        if (layer->OnEvent(event)) { break; }
    }
}

void Game::Stop()
{
    running = false;
}

void Game::PushLayer(Layer& layer)
{
    layerStack.push_back(&layer);
}

} // namespace Core