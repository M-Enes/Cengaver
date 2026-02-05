#include "Game/TestLevelLayer.hpp"
#include "Core/Physics.hpp"
#include "Core/Player.hpp"
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