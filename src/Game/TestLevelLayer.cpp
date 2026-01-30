#include "Game/TestLevelLayer.hpp"
#include "Core/Player.hpp"

namespace Game
{
    TestLevelLayer::TestLevelLayer()
    {
        character = new Core::Player({500, 500}, "../../res/images/idle_0.png");
    }

    TestLevelLayer::~TestLevelLayer()
    {
        delete character;
    }

    bool TestLevelLayer::OnEvent(const sf::Event& event)
    {
        character->OnEvent(event);
        return false;
    }

    void TestLevelLayer::OnUpdate(float dt)
    {
        character->OnUpdate(dt);
    }

    void TestLevelLayer::OnRender(Core::Window& window)
    {
        sf::RenderWindow& renderWindow = window.GetRenderWindow();
        character->OnRender(renderWindow);
    }
} // namespace Game