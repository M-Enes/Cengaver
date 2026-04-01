#include "Game/States/RunState.hpp"
#include "Game/Player.hpp"
#include "Game/States/IdleState.hpp"
#include "Game/States/JumpState.hpp"
#include <iostream>
#include <memory>
#include <SFML/System/Vector2.hpp>

namespace Game
{
    void RunState::OnEnter(Player& player)
    {
        std::cout << "Entered Run State" << std::endl;
        player.goToAnimation("run");
    }
    void RunState::OnUpdate(Player& player) {}
    void RunState::OnExit(Player& player) {}
    std::unique_ptr<IMovementState> RunState::CheckTransition(Player& player)
    {
        if (player.m_velocity == sf::Vector2f{0, 0})
        {
            return std::make_unique<IdleState>();
        }

        if (player.m_velocity.y != 0) { return std::make_unique<JumpState>(); }

        return nullptr;
    }

} // namespace Game