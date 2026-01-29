#pragma once

#include <SFML/Window/Event.hpp>
namespace Core
{
class Layer
{
  public:
    virtual ~Layer() = default;

    virtual bool OnEvent(const sf::Event& event)
    {
        return false;
    };

    virtual void OnUpdate(float timeStep) {};
    virtual void OnRender() {};

  private:
};
} // namespace Core