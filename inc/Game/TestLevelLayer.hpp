#pragma once

#include "Core/Layer.hpp"
#include "Core/Player.hpp"

namespace Game
{
    class TestLevelLayer : public Core::Layer
    {
      public:
        Core::Player *character = nullptr;

      public:
        TestLevelLayer();
        virtual ~TestLevelLayer();

        bool OnEvent(const sf::Event& event) override;
        void OnUpdate(float timeStep) override;
        void OnRender(Core::Window& window) override;
    };
} // namespace Game