#pragma once

#include "Core/Entity.hpp"
#include <SFML/System/Vector2.hpp>

namespace Core
{
    class Player : public Entity
    {
        enum State
        {
            Idle,
            Running,
            Jumping,
            Falling,
            Attacking,
            Swiming,
            Victory,
            Loss
        };

      public:
        Player(sf::Vector2f position, std::string texturePath);
        ~Player();

        void OnEvent(const sf::Event& Event) override;
        void OnUpdate(float dt) override;
        void OnRender(sf::RenderWindow& renderWindow) override;
    };
} // namespace Core