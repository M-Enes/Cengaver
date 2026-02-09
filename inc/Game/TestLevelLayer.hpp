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
        bool debugMode = false;
        Core::Player *character = nullptr;
        Core::Entity *block[6] = {nullptr};

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