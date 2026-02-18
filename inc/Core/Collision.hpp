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
        Core::Entity *m_obj1;
        Core::Entity *m_obj2;
        float m_distances[4];
        sf::Vector2f m_overlap = {0, 0};
        bool Check();
        void Effect();
    };

    // Seperating Axis Theorem
    // class SAT
    // {
    //     static bool Check(Core::Entity& entity1, Core::Entity& entity2);
    // };
} // namespace Core