#include "Game/States/RunState.hpp"
#include "Game/Player.hpp"
#include "Game/States/IdleState.hpp"
#include "Game/States/JumpState.hpp"
#include <iostream>
#include <SFML/System/Vector2.hpp>

namespace Game
{
    void RunState::OnEnter(Player& player)
    {
        std::cout << "Entered Run State" << std::endl;
    }
    void RunState::OnUpdate(Player& player) {}
    void RunState::OnExit(Player& player) {}
    IMovementState *RunState::CheckTransition(Player& player)
    {
        if (player.m_velocity == sf::Vector2f{0, 0}) { return new IdleState(); }

        if (player.m_velocity.y != 0) { return new JumpState(); }

        return nullptr;
    }

} // namespace Game