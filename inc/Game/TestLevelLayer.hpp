#pragma once

#include "Core/Entity.hpp"
#include "Core/Layer.hpp"
#include "Core/Player.hpp"
#include <vector>

namespace Game
{
    class TestLevelLayer : public Core::Layer
    {
      public:
        Core::Player *character = nullptr;
        Core::Entity *block = nullptr;

      public:
        TestLevelLayer();
        virtual ~TestLevelLayer();

        bool OnEvent(const sf::Event& event) override;
        void OnUpdate(float timeStep) override;
        void OnRender(Core::Window& window) override;

      private:
        std::vector<Core::Entity *> entities;
    };
} // namespace Game