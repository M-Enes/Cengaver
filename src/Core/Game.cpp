#include "Core/Game.hpp"
#include <memory>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include "Core/GameContext.hpp"
#include "Core/Layer.hpp"

namespace Core
{
    Game::Game(const GameSpecification& specification)
        : m_specification(specification)
    {
        if (specification.windowSpec.title.empty())
        {
            this->m_specification.windowSpec.title = specification.name;
        }

        m_window = std::make_unique<Window>(m_specification.windowSpec);
        m_window->Create();

        m_context = std::make_unique<GameContext>(*m_window, m_assetManager);
    }

    Game::~Game() {}

    void Game::Run()
    {
        m_running = true;

        sf::Clock clock;
        sf::Time previous = clock.restart();
        while (m_running)
        {
            if (m_window->ShouldClose())
            {
                Stop();
                break;
            }

            float elapsed = (float)clock.restart().asMicroseconds() / 1000;

            m_window->PollEvents(this);

            if (m_window->GetRenderWindow().hasFocus())
            {
                m_window->Clear();
                for (std::unique_ptr<Layer>& layer : m_layerStack)
                {
                    layer->OnUpdate(elapsed);
                }
                for (std::unique_ptr<Layer>& layer : m_layerStack)
                {
                    layer->OnRender(*m_window);
                }
                m_window->Display();
            }
        }
    }

    void Game::RaiseEvent(const sf::Event& event)
    {
        // events like sf::Event::Closed should also be handled here
        if (event.is<sf::Event::Closed>())
        {
            m_window->Close();
            return;
        }

        // traverse layers from front to back and send the event to them,
        // if event is handled, do not send the event to other layers, just break the loop

        Layer *layer;
        for (auto it = m_layerStack.rbegin(); it != m_layerStack.rend(); it++)
        {
            layer = it->get();
            if (layer->OnEvent(event)) { break; }
        }
    }

    void Game::Stop() { m_running = false; }

    void Game::PushLayer(std::unique_ptr<Layer> layer)
    {
        layer->OnAttach(*m_context);
        m_layerStack.push_back(std::move(layer));
    }

    AssetManager& Game::GetAssetManager() { return m_assetManager; }

} // namespace Core