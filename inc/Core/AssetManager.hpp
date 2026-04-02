#pragma once

#include <memory>
#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <unordered_map>

namespace Core
{

    class AssetManager
    {
      public:
        const sf::Texture *GetTexture(const std::string& filepath);

      private:
        std::unordered_map<std::string, std::unique_ptr<sf::Texture>> m_textures;
    };
} // namespace Core