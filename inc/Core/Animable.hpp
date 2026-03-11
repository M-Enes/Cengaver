#pragma once

#include <cstdint>
#include <SFML/Graphics/Texture.hpp>
#include <unordered_map>

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
        Animable(std::string animationsPath);
        ~Animable();

        void goToNextFrame();
        void goToAnimation(std::string name);
        sf::Texture *getCurrentFrame();

      private:
        uint8_t m_currentAnimationFrame = 0;
        std::string m_currentAnimationName;
        std::unordered_map<std::string, std::vector<sf::Texture *>> m_animations;
    };
} // namespace Core