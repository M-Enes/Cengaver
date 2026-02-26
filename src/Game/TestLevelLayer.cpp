#include "Game/TestLevelLayer.hpp"
#include "Core/Entity.hpp"
#include "Core/Physics.hpp"
#include <SFML/Window/Keyboard.hpp>

namespace Game
{
    TestLevelLayer::TestLevelLayer()
    {
        character =
            new Game::Player({120, 100}, {{13, 11}, {20, 25}}, 5, Core::Entity::Dynamic,
                             sf::Texture("../../res/images/idle_0.png"));
        block[0] =
            new Core::Entity({200, 520}, {{0, 0}, {16, 16}}, 5, Core::Entity::Static,
                             sf::Texture("../../res/images/castle-tileset.png", false,
                                         {{16, 16}, {16, 16}}));
        block[1] =
            new Core::Entity({280, 520}, {{0, 0}, {16, 16}}, 5, Core::Entity::Static,
                             sf::Texture("../../res/images/castle-tileset.png", false,
                                         {{16, 16}, {16, 16}}));
        block[2] =
            new Core::Entity({360, 520}, {{0, 0}, {16, 16}}, 5, Core::Entity::Static,
                             sf::Texture("../../res/images/castle-tileset.png", false,
                                         {{16, 16}, {16, 16}}));
        block[3] =
            new Core::Entity({440, 520}, {{0, 0}, {16, 16}}, 5, Core::Entity::Static,
                             sf::Texture("../../res/images/castle-tileset.png", false,
                                         {{16, 16}, {16, 16}}));
        block[4] =
            new Core::Entity({520, 520}, {{0, 0}, {16, 16}}, 5, Core::Entity::Static,
                             sf::Texture("../../res/images/castle-tileset.png", false,
                                         {{16, 16}, {16, 16}}));
        block[5] =
            new Core::Entity({600, 520}, {{0, 0}, {16, 16}}, 5, Core::Entity::Static,
                             sf::Texture("../../res/images/castle-tileset.png", false,
                                         {{16, 16}, {16, 16}}));
        block[6] =
            new Core::Entity({600, 440}, {{0, 0}, {16, 16}}, 5, Core::Entity::Static,
                             sf::Texture("../../res/images/castle-tileset.png", false,
                                         {{16, 16}, {16, 16}}));
        block[7] =
            new Core::Entity({200, 440}, {{0, 0}, {16, 16}}, 5, Core::Entity::Static,
                             sf::Texture("../../res/images/castle-tileset.png", false,
                                         {{16, 16}, {16, 16}}));
        block[8] =
            new Core::Entity({520, 280}, {{0, 0}, {16, 16}}, 5, Core::Entity::Static,
                             sf::Texture("../../res/images/castle-tileset.png", false,
                                         {{16, 16}, {16, 16}}));
        block[9] =
            new Core::Entity({440, 280}, {{0, 0}, {16, 16}}, 5, Core::Entity::Static,
                             sf::Texture("../../res/images/castle-tileset.png", false,
                                         {{16, 16}, {16, 16}}));
        character->m_kineticState = Core::Entity::Dynamic;

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
        return true;
    }

    void TestLevelLayer::OnUpdate(float dt)
    {
        for (int i = 0; i < blockCount; i++) block[i]->OnUpdate(dt);
        character->OnUpdate(dt);
        character->Move({character->m_velocity.x * dt, 0});
        for (int i = 1; i < entities.size(); i++)
        {
            Core::Physics::ResolveX(*character, *(entities[i]));
        }
        character->m_isGrounded = false;
        character->Move({0, character->m_velocity.y * dt});
        for (int i = 1; i < entities.size(); i++)
        {
            Core::Physics::ResolveY(*character, *(entities[i]));
        }
    }

    void TestLevelLayer::OnRender(Core::Window& window)
    {
        sf::RenderWindow& renderWindow = window.GetRenderWindow();
        for (int i = 0; i < blockCount; i++) block[i]->OnRender(renderWindow);
        character->OnRender(renderWindow);

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