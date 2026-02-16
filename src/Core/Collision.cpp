#include "Core/Collision.hpp"
#include "Core/Entity.hpp"
#include <iostream>
#include <SFML/System/Vector2.hpp>

namespace Core
{
    AABB::AABB(Core::Entity *object1, Core::Entity *object2)
        : m_obj1(object1), m_obj2(object2)
    {
        m_distances[0] = m_obj1->m_hitbox.bottomRight.x - m_obj2->m_hitbox.topLeft.x;
        m_distances[1] = m_obj2->m_hitbox.bottomRight.x - m_obj1->m_hitbox.topLeft.x;
        m_distances[2] = m_obj1->m_hitbox.bottomRight.y - m_obj2->m_hitbox.topLeft.y;
        m_distances[3] = m_obj2->m_hitbox.bottomRight.y - m_obj1->m_hitbox.topLeft.y;

        if (m_obj1 != m_obj2 && Check()) { Effect(); }
    }

    bool AABB::Check()
    {
        if (m_distances[0] > 0 && m_distances[1] > 0 && m_distances[2] > 0 &&
            m_distances[3] > 0)
        {
            // m_overlap = {min(m_distances[0], m_distances[1]),
            //              min(m_distances[2], m_distances[3])};
            return true;
        }
        else
        {
            return false;
        }
    }

    void AABB::Effect()
    {
        std::cout << "---\n"
                  << m_distances[0] << ", " << m_distances[1] << ", " << m_distances[2]
                  << ", " << m_distances[3] << std::endl;
        std::cout << "(" << m_obj1->m_hitbox.topLeft.x << ", "
                  << m_obj1->m_hitbox.topLeft.y << "), "
                  << "(" << m_obj1->m_hitbox.bottomRight.x << ", "
                  << m_obj1->m_hitbox.bottomRight.y << ")" << std::endl;
        std::cout << "(" << m_obj1->m_previousHitbox.topLeft.x << ", "
                  << m_obj1->m_previousHitbox.topLeft.y << "), "
                  << "(" << m_obj1->m_previousHitbox.bottomRight.x << ", "
                  << m_obj1->m_previousHitbox.bottomRight.y << ")" << std::endl;

        if (m_obj1->m_previousHitbox.bottomRight.x <= m_obj2->m_hitbox.topLeft.x)
        {
            std::cout << "Here dist[0]" << std::endl;
            m_overlap.x = m_distances[0];
            m_obj1->m_velocity.x = 0;
            m_obj1->m_acceleration.x = 0;
        }
        if (m_obj1->m_previousHitbox.topLeft.x >= m_obj2->m_hitbox.bottomRight.x)
        {
            std::cout << "Here dist[1]" << std::endl;
            m_overlap.x = m_distances[1];
            m_obj1->m_velocity.x = 0;
            m_obj1->m_acceleration.x = 0;
        }
        if (m_obj1->m_previousHitbox.bottomRight.y <= m_obj2->m_hitbox.topLeft.y)
        {
            std::cout << "Here dist[2]" << std::endl;
            m_overlap.y = -m_distances[2];
            m_obj1->m_velocity.y = 0;
            m_obj1->m_acceleration.y = 0;
        }
        if (m_obj1->m_previousHitbox.topLeft.y >= m_obj2->m_hitbox.bottomRight.y)
        {
            std::cout << "Here dist[3]" << std::endl;
            m_overlap.y = -m_distances[3];
            m_obj1->m_velocity.y = 0;
            m_obj1->m_acceleration.y = 0;
        }

        std::cout << m_overlap.x << ", " << m_overlap.y << std::endl;

        if (m_obj1->m_kineticState == Entity::Dynamic &&
            m_obj2->m_kineticState == Entity::Dynamic)
        {
            m_obj1->Move({(-m_overlap.x) / 2, (-m_overlap.y) / 2});
            m_obj2->Move({(m_overlap.x) / 2, (m_overlap.y) / 2});
        }
        else if (m_obj1->m_kineticState == Entity::Dynamic)
        {
            m_obj1->Move({-m_overlap.x, -m_overlap.y});
        }
        else if (m_obj2->m_kineticState == Entity::Dynamic)
        {
            m_obj2->Move({-m_overlap.x, -m_overlap.y});
        }
        m_obj1->m_previousHitbox = m_obj1->m_hitbox;
        std::cout << "(" << m_obj1->m_hitbox.topLeft.x << ", "
                  << m_obj1->m_hitbox.topLeft.y << "), "
                  << "(" << m_obj1->m_hitbox.bottomRight.x << ", "
                  << m_obj1->m_hitbox.bottomRight.y << ")" << std::endl;
    }
} // namespace Core