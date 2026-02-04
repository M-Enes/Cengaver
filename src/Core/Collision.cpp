#include "Core/Collision.hpp"
#include "Core/log.hpp"

namespace Core
{
    bool AABB::Check(Core::Entity *obj1, Core::Entity *obj2)
    {
        if (obj1->m_hitbox.y.x > obj2->m_hitbox.x.x &
            obj1->m_hitbox.x.x<obj2->m_hitbox.y.x & obj1->m_hitbox.y.y> obj2->m_hitbox.x
                .y &
            obj1->m_hitbox.x.y < obj2->m_hitbox.y.y)
        {
            logger.level = Log::Debug;
            logger.debug("Collision detected");

            return true;
        }
        else
        {
            return false;
        }
    }
} // namespace Core