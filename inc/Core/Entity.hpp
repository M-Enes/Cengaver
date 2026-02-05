#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

namespace Core
{
    class Entity
    {
      public:
        struct
        {
            sf::Vector2f topLeft;
            sf::Vector2f bottomRight;
        } m_hitbox;

        bool isAlive = true;
        sf::Vector2f m_position, m_velocity, m_acceleration;
        float m_scale;
        const sf::Texture m_texture;
        sf::Sprite m_sprite;
        uint8_t m_animationFrame, m_animationOffset;

      public:
        ////////////////////////////////////////////////////////////
        /// \brief Constructs an entity
        ///
        /// \param position Start position
        ///
        /// \param hitbox Hitbox's corners' coordinates relative to top-left corner of the
        /// texture you passed
        ///
        /// \param scale Coefficient of the texture
        ///
        /// \param texture sf::Texture instance for entity
        ///
        ////////////////////////////////////////////////////////////
        Entity(sf::Vector2f position, sf::Vector2<sf::Vector2f> hitbox, float scale,
               sf::Texture texture);
        virtual ~Entity();

        virtual void OnEvent(const sf::Event& Event);
        virtual void OnUpdate(float dt);
        virtual void OnRender(sf::RenderWindow& renderWindow);

      private:
        void Run();
    };
} // namespace Core