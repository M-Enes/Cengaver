#pragma once

#include <memory>

namespace Game
{
    class Player;

    class IMovementState
    {
      public:
        virtual ~IMovementState() = default;
        virtual void OnEnter(Player& player) = 0;
        virtual void OnUpdate(Player& player) = 0;
        virtual void OnExit(Player& player) = 0;
        /**
         * Checks for any required transition.
         * If found any, then creates an object of target IMovementState derived type
         * and returns address of it. Otherwise, returns nullptr.
         */
        virtual std::unique_ptr<IMovementState> CheckTransition(Player& player) = 0;
    };

} // namespace Game