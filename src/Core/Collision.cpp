#include "Core/Collision.hpp"

namespace Core
{
    AABB::AABB(Core::Entity *object1, Core::Entity *object2)
        : m_obj1(object1), m_obj2(object2)
    {
        m_distances[0] = m_obj1->m_hitbox.bottomRight.x - m_obj2->m_hitbox.topLeft.x;
        m_distances[1] = m_obj2->m_hitbox.bottomRight.x - m_obj1->m_hitbox.topLeft.x;
        m_distances[2] = m_obj1->m_hitbox.bottomRight.y - m_obj2->m_hitbox.topLeft.y;
        m_distances[3] = m_obj2->m_hitbox.bottomRight.y - m_obj1->m_hitbox.topLeft.y;

        if (m_obj1 != m_obj2 && Check())
        {
            Effect();
        }
    }

    bool AABB::Check()
    {
        if (m_distances[0] > 0 && m_distances[1] > 0 && m_distances[2] > 0 &&
            m_distances[3] > 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void AABB::Effect()
    {
        m_obj1->m_isGrounded = false;

        if (m_obj1->m_previousHitbox.bottomRight.y <= m_obj2->m_hitbox.topLeft.y)
        {
            m_overlap.y = m_distances[2];
            m_obj1->m_velocity.y = 0;
            m_obj1->m_acceleration.y = 0;
            m_obj1->m_isGrounded = true;
        }
        else if (m_obj1->m_previousHitbox.topLeft.y >= m_obj2->m_hitbox.bottomRight.y)
        {
            m_overlap.y = -m_distances[3];
            m_obj1->m_velocity.y = 0;
            m_obj1->m_acceleration.y = 0;
        }
        else if (m_obj1->m_previousHitbox.bottomRight.x <= m_obj2->m_hitbox.topLeft.x)
        {
            m_overlap.x = m_distances[0];
            m_obj1->m_velocity.x = 0;
            m_obj1->m_acceleration.x = 0;
        }
        else if (m_obj1->m_previousHitbox.topLeft.x >= m_obj2->m_hitbox.bottomRight.x)
        {
            m_overlap.x = -m_distances[1];
            m_obj1->m_velocity.x = 0;
            m_obj1->m_acceleration.x = 0;
        }

        m_obj1->Move({-m_overlap.x, -m_overlap.y});
    }
} // namespace Core