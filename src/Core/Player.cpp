#include "Core/Player.hpp"
#include "Core/log.hpp"
#include <cstdint>
#include <SFML/Window/Keyboard.hpp>
#include <string>

namespace Core
{
    Player::Player(sf::Vector2f position, sf::Vector2<sf::Vector2f> hitbox, float scale,
                   KineticState kineticState, sf::Texture texture)
        : Entity(position, hitbox, scale, kineticState, texture), m_state(Idle)
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
                m_input.isWPressed = 30;
                logger.info("Pressed W");
            }
            else if (keyPressed->scancode == sf::Keyboard::Scancode::S)
            {
                m_input.isSPressed = 30;
                logger.info("Pressed S");
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
                logger.info("Released W");
            }
            else if (keyReleased->scancode == sf::Keyboard::Scancode::S)
            {
                m_input.isSPressed = 0;
                logger.info("Released S");
            }
        }
    }

    void Player::OnUpdate(float dt)
    {
        m_previousHitbox = m_hitbox;

        if (m_input.isAPressed < m_input.isDPressed)
        {
            if (m_velocity.x < 0)
                m_acceleration.x = 0.010;
            else
                m_acceleration.x = 0.002;
        }
        else if (m_input.isAPressed > m_input.isDPressed)
        {
            if (m_velocity.x > 0)
                m_acceleration.x = -0.010;
            else
                m_acceleration.x = -0.002;
        }
        else
        {
            if (m_velocity.x < 0.005 && m_velocity.x > -0.005) m_velocity.x = 0;
            if (m_velocity.x > 0)
                m_acceleration.x = -0.001;
            else if (m_velocity.x < 0)
                m_acceleration.x = 0.001;
            else
                m_acceleration.x = 0;
        }

        if (m_input.isSPressed < m_input.isWPressed)
        {
            if (isGrounded)
            {
                m_velocity.y = -0.45;
                isGrounded = false;
            }
        }

        else if (m_input.isSPressed > m_input.isWPressed)
            m_acceleration.y = 0.002;
        else
            m_acceleration.y = 0;

        if (m_input.isAPressed) m_input.isAPressed -= 1;
        if (m_input.isDPressed) m_input.isDPressed -= 1;
        if (m_input.isWPressed) m_input.isWPressed -= 1;
        if (m_input.isSPressed) m_input.isSPressed -= 1;

        m_velocity += (m_acceleration + m_gravity) * dt;

        if (m_velocity.x > MaxSpeed) { m_velocity.x = MaxSpeed; }
        else if (m_velocity.x < -MaxSpeed) { m_velocity.x = -MaxSpeed; }
        if (m_velocity.y > MaxSpeed) { m_velocity.y = MaxSpeed; }

        Move(m_velocity * dt);

        logger.info(std::to_string(m_velocity.x) + ", " + std::to_string(m_velocity.y));
    }

    void Player::OnRender(sf::RenderWindow& renderWindow)
    {
        renderWindow.draw(m_sprite);
    }

    void Player::Move(sf::Vector2f dx)
    {
        Entity::Move(dx);
    }

} // namespace Core
