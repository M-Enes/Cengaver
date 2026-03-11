#pragma once

#include "Core/Entity.hpp"

namespace Core
{
    namespace Physics
    {
        void ResolveX(Core::Entity& entity1, Core::Entity& entity2);
        void ResolveY(Core::Entity& entity1, Core::Entity& entity2);
    } // namespace Physics
} // namespace Core