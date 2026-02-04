#include "Game/TestLevelLayer.hpp"
#include "Core/Physics.hpp"
#include "Core/Player.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace Game
{
    TestLevelLayer::TestLevelLayer()
    {
        character = new Core::Player({500, 500}, {{8, 9}, {24, 25}}, 10,
                                     sf::Texture("../../res/images/idle_0.png"));
        block = new Core::Entity({600, 600}, {{0, 0}, {15, 15}}, 10,
                                 sf::Texture("../../res/images/castle-tileset.png", false,
                                             {{16, 16}, {17, 17}}));
    }

    TestLevelLayer::~TestLevelLayer()
    {
        delete character;
        delete block;
    }

    bool TestLevelLayer::OnEvent(const sf::Event& event)
    {
        character->OnEvent(event);
        block->OnEvent(event);
        return false;
    }

    void TestLevelLayer::OnUpdate(float dt)
    {
        character->OnUpdate(dt);
        block->OnUpdate(dt);
        Core::AABB::Check(character, block);
    }

    void TestLevelLayer::OnRender(Core::Window& window)
    {
        sf::RenderWindow& renderWindow = window.GetRenderWindow();
        character->OnRender(renderWindow);
        block->OnRender(renderWindow);

        sf::RectangleShape charbox({character->m_hitbox.y.x - character->m_hitbox.x.x,
                                    character->m_hitbox.y.y - character->m_hitbox.x.y});
        charbox.setPosition(character->m_position);
        renderWindow.draw(charbox);

        sf::RectangleShape blockbox({block->m_hitbox.y.x - block->m_hitbox.x.x,
                                     block->m_hitbox.y.y - block->m_hitbox.x.y});
        blockbox.setPosition(block->m_position);
        blockbox.setFillColor(sf::Color::Cyan);
        renderWindow.draw(blockbox);
    }
} // namespace Game