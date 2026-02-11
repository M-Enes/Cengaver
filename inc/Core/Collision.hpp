#pragma once

#include "Core/Entity.hpp"

namespace Core
{
    // Axis-Aligned Bounding Box
    class AABB
    {
      public:
        AABB(Core::Entity *object1, Core::Entity *object2);

      private:
        bool Check(float distances[4]);
        void Effect(Core::Entity *obj1, Core::Entity *obj2);
    };

    // Seperating Axis Theorem
    // class SAT
    // {
    //     static bool Check(Core::Entity& entity1, Core::Entity& entity2);
    // };
} // namespace Core