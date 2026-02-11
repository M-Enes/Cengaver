#include "Core/Entity.hpp"

namespace Core
{
    int Entity::idCounter = 0;

    Entity::Entity(sf::Vector2f position, sf::Vector2<sf::Vector2f> hitbox, float scale,
                   sf::Texture texture)
        : m_position(position), m_scale(scale), m_texture(texture), m_sprite(m_texture)
    {
        m_hitbox = {m_position + m_scale * hitbox.x, m_position + m_scale * hitbox.y};
        m_sprite.setPosition(m_position);
        m_sprite.setScale({m_scale, m_scale});
    }

    Entity::~Entity() {}

    void Entity::OnEvent(const sf::Event& event) {}

    void Entity::OnUpdate(float dt)
    {
        m_velocity += m_acceleration * dt;
        Move(m_velocity * dt);
    }

    void Entity::OnRender(sf::RenderWindow& renderWindow)
    {
        renderWindow.draw(m_sprite);
    }

    void Entity::Move(sf::Vector2f dx)
    {
        m_position += dx;
        m_hitbox.topLeft += dx;
        m_hitbox.bottomRight += dx;
        m_sprite.move(dx);
    }
} // namespace Core