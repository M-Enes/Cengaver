#include "Core/Player.hpp"
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
                m_movRequest.horizontal = HorizontalMovement::Left;
            }
            else if (keyPressed->scancode == sf::Keyboard::Scancode::D)
            {
                m_movRequest.horizontal = HorizontalMovement::Right;
            }
            else if (keyPressed->scancode == sf::Keyboard::Scancode::W)
            {
                m_movRequest.vertical = VerticalMovement::Up;
            }
            else if (keyPressed->scancode == sf::Keyboard::Scancode::S)
            {
                m_movRequest.vertical = VerticalMovement::Down;
            }
        }
        else if (const auto *keyReleased = event.getIf<sf::Event::KeyReleased>())
        {
            if (keyReleased->scancode == sf::Keyboard::Scancode::A)
            {
                m_movRequest.horizontal = HorizontalMovement::None;
            }
            else if (keyReleased->scancode == sf::Keyboard::Scancode::D)
            {
                m_movRequest.horizontal = HorizontalMovement::None;
            }
            else if (keyReleased->scancode == sf::Keyboard::Scancode::W)
            {
                m_movRequest.vertical = VerticalMovement::None;
            }
            else if (keyReleased->scancode == sf::Keyboard::Scancode::S)
            {
                m_movRequest.vertical = VerticalMovement::None;
            }
        }
    }

    void Player::OnUpdate(float dt)
    {
        if (m_movRequest.horizontal == HorizontalMovement::Right)
            m_acceleration.x = 0.0001;
        else if (m_movRequest.horizontal == HorizontalMovement::Left)
            m_acceleration.x = -0.0001;
        else
            m_acceleration.x = 0;
        if (m_movRequest.vertical == VerticalMovement::Up)
            m_acceleration.y = -0.0001;
        else if (m_movRequest.vertical == VerticalMovement::Down)
            m_acceleration.y = 0.0001;
        else
            m_acceleration.y = 0;

        Entity::OnUpdate(dt);
    }

    void Player::OnRender(sf::RenderWindow& renderWindow)
    { renderWindow.draw(m_sprite); }

    void Player::Move(sf::Vector2f dx)
    { Entity::Move(dx); }

} // namespace Core
