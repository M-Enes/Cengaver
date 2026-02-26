#pragma once

namespace Game
{
    class Player;

    class IMovementState
    {
        virtual ~IMovementState() = default;
        virtual void OnEnter(Player& player) = 0;
        virtual void OnUpdate(Player& player) = 0;
        virtual void OnExit(Player& player) = 0;
        virtual void CheckTransition(Player& player) = 0;
    };

} // namespace Game