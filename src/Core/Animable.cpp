#include "Core/Animable.hpp"
#include <filesystem>
#include <SFML/Graphics/Texture.hpp>
#include <string>

namespace Core
{
    Animable::Animable(std::string animationsPath)
    {
        for (const auto& entry : std::filesystem::directory_iterator(animationsPath))
        {
            std::string filename = entry.path().filename().string();
            std::string animationName = filename.substr(0, filename.find_last_of('_'));
            sf::Texture *texture = new sf::Texture(entry.path());
            m_animations[animationName].push_back(texture);
        }

        goToAnimation(m_animations.begin()->first);
    }
    Animable::~Animable()
    {
        for (auto it = m_animations.begin(); it != m_animations.end(); it++)
        {
            auto& vector = it->second;
            for (int i = 0; i < vector.size(); i++) { delete vector[i]; }
        }
    }

    void Animable::goToNextFrame()
    {
        m_currentAnimationFrame =
            (m_currentAnimationFrame + 1) % m_animations[m_currentAnimationName].size();
    }
    void Animable::goToAnimation(std::string name)
    {
        if (m_animations.find(name) == m_animations.end())
        {
            // Animation does not exist
            return;
        }

        m_currentAnimationName = name;
        m_currentAnimationFrame = 0;
    }
    sf::Texture *Animable::getCurrentFrame()
    {
        return m_animations[m_currentAnimationName][m_currentAnimationFrame];
    }
} // namespace Core