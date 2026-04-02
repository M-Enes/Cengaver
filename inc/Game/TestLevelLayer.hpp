#pragma once

#include "Core/Entity.hpp"
#include "Core/GameContext.hpp"
#include "Core/Layer.hpp"
#include "Game/Player.hpp"
#include <memory>
#include <vector>

namespace Game
{
    class TestLevelLayer : public Core::Layer
    {
      public:
      public:
        TestLevelLayer();
        virtual ~TestLevelLayer();

        void OnAttach(Core::GameContext& context) override;
        bool OnEvent(const sf::Event& event) override;
        void OnUpdate(float timeStep) override;
        void OnRender(Core::Window& window) override;

      private:
        bool debugMode = false;
        Player *character = nullptr;
        std::vector<Core::Entity *> blocks;
        std::vector<std::unique_ptr<Core::Entity>> entities;
    };
} // namespace Game