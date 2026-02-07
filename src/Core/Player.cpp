#include "Core/Player.hpp"
#include <SFML/Window/Keyboard.hpp>

namespace Core
{
    Player::Player(sf::Vector2f position, sf::Vector2<sf::Vector2f> hitbox, float scale,
                   sf::Texture texture)
        : Entity(position, hitbox, scale, texture), m_state(Idle)
    {}

    Player::~Player() {}

    void Player::OnEvent(const sf::Event& Event)
    {
        if (inputProcessed)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
                m_velocity = {0, -0.5f};
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
                m_velocity = {-0.5f, 0};
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
                m_velocity = {0, 0.5f};
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
                m_velocity = {0.5f, 0};
            else
                m_velocity = {0, 0};

            inputProcessed = false;
        }
    }

    void Player::OnUpdate(float dt)
    {
        m_velocity += m_acceleration * dt;
        sf::Vector2f dx = m_velocity * dt;
        m_position += dx;
        m_hitbox.topLeft += dx;
        m_hitbox.bottomRight += dx;
        m_sprite.setPosition(m_position);
        inputProcessed = true;
    }

    void Player::OnRender(sf::RenderWindow& renderWindow)
    {
        renderWindow.draw(m_sprite);
    }

    void Player::Move(sf::Vector2f dx)
    {
        m_position += dx;
        m_hitbox.topLeft += dx;
        m_hitbox.bottomRight += dx;
        m_sprite.move(dx);
    }

} // namespace Core
