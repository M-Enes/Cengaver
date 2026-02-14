#include "Core/Collision.hpp"
#include "Core/Entity.hpp"
#include <iostream>
#include <SFML/System/Vector2.hpp>

namespace Core
{
    int a = 0;

    AABB::AABB(Core::Entity *obj1, Core::Entity *obj2)
    {
        float distances[4] = {obj1->m_hitbox.bottomRight.x - obj2->m_hitbox.topLeft.x,
                              obj2->m_hitbox.bottomRight.x - obj1->m_hitbox.topLeft.x,
                              obj1->m_hitbox.bottomRight.y - obj2->m_hitbox.topLeft.y,
                              obj2->m_hitbox.bottomRight.y - obj1->m_hitbox.topLeft.y};

        if (obj1 != obj2 & Check(distances)) { Effect(obj1, obj2); }
    }

    bool AABB::Check(float distances[4])
    {
        // std::cout << distances[0] << ", " << distances[1] << ", " << distances[2] << ",
        // "
        //           << distances[3] << "\n";
        if (distances[0] > 0 & distances[1] > 0 & distances[2] > 0 & distances[3] > 0)
        {
            // std::cout << "Collision " << a++ << " detected" << "\n";
            return true;
        }
        else
        {
            return false;
        }
    }

    void AABB::Effect(Core::Entity *obj1, Core::Entity *obj2)
    {
        sf::Vector2f overlap = {0, 0};

        if (obj1->m_velocity.x != 0)
        {
            if (obj1->m_velocity.x > 0)
            {
                overlap.x = obj1->m_hitbox.bottomRight.x - obj2->m_hitbox.topLeft.x;
            }
            else if (obj1->m_velocity.x < 0)
            {
                overlap.x = obj1->m_hitbox.topLeft.x - obj2->m_hitbox.bottomRight.x;
            }
        }
        else if (obj1->m_velocity.y != 0)
        {
            if (obj1->m_velocity.y > 0)
            {
                overlap.y = obj1->m_hitbox.bottomRight.y - obj2->m_hitbox.topLeft.y;
            }
            else if (obj1->m_velocity.y < 0)
            {
                overlap.y = obj1->m_hitbox.topLeft.y - obj2->m_hitbox.bottomRight.y;
            }
        }

        if (obj1->m_kineticState == Entity::Dynamic &
            obj2->m_kineticState == Entity::Dynamic)
        {
            obj1->Move({(-overlap.x) / 2, (-overlap.y) / 2});
            obj2->Move({(overlap.x) / 2, (overlap.y) / 2});
        }
        else if (obj1->m_kineticState == Entity::Dynamic)
        {
            obj1->Move({-overlap.x, -overlap.y});
        }
        else if (obj2->m_kineticState == Entity::Dynamic)
        {
            obj2->Move({-overlap.x, -overlap.y});
        }

        if (obj1->m_hitbox.bottomRight.x <= obj2->m_hitbox.topLeft.x |
            obj1->m_hitbox.topLeft.x >= obj2->m_hitbox.bottomRight.x)
        {
            obj1->m_velocity.x = 0;
        }
        if (obj1->m_hitbox.bottomRight.y <= obj2->m_hitbox.topLeft.y |
            obj1->m_hitbox.topLeft.y >= obj2->m_hitbox.bottomRight.y)
        {
            obj1->m_velocity.y = 0;
        }
    }
} // namespace Core