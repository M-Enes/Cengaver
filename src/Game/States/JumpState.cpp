#include "Game/States/JumpState.hpp"
#include "Game/Player.hpp"
#include "Game/States/IdleState.hpp"
#include "Game/States/RunState.hpp"
#include <iostream>

namespace Game
{
    void JumpState::OnEnter(Player& player)
    {
        std::cout << "Entered Jump State" << std::endl;
    }
    void JumpState::OnUpdate(Player& player) {}
    void JumpState::OnExit(Player& player) {}
    IMovementState *JumpState::CheckTransition(Player& player)
    {
        if (player.m_velocity == sf::Vector2f{0, 0}) { return new IdleState(); }

        if (player.m_velocity.y == 0) { return new RunState(); }

        return nullptr;
    }

} // namespace Game