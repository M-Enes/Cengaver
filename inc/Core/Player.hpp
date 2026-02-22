#pragma once

#include "Core/Collision.hpp"
#include "Core/Entity.hpp"

namespace Core
{
    class Player : public Entity
    {

      public:
        Player(sf::Vector2f position, sf::Vector2<sf::Vector2f> hitbox, float scale,
               KineticState kineticState, sf::Texture texture);
        ~Player();

        void OnEvent(const sf::Event& Event) override;
        void OnUpdate(float dt) override;
        void OnRender(sf::RenderWindow& renderWindow) override;

        void Move(sf::Vector2f dx) override;

      private:
        const float MaxSpeed = 0.4;

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

        struct
        {
            uint16_t isAPressed = 0;
            uint16_t isDPressed = 0;
            uint16_t isWPressed = 0;
            uint16_t isSPressed = 0;
        } m_input;
    };
} // namespace Core