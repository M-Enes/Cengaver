#include "Game/States/JumpState.hpp"
#include "Game/Player.hpp"
#include "Game/States/IdleState.hpp"
#include "Game/States/RunState.hpp"
#include <iostream>
#include <memory>

namespace Game
{
    void JumpState::OnEnter(Player& player)
    {
        std::cout << "Entered Jump State" << std::endl;
        player.GoToAnimation("jump");
    }
    void JumpState::OnUpdate(Player& player) {}
    void JumpState::OnExit(Player& player) {}
    std::unique_ptr<IMovementState> JumpState::CheckTransition(Player& player)
    {
        if (player.m_velocity == sf::Vector2f{0, 0})
        {
            return std::make_unique<IdleState>();
        }

        if (player.m_velocity.y == 0) { return std::make_unique<RunState>(); }

        return nullptr;
    }

} // namespace Game