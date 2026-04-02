#pragma once

#include "AssetManager.hpp"
#include "Core/Layer.hpp"
#include "Core/Window.hpp"
#include "GameContext.hpp"
#include <memory>
#include <SFML/Window/Event.hpp>
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
        void Stop();

        void PushLayer(std::unique_ptr<Layer> layer);

        void RaiseEvent(const sf::Event& event);

        AssetManager& GetAssetManager();

      private:
        GameSpecification m_specification;
        std::unique_ptr<Window> m_window;
        AssetManager m_assetManager;
        std::unique_ptr<GameContext> m_context;
        bool m_running = false;
        std::vector<std::unique_ptr<Layer>> m_layerStack;
    };
} // namespace Core