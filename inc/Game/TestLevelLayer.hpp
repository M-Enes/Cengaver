#pragma once

#include "Core/Layer.hpp"

namespace Game
{
class TestLevelLayer : public Core::Layer
{
  public:
    TestLevelLayer();
    virtual ~TestLevelLayer();

    virtual bool OnEvent(const sf::Event& event) override;
    virtual void OnUpdate(float timeStep) override;
    virtual void OnRender(Core::Window& window) override;

  private:
    sf::Texture characterTexture;
    sf::Sprite characterSprite;
};
} // namespace Game