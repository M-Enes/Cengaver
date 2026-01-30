#pragma once

#include "Core/Entity.hpp"
#include "Core/Layer.hpp"

namespace Game
{
    class TestLevelLayer : public Core::Layer
    {
      public:
        Core::Entity * character = nullptr;

      public:
        TestLevelLayer();
        virtual ~TestLevelLayer();

        bool OnEvent(const sf::Event& event) override;
        void OnUpdate(float timeStep) override;
        void OnRender(Core::Window& window) override;
    };
} // namespace Game