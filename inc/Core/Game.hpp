#pragma once

#include "Core/Layer.hpp"
#include "Core/Window.hpp"
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

        void PushLayer(Layer& layer);

        void RaiseEvent(const sf::Event& event);

      private:
        GameSpecification specification;
        Window * window;
        bool running = false;
        std::vector<Layer *> layerStack;
    };
} // namespace Core