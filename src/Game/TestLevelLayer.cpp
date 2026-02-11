#include "Game/TestLevelLayer.hpp"
#include "Core/Entity.hpp"
#include "Core/Physics.hpp"
#include "Core/Player.hpp"
#include <iostream>
#include <SFML/Graphics/PrimitiveType.hpp>
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
        for (int i = 0; i < blockCount; i++)
        {
            block[i]->m_kineticState = Core::Entity::Static;
        }

        entities.push_back(character);
        for (int i = 0; i < blockCount; i++) entities.push_back(block[i]);
    }

    TestLevelLayer::~TestLevelLayer()
    {
        for (int i = 0; i < entities.size(); i++) { delete entities[i]; }
    }

    bool TestLevelLayer::OnEvent(const sf::Event& event)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F3)) debugMode = !debugMode;
        character->OnEvent(event);
        for (int i = 0; i < blockCount; i++) block[i]->OnEvent(event);
        return false;
    }

    void TestLevelLayer::OnUpdate(float dt)
    {
        for (int i = 0; i < blockCount; i++) block[i]->OnUpdate(dt);
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
        for (int i = 0; i < blockCount; i++) block[i]->OnRender(renderWindow);

        if (debugMode)
        {
            std::vector<sf::VertexArray> entityHitboxes;
            for (int i = 0; i < entities.size(); i++)
            {
                entityHitboxes.emplace_back(sf::PrimitiveType::LineStrip, 5);
                entityHitboxes[i][0].position = entities[i]->m_hitbox.topLeft;
                entityHitboxes[i][1].position = {entities[i]->m_hitbox.bottomRight.x,
                                                 entities[i]->m_hitbox.topLeft.y};
                entityHitboxes[i][2].position = entities[i]->m_hitbox.bottomRight;
                entityHitboxes[i][3].position = {entities[i]->m_hitbox.topLeft.x,
                                                 entities[i]->m_hitbox.bottomRight.y};
                entityHitboxes[i][4].position = entities[i]->m_hitbox.topLeft;
                renderWindow.draw(entityHitboxes[i]);
            }
        }
    }
} // namespace Game