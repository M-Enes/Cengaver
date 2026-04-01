#pragma once

#include "Game/IMovementState.hpp"
namespace Game
{

    class IdleState : public IMovementState
    {
      public:
        virtual ~IdleState() = default;
        virtual void OnEnter(Player& player);
        virtual void OnUpdate(Player& player);
        virtual void OnExit(Player& player);
        virtual std::unique_ptr<IMovementState> CheckTransition(Player& player);
    };

} // namespace Game