#pragma once

#include "Core/Entity.hpp"

namespace Core
{
    class Player : public Entity
    {
        enum
        {
            Idle,
            Running,
            Jumping,
            Falling,
            Attacking,
            Swiming,
            Victory,
            Loss
        } m_state;

      public:
        Player(sf::Vector2f position, sf::Vector2<sf::Vector2f> hitbox, float scale,
               sf::Texture texture);
        ~Player();

        void OnEvent(const sf::Event& Event) override;
        void OnUpdate(float dt) override;
        void OnRender(sf::RenderWindow& renderWindow) override;
    };
} // namespace Core