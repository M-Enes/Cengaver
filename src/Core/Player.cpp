#include "Core/Player.hpp"
#include <cstdint>
#include <SFML/Window/Keyboard.hpp>

namespace Core
{
    Player::Player(sf::Vector2f position, sf::Vector2<sf::Vector2f> hitbox, float scale,
                   sf::Texture texture)
        : Entity(position, hitbox, scale, texture), m_state(Idle)
    {}

    Player::~Player() {}

    void Player::OnEvent(const sf::Event& event)
    {
        if (const auto *keyPressed = event.getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->scancode == sf::Keyboard::Scancode::A)
            {
                m_input.isAPressed = UINT16_MAX;
            }
            else if (keyPressed->scancode == sf::Keyboard::Scancode::D)
            {
                m_input.isDPressed = UINT16_MAX;
            }
            else if (keyPressed->scancode == sf::Keyboard::Scancode::W)
            {
                m_input.isWPressed = UINT16_MAX;
            }
            else if (keyPressed->scancode == sf::Keyboard::Scancode::S)
            {
                m_input.isSPressed = UINT16_MAX;
            }
        }
        else if (const auto *keyReleased = event.getIf<sf::Event::KeyReleased>())
        {
            if (keyReleased->scancode == sf::Keyboard::Scancode::A)
            {
                m_input.isAPressed = 0;
            }
            else if (keyReleased->scancode == sf::Keyboard::Scancode::D)
            {
                m_input.isDPressed = 0;
            }
            else if (keyReleased->scancode == sf::Keyboard::Scancode::W)
            {
                m_input.isWPressed = 0;
            }
            else if (keyReleased->scancode == sf::Keyboard::Scancode::S)
            {
                m_input.isSPressed = 0;
            }
        }
    }

    void Player::OnUpdate(float dt)
    {
        if (m_input.isAPressed < m_input.isDPressed)
            m_acceleration.x = 0.0001;
        else if (m_input.isAPressed > m_input.isDPressed)
            m_acceleration.x = -0.0001;
        else
            m_acceleration.x = 0;

        if (m_input.isSPressed < m_input.isWPressed)
            m_acceleration.y = -0.0001;
        else if (m_input.isSPressed > m_input.isWPressed)
            m_acceleration.y = 0.0001;
        else
            m_acceleration.y = 0;

        if (m_input.isAPressed) m_input.isAPressed -= 1;
        if (m_input.isDPressed) m_input.isDPressed -= 1;
        if (m_input.isWPressed) m_input.isWPressed -= 1;
        if (m_input.isSPressed) m_input.isSPressed -= 1;

        Entity::OnUpdate(dt);
    }

    void Player::OnRender(sf::RenderWindow& renderWindow)
    { renderWindow.draw(m_sprite); }

    void Player::Move(sf::Vector2f dx)
    { Entity::Move(dx); }

} // namespace Core
