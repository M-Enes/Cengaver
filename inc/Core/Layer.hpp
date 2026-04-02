#pragma once

#include "Core/Window.hpp"
#include "GameContext.hpp"
#include <SFML/Graphics.hpp>

namespace Core
{
    class Layer
    {
      public:
        virtual ~Layer() = default;

        virtual void OnAttach(GameContext& context) {};
        virtual bool OnEvent(const sf::Event& event) { return false; };
        virtual void OnUpdate(float timeStep) {};
        virtual void OnRender(Core::Window& window) {};

      private:
    };
} // namespace Core