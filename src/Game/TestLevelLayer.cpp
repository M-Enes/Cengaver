#include "Game/TestLevelLayer.hpp"
#include "Core/Physics.hpp"
#include "Core/Player.hpp"
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Window/Keyboard.hpp>

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
        // block->m_kineticState = Core::Entity::Dynamic;

        entities.push_back(character);
        entities.push_back(block);
    }

    TestLevelLayer::~TestLevelLayer()
    {
        delete character;
        delete block;
    }

    bool TestLevelLayer::OnEvent(const sf::Event& event)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F3)) debugMode = !debugMode;
        block->OnEvent(event);
        character->OnEvent(event);
        return false;
    }

    void TestLevelLayer::OnUpdate(float dt)
    {
        block->OnUpdate(dt);
        character->OnUpdate(dt);
        for (int i = 0; i < entities.size(); i++)
        {
            for (int j = i + 1; j < entities.size(); j++)
            {
                Core::AABB(entities[i], entities[j]);
            }
        }
    }

    void TestLevelLayer::OnRender(Core::Window& window)
    {
        sf::RenderWindow& renderWindow = window.GetRenderWindow();
        character->OnRender(renderWindow);
        block->OnRender(renderWindow);

        if (debugMode)
        {
            sf::VertexArray charbox(sf::PrimitiveType::LineStrip, 5);
            charbox[0].position = character->m_hitbox.topLeft;
            charbox[1].position = {character->m_hitbox.bottomRight.x,
                                   character->m_hitbox.topLeft.y};
            charbox[2].position = character->m_hitbox.bottomRight;
            charbox[3].position = {character->m_hitbox.topLeft.x,
                                   character->m_hitbox.bottomRight.y};
            charbox[4].position = character->m_hitbox.topLeft;

            renderWindow.draw(charbox);

            sf::VertexArray blockbox(sf::PrimitiveType::Lines, 5);
            blockbox[0].position = block->m_hitbox.topLeft;
            blockbox[1].position = {block->m_hitbox.bottomRight.x,
                                    block->m_hitbox.topLeft.y};
            blockbox[2].position = block->m_hitbox.bottomRight;
            blockbox[3].position = {block->m_hitbox.topLeft.x,
                                    block->m_hitbox.bottomRight.y};
            blockbox[4].position = block->m_hitbox.topLeft;

            renderWindow.draw(blockbox);
        }
    }
} // namespace Game