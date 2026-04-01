#pragma once

#include "Core/Animable.hpp"
#include "Core/Collision.hpp"
#include "Core/Entity.hpp"
#include "Game/IMovementState.hpp"

namespace Game
{
    class Player : public Core::Entity, public Core::Animable
    {

      public:
        Player(sf::Vector2f position, sf::Vector2<sf::Vector2f> hitbox, float scale,
               KineticState kineticState, sf::Texture texture,
               std::string animationsPath);
        ~Player();

        void OnEvent(const sf::Event& Event) override;
        void OnUpdate(float dt) override;
        void OnRender(sf::RenderWindow& renderWindow) override;

        void Move(sf::Vector2f dx) override;

      private:
        const float MaxSpeed = 0.4;

        std::unique_ptr<IMovementState> m_movementState;

        struct
        {
            uint16_t isAPressed = 0;
            uint16_t isDPressed = 0;
            uint16_t isWPressed = 0;
            uint16_t isSPressed = 0;
        } m_input;
    };
} // namespace Game