#include "Core/Collision.hpp"
#include <iostream>

namespace Core
{
    int a = 0;
    bool AABB::Check(Core::Entity *obj1, Core::Entity *obj2)
    {
        if ((obj1->m_hitbox.bottomRight.x > obj2->m_hitbox.topLeft.x) &
            (obj1->m_hitbox.topLeft.x < obj2->m_hitbox.bottomRight.x) &
            (obj1->m_hitbox.bottomRight.y > obj2->m_hitbox.topLeft.y) &
            (obj1->m_hitbox.topLeft.y < obj2->m_hitbox.bottomRight.y))
        {
            std::cout << "Collision " << a++ << " detected" << std::endl;

            return true;
        }
        else
        {
            return false;
        }
    }
} // namespace Core