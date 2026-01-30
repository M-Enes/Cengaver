#include "Core/Entity.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

namespace Core
{
    Entity::Entity(sf::Vector2f position, std::string texturePath)
        : m_texture(sf::Texture(texturePath)), m_sprite(m_texture)
    {
        m_position = position;
        m_sprite.setPosition(m_position);
    }
    Entity::~Entity() {};

    void Entity::OnEvent(const sf::Event& Event) {}

    void Entity::OnUpdate(float dt)
    {
        m_velocity += m_acceleration * dt;
        m_position += m_velocity * dt;
        m_hitbox = {m_position, m_position + sf::Vector2f{16, 16}};
    }

    void Entity::OnRender(sf::RenderWindow& renderWindow)
    {
        renderWindow.draw(m_sprite);
    }
} // namespace Core