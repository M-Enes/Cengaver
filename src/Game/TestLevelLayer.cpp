#include "Game/TestLevelLayer.hpp"
#include "Core/Window.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

namespace Game
{
TestLevelLayer::TestLevelLayer()
    : characterTexture("../../res/images/idle_0.png"), characterSprite(characterTexture)
{
    characterSprite.setPosition({500.0f, 500.0f});
}
TestLevelLayer::~TestLevelLayer() {}

bool TestLevelLayer::OnEvent(const sf::Event& event)
{
    return false;
}

void TestLevelLayer::OnUpdate(float timeStep) {}

void TestLevelLayer::OnRender(Core::Window& window)
{
    sf::RenderWindow& renderWindow = window.GetRenderWindow();
    renderWindow.draw(characterSprite);
}
} // namespace Game