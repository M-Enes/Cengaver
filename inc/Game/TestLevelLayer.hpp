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
      public:
        TestLevelLayer();
        virtual ~TestLevelLayer();

        bool OnEvent(const sf::Event& event) override;
        void OnUpdate(float timeStep) override;
        void OnRender(Core::Window& window) override;

      private:
        bool debugMode = false;
        Core::Player *character = nullptr;
        std::vector<Core::Entity *> entities;
        static constexpr int blockCount = 6;
        Core::Entity *block[blockCount];
    };
} // namespace Game