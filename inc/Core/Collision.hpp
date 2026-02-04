#pragma once

#include "Core/Entity.hpp"

namespace Core
{
    // Axis-Aligned Bounding Box
    class AABB
    {
      public:
        static bool Check(Core::Entity *entity1, Core::Entity *entity2);
    };

    // Seperating Axis Theorem
    // class SAT
    // {
    //     static bool Check(Core::Entity& entity1, Core::Entity& entity2);
    // };
} // namespace Core