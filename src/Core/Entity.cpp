#include "Core/Entity.hpp"

namespace Core
{
    Entity::Entity(sf::Vector2f position, sf::Vector2<sf::Vector2f> hitbox, float scale,
                   sf::Texture texture)
        : m_position(position),
          m_hitbox(hitbox),
          m_texture(texture),
          m_sprite(m_texture),
          m_scale(scale)
    {
        m_sprite.setOrigin(m_hitbox.x);
        m_sprite.setPosition(m_position);
        m_sprite.setScale({m_scale, m_scale});
    }

    Entity::~Entity() {};

    void Entity::OnEvent(const sf::Event& Event) {}

    void Entity::OnUpdate(float dt)
    {
        m_velocity += m_acceleration * dt;
        sf::Vector2f dx = m_velocity * dt;
        m_position += dx;
        m_hitbox.x += dx;
        m_hitbox.y += dx;
        m_sprite.setPosition(m_position);
    }

    void Entity::OnRender(sf::RenderWindow& renderWindow)
    {
        renderWindow.draw(m_sprite);
    }
} // namespace Core