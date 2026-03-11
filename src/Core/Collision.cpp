#include "Core/Collision.hpp"

namespace Core
{
    namespace Physics
    {

        static bool Check(Entity& entity1, Entity& entity2)
        {
            float& entity1Right = entity1.m_hitbox.bottomRight.x;
            float& entity1Left = entity1.m_hitbox.topLeft.x;
            float& entity1Top = entity1.m_hitbox.topLeft.y;
            float& entity1Bottom = entity1.m_hitbox.bottomRight.y;

            float& entity2Right = entity2.m_hitbox.bottomRight.x;
            float& entity2Left = entity2.m_hitbox.topLeft.x;
            float& entity2Top = entity2.m_hitbox.topLeft.y;
            float& entity2Bottom = entity2.m_hitbox.bottomRight.y;

            if (entity1Right > entity2Left && entity2Right > entity1Left &&
                entity1Bottom > entity2Top && entity2Bottom > entity1Top)
            {
                return true;
            }

            return false;
        }

        void ResolveX(Entity& entity1, Entity& entity2)
        {

            if (Check(entity1, entity2))
            {
                if (entity1.m_kineticState == Entity::KineticState::Static &&
                    entity2.m_kineticState == Entity::KineticState::Static)
                {
                    // log the collision
                }
                else if (entity1.m_kineticState == Entity::KineticState::Dynamic &&
                         entity2.m_kineticState == Entity::KineticState::Dynamic)
                {
                    // do nothing for now
                }
                else
                {
                    Entity *dynamicEntity;
                    Entity *staticEntity;

                    if (entity1.m_kineticState == Entity::KineticState::Dynamic)
                    {
                        dynamicEntity = &entity1;
                        staticEntity = &entity2;
                    }
                    else
                    {
                        dynamicEntity = &entity2;
                        staticEntity = &entity1;
                    }

                    // dynamic comes from left
                    float leftOverlap = dynamicEntity->m_hitbox.bottomRight.x -
                                        staticEntity->m_hitbox.topLeft.x;

                    // dynamic comes from right
                    float rightOverlap = staticEntity->m_hitbox.bottomRight.x -
                                         dynamicEntity->m_hitbox.topLeft.x;

                    if (leftOverlap < rightOverlap)
                    {
                        dynamicEntity->Move({-leftOverlap, 0});
                    }
                    else
                    {
                        dynamicEntity->Move({rightOverlap, 0});
                    }

                    dynamicEntity->m_velocity.x = 0;
                    dynamicEntity->m_acceleration.x = 0;
                }
            }
        }

        void ResolveY(Entity& entity1, Entity& entity2)
        {

            if (Check(entity1, entity2))
            {
                if (entity1.m_kineticState == Entity::KineticState::Static &&
                    entity2.m_kineticState == Entity::KineticState::Static)
                {
                    // log the collision
                }
                else if (entity1.m_kineticState == Entity::KineticState::Dynamic &&
                         entity2.m_kineticState == Entity::KineticState::Dynamic)
                {
                    // do nothing for now
                }
                else
                {
                    Entity *dynamicEntity;
                    Entity *staticEntity;

                    if (entity1.m_kineticState == Entity::KineticState::Dynamic)
                    {
                        dynamicEntity = &entity1;
                        staticEntity = &entity2;
                    }
                    else
                    {
                        dynamicEntity = &entity2;
                        staticEntity = &entity1;
                    }

                    // dynamic comes from top
                    float floorOverlap = dynamicEntity->m_hitbox.bottomRight.y -
                                         staticEntity->m_hitbox.topLeft.y;

                    // dynamic comes from bottom
                    float ceilingOverlap = staticEntity->m_hitbox.bottomRight.y -
                                           dynamicEntity->m_hitbox.topLeft.y;

                    if (floorOverlap < ceilingOverlap)
                    {
                        dynamicEntity->Move({0, -floorOverlap});
                        dynamicEntity->m_isGrounded = true;
                    }
                    else
                    {
                        dynamicEntity->Move({0, ceilingOverlap});
                    }

                    dynamicEntity->m_velocity.y = 0;
                    dynamicEntity->m_acceleration.y = 0;
                }
            }
        }
    } // namespace Physics
} // namespace Core