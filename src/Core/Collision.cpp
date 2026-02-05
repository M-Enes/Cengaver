#include "Core/Collision.hpp"
#include <iostream>

namespace Core
{
    int a = 0;
    bool AABB::Check(Core::Entity *obj1, Core::Entity *obj2)
    {
        if ((obj1->m_hitbox.y.x > obj2->m_hitbox.x.x) &
            (obj1->m_hitbox.x.x < obj2->m_hitbox.y.x) &
            (obj1->m_hitbox.y.y > obj2->m_hitbox.x.y) &
            (obj1->m_hitbox.x.y < obj2->m_hitbox.y.y))
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