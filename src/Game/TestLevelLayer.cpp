#include "Game/TestLevelLayer.hpp"
#include "Core/Entity.hpp"
#include "Core/log.hpp"
#include "Core/Physics.hpp"
#include "Game/Player.hpp"
#include <memory>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <utility>
#include <vector>

namespace Game
{
    TestLevelLayer::TestLevelLayer()
    {
        Core::logger.info("Test Level Layer constructing...");
        std::unique_ptr<Player> playerPtr = std::make_unique<Player>(
            sf::Vector2f{120, 100}, sf::Vector2<sf::Vector2f>{{13, 11}, {20, 25}}, 5,
            Core::Entity::Dynamic, sf::Texture("../../res/images/idle_0.png"),
            "../../res/images/animtest");

        character = playerPtr.get();
        entities.push_back(std::move(playerPtr));

        character->m_kineticState = Core::Entity::Dynamic;

        std::vector<std::unique_ptr<Core::Entity>> blockPtrs;

        blockPtrs.push_back(std::make_unique<Core::Entity>(
            sf::Vector2f{200, 520}, sf::Vector2<sf::Vector2f>{{0, 0}, {16, 16}}, 5,
            Core::Entity::Static,
            sf::Texture("../../res/images/castle-tileset.png", false,
                        sf::IntRect{{16, 16}, {16, 16}})));
        blockPtrs.push_back(std::make_unique<Core::Entity>(
            sf::Vector2f{280, 520}, sf::Vector2<sf::Vector2f>{{0, 0}, {16, 16}}, 5,
            Core::Entity::Static,
            sf::Texture("../../res/images/castle-tileset.png", false,
                        sf::IntRect{{16, 16}, {16, 16}})));
        blockPtrs.push_back(std::make_unique<Core::Entity>(
            sf::Vector2f{360, 520}, sf::Vector2<sf::Vector2f>{{0, 0}, {16, 16}}, 5,
            Core::Entity::Static,
            sf::Texture("../../res/images/castle-tileset.png", false,
                        sf::IntRect{{16, 16}, {16, 16}})));
        blockPtrs.push_back(std::make_unique<Core::Entity>(
            sf::Vector2f{440, 520}, sf::Vector2<sf::Vector2f>{{0, 0}, {16, 16}}, 5,
            Core::Entity::Static,
            sf::Texture("../../res/images/castle-tileset.png", false,
                        sf::IntRect{{16, 16}, {16, 16}})));
        blockPtrs.push_back(std::make_unique<Core::Entity>(
            sf::Vector2f{520, 520}, sf::Vector2<sf::Vector2f>{{0, 0}, {16, 16}}, 5,
            Core::Entity::Static,
            sf::Texture("../../res/images/castle-tileset.png", false,
                        sf::IntRect{{16, 16}, {16, 16}})));
        blockPtrs.push_back(std::make_unique<Core::Entity>(
            sf::Vector2f{600, 520}, sf::Vector2<sf::Vector2f>{{0, 0}, {16, 16}}, 5,
            Core::Entity::Static,
            sf::Texture("../../res/images/castle-tileset.png", false,
                        sf::IntRect{{16, 16}, {16, 16}})));
        blockPtrs.push_back(std::make_unique<Core::Entity>(
            sf::Vector2f{600, 440}, sf::Vector2<sf::Vector2f>{{0, 0}, {16, 16}}, 5,
            Core::Entity::Static,
            sf::Texture("../../res/images/castle-tileset.png", false,
                        sf::IntRect{{16, 16}, {16, 16}})));
        blockPtrs.push_back(std::make_unique<Core::Entity>(
            sf::Vector2f{200, 440}, sf::Vector2<sf::Vector2f>{{0, 0}, {16, 16}}, 5,
            Core::Entity::Static,
            sf::Texture("../../res/images/castle-tileset.png", false,
                        sf::IntRect{{16, 16}, {16, 16}})));
        blockPtrs.push_back(std::make_unique<Core::Entity>(
            sf::Vector2f{520, 280}, sf::Vector2<sf::Vector2f>{{0, 0}, {16, 16}}, 5,
            Core::Entity::Static,
            sf::Texture("../../res/images/castle-tileset.png", false,
                        sf::IntRect{{16, 16}, {16, 16}})));
        blockPtrs.push_back(std::make_unique<Core::Entity>(
            sf::Vector2f{440, 280}, sf::Vector2<sf::Vector2f>{{0, 0}, {16, 16}}, 5,
            Core::Entity::Static,
            sf::Texture("../../res/images/castle-tileset.png", false,
                        sf::IntRect{{16, 16}, {16, 16}})));

        for (int i = 0; i < blockPtrs.size(); i++)
        {
            blocks.push_back(blockPtrs[i].get());
            entities.push_back(std::move(blockPtrs[i]));
        }
        Core::logger.info("Test Level Layer constructed.");
    }

    TestLevelLayer::~TestLevelLayer() {}

    bool TestLevelLayer::OnEvent(const sf::Event& event)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F3)) debugMode = !debugMode;
        character->OnEvent(event);
        for (int i = 0; i < blocks.size(); i++) blocks[i]->OnEvent(event);
        return true;
    }

    void TestLevelLayer::OnUpdate(float dt)
    {
        for (int i = 0; i < blocks.size(); i++) blocks[i]->OnUpdate(dt);
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
        for (int i = 0; i < blocks.size(); i++) blocks[i]->OnRender(renderWindow);
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