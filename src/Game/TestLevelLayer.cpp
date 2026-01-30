#include "Game/TestLevelLayer.hpp"
#include "Core/Entity.hpp"

namespace Game
{
    TestLevelLayer::TestLevelLayer()
    {
        character = new Core::Entity({500, 500}, "../../res/images/idle_0.png");
    }

    TestLevelLayer::~TestLevelLayer()
    {
        delete character;
    }

    bool TestLevelLayer::OnEvent(const sf::Event& event)
    {
        return false;
    }

    void TestLevelLayer::OnUpdate(float timeStep) {}

    void TestLevelLayer::OnRender(Core::Window& window)
    {
        sf::RenderWindow& renderWindow = window.GetRenderWindow();
        character->OnRender(renderWindow);
    }
} // namespace Game