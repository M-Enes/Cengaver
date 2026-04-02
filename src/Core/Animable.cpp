#include "Core/Animable.hpp"
#include "Core/AssetManager.hpp"
#include "Core/GameContext.hpp"
#include <filesystem>
#include <SFML/Graphics/Texture.hpp>
#include <string>

namespace Core
{
    Animable::Animable(GameContext& context, std::string animationsPath)
    {
        for (const auto& entry : std::filesystem::directory_iterator(animationsPath))
        {
            std::string filename = entry.path().filename().string();
            std::string animationName = filename.substr(0, filename.find_last_of('_'));
            sf::Texture *texture =
                (sf::Texture *)context.assetManager.GetTexture(entry.path().string());
            m_animations[animationName].push_back(texture);
        }

        GoToAnimation(m_animations.begin()->first);
    }
    Animable::~Animable() {}

    void Animable::GoToNextFrame()
    {
        m_currentAnimationFrame =
            (m_currentAnimationFrame + 1) % m_animations[m_currentAnimationName].size();
    }
    void Animable::GoToAnimation(std::string name)
    {
        if (m_animations.find(name) == m_animations.end())
        {
            // Animation does not exist
            return;
        }

        m_currentAnimationName = name;
        m_currentAnimationFrame = 0;
    }
    sf::Texture *Animable::GetCurrentFrame()
    {
        return m_animations[m_currentAnimationName][m_currentAnimationFrame];
    }
} // namespace Core