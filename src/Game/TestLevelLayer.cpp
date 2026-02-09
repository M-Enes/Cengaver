#include "Game/TestLevelLayer.hpp"
#include "Core/Physics.hpp"
#include "Core/Player.hpp"
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace Game
{
    TestLevelLayer::TestLevelLayer()
    {
        character = new Core::Player({100, 100}, {{10, 11}, {23, 25}}, 5,
                                     sf::Texture("../../res/images/idle_0.png"));
        block[0] = new Core::Entity({200, 200}, {{0, 0}, {16, 16}}, 5,
                                    sf::Texture("../../res/images/castle-tileset.png",
                                                false, {{16, 16}, {16, 16}}));
        block[1] = new Core::Entity({280, 280}, {{0, 0}, {16, 16}}, 5,
                                    sf::Texture("../../res/images/castle-tileset.png",
                                                false, {{16, 16}, {16, 16}}));
        block[2] = new Core::Entity({360, 360}, {{0, 0}, {16, 16}}, 5,
                                    sf::Texture("../../res/images/castle-tileset.png",
                                                false, {{16, 16}, {16, 16}}));
        block[3] = new Core::Entity({440, 440}, {{0, 0}, {16, 16}}, 5,
                                    sf::Texture("../../res/images/castle-tileset.png",
                                                false, {{16, 16}, {16, 16}}));
        block[4] = new Core::Entity({520, 520}, {{0, 0}, {16, 16}}, 5,
                                    sf::Texture("../../res/images/castle-tileset.png",
                                                false, {{16, 16}, {16, 16}}));
        block[5] = new Core::Entity({600, 600}, {{0, 0}, {16, 16}}, 5,
                                    sf::Texture("../../res/images/castle-tileset.png",
                                                false, {{16, 16}, {16, 16}}));
        character->m_kineticState = Core::Entity::Dynamic;
        // block->m_kineticState = Core::Entity::Dynamic;

        entities.push_back(character);
        for (int i = 0; i < 6; i++) entities.push_back(block[i]);
    }

    TestLevelLayer::~TestLevelLayer()
    {
        for (int i = 0; i < entities.size(); i++) { delete entities[i]; }
    }

    bool TestLevelLayer::OnEvent(const sf::Event& event)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F3)) debugMode = !debugMode;
        character->OnEvent(event);
        for (int i = 0; i < 6; i++) block[i]->OnEvent(event);
        return false;
    }

    void TestLevelLayer::OnUpdate(float dt)
    {
        for (int i = 0; i < 6; i++) block[i]->OnUpdate(dt);
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
        for (int i = 0; i < 6; i++) block[i]->OnRender(renderWindow);

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

            // sf::VertexArray blockbox(sf::PrimitiveType::Lines, 5);
            // blockbox[0].position = block->m_hitbox.topLeft;
            // blockbox[1].position = {block->m_hitbox.bottomRight.x,
            //                         block->m_hitbox.topLeft.y};
            // blockbox[2].position = block->m_hitbox.bottomRight;
            // blockbox[3].position = {block->m_hitbox.topLeft.x,
            //                         block->m_hitbox.bottomRight.y};
            // blockbox[4].position = block->m_hitbox.topLeft;

            // renderWindow.draw(blockbox);
        }
    }
} // namespace Game