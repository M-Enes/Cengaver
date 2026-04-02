#include "Game/TestLevelLayer.hpp"
#include "Core/AssetManager.hpp"
#include "Core/Entity.hpp"
#include "Core/GameContext.hpp"
#include "Core/log.hpp"
#include "Core/Physics.hpp"
#include "Game/Player.hpp"
#include <memory>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <utility>
#include <vector>

namespace Game
{
    TestLevelLayer::TestLevelLayer() {}

    void TestLevelLayer::OnAttach(Core::GameContext& context)
    {
        Core::logger.info("Test Level Layer attaching...");

        const sf::Texture *idleTexture =
            context.assetManager.GetTexture("../../res/images/idle_0.png");

        if (idleTexture == nullptr)
        {
            Core::logger.error(
                "Test Level Layer could attached: Character texture not found.");
            exit(1);
        }

        const sf::Texture *blockTexture =
            context.assetManager.GetTexture("../../res/images/castle-tileset.png");

        if (blockTexture == nullptr)
        {
            Core::logger.error(
                "Test Level Layer could not attached: Block texture not found.");
            exit(1);
        }

        std ::unique_ptr<Player> playerPtr = std::make_unique<Player>(
            context, sf::Vector2f{120, 100},
            sf::Vector2<sf::Vector2f>{{13, 11}, {20, 25}}, 5, Core::Entity::Dynamic,
            (sf::Texture&)*idleTexture, "../../res/images/animtest");

        character = playerPtr.get();
        entities.push_back(std::move(playerPtr));

        character->m_kineticState = Core::Entity::Dynamic;

        std::vector<sf::Vector2f> blockPositions = {
            {200, 520}, {280, 520}, {360, 520}, {440, 520}, {520, 520},
            {600, 520}, {600, 440}, {200, 440}, {520, 280}, {440, 280}};

        for (const sf::Vector2f& pos : blockPositions)
        {
            std::unique_ptr<Core::Entity> blockPtr = std::make_unique<Core::Entity>(
                context, pos, sf::Vector2<sf::Vector2f>{{0, 0}, {16, 16}}, 5,
                Core::Entity::Static, (sf::Texture&)*blockTexture);

            blockPtr->m_sprite.setTextureRect(sf::IntRect({{0, 0}, {16, 16}}));

            blocks.push_back(blockPtr.get());
            entities.push_back(std::move(blockPtr));
        }

        Core::logger.info("Test Level Layer attached.");
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