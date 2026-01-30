#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

namespace Core
{
    class Entity
    {
      public:
        enum State
        {
            Idle,
            Running,
            Jumping,
            Falling,
            Attacking,
            Swimming,
            Victory,
            Loss
        };
        bool isAlive = true;
        sf::Vector2f m_position;
        sf::Vector2f m_velocity;
        sf::Vector2f m_acceleration;
        sf::Vector2<sf::Vector2f> m_hitbox;
        sf::Texture m_texture;
        sf::Sprite m_sprite;
        uint8_t m_animationFrame, m_animationOffset;

      public:
        Entity(sf::Vector2f position, std::string texturePath);
        virtual ~Entity();

        virtual void OnEvent(const sf::Event& Event);
        virtual void OnUpdate(float dt);
        virtual void OnRender(sf::RenderWindow& renderWindow);

      private:
        void Run();
    };
} // namespace Core