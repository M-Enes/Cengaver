#pragma once

#include "GameContext.hpp"
#include <cstdint>
#include <SFML/Graphics/Texture.hpp>
#include <unordered_map>
#include <vector>

namespace Core
{
    /*Works with the file structure like:

    idle_0.png

    idle_1.png

    walk_0.png
    */
    class Animable
    {
      public:
        Animable(GameContext& context, std::string animationsPath);
        ~Animable();

        void GoToNextFrame();
        void GoToAnimation(std::string name);
        sf::Texture *GetCurrentFrame();

      private:
        uint8_t m_currentAnimationFrame = 0;
        std::string m_currentAnimationName;
        std::unordered_map<std::string, std::vector<sf::Texture *>> m_animations;
    };
} // namespace Core