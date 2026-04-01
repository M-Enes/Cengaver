#include "Game/States/IdleState.hpp"
#include "Game/IMovementState.hpp"
#include "Game/Player.hpp"
#include "Game/States/JumpState.hpp"
#include "Game/States/RunState.hpp"
#include <iostream>
#include <memory>
#include <SFML/System/Vector2.hpp>

namespace Game
{
    void IdleState::OnEnter(Player& player)
    {
        std::cout << "Entered Idle State" << std::endl;
        player.GoToAnimation("idle");
    }
    void IdleState::OnUpdate(Player& player) {}
    void IdleState::OnExit(Player& player) {}
    std::unique_ptr<IMovementState> IdleState::CheckTransition(Player& player)
    {
        if (player.m_velocity.y != 0) { return std::make_unique<JumpState>(); }

        if (player.m_velocity != sf::Vector2f{0, 0})
        {
            return std::make_unique<RunState>();
        }

        return nullptr;
    }

} // namespace Game