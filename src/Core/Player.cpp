#include "Core/Player.hpp"

namespace Core
{
    Player::Player(sf::Vector2f position, std::string texturePath)
        : Entity(position, texturePath)
    {
        m_position = position;
        m_sprite.setPosition(m_position);
        m_sprite.setScale({5, 5});
    }

    Player::~Player() {}

    void Player::OnEvent(const sf::Event& Event) {}

    void Player::OnUpdate(float dt)
    {
        m_velocity += m_acceleration * dt;
        m_position += m_velocity * dt;
        m_sprite.setPosition(m_position);
        m_hitbox = {m_position, m_position + sf::Vector2f{16, 16}};
    }

    void Player::OnRender(sf::RenderWindow& renderWindow)
    {
        renderWindow.draw(m_sprite);
    }
} // namespace Core
