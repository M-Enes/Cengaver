#include "Game/TestLevelLayer.hpp"
#include "Core/Physics.hpp"
#include "Core/Player.hpp"
#include <iostream>
#include <SFML/Graphics/VertexArray.hpp>

namespace Game
{
    TestLevelLayer::TestLevelLayer()
    {
        character = new Core::Player({100, 100}, {{8, 9}, {24, 25}}, 6,
                                     sf::Texture("../../res/images/idle_0.png"));
        block = new Core::Entity({200, 200}, {{0, 0}, {16, 16}}, 6,
                                 sf::Texture("../../res/images/castle-tileset.png", false,
                                             {{16, 16}, {16, 16}}));
        character->m_kineticState = Core::Entity::Dynamic;
        block->m_kineticState = Core::Entity::Dynamic;
    }

    TestLevelLayer::~TestLevelLayer()
    {
        delete character;
        delete block;
    }

    bool TestLevelLayer::OnEvent(const sf::Event& event)
    {
        block->OnEvent(event);
        character->OnEvent(event);
        return false;
    }

    void TestLevelLayer::OnUpdate(float dt)
    {
        block->OnUpdate(dt);
        character->OnUpdate(dt);
        Core::AABB(character, block);
    }

    void TestLevelLayer::OnRender(Core::Window& window)
    {
        sf::RenderWindow& renderWindow = window.GetRenderWindow();
        block->OnRender(renderWindow);
        character->OnRender(renderWindow);

        sf::VertexArray charbox(sf::PrimitiveType::Lines, 2);
        charbox[0].position = character->m_hitbox.topLeft;
        charbox[1].position = character->m_hitbox.bottomRight;

        renderWindow.draw(charbox);

        sf::VertexArray blockbox(sf::PrimitiveType::Lines, 2);
        blockbox[0].position = block->m_hitbox.topLeft;
        blockbox[1].position = block->m_hitbox.bottomRight;
        renderWindow.draw(blockbox);
    }
} // namespace Game