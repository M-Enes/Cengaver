#include "Core/AssetManager.hpp"
#include "Core/log.hpp"
#include <memory>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Exception.hpp>

namespace Core
{

    const sf::Texture *AssetManager::GetTexture(const std::string& filepath)
    {

        if (m_textures.find(filepath) != m_textures.end())
        {
            return m_textures[filepath].get();
        }

        try
        {
            std::unique_ptr<sf::Texture> texturePtr =
                std::make_unique<sf::Texture>(filepath);

            m_textures[filepath] = std::move(texturePtr);
            return m_textures[filepath].get();

        } catch (const sf::Exception& e)
        {
            logger.error("The texture from the file '" + filepath +
                         "' could not loaded. Exception: " + e.what());
            return nullptr;
        }
    }

} // namespace Core