#include "Core/Player.hpp"

namespace Core
{
    Player::Player(sf::Vector2f position, sf::Vector2<sf::Vector2f> hitbox, float scale,
                   sf::Texture texture)
        : Entity(position, hitbox, scale, texture), m_state(Idle)
    {}

    Player::~Player() {}

    void Player::OnEvent(const sf::Event& Event) {}

    void Player::OnUpdate(float dt)
    {
        m_velocity += m_acceleration * dt;
        sf::Vector2f dx = m_velocity * dt;
        m_position += dx;
        m_hitbox.x += dx;
        m_hitbox.y += dx;
        m_sprite.setPosition(m_position);
    }

    void Player::OnRender(sf::RenderWindow& renderWindow)
    {
        renderWindow.draw(m_sprite);
    }
} // namespace Core
