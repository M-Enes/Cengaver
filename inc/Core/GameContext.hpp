#pragma once

namespace Core
{

    class Window;
    class AssetManager;

    struct GameContext
    {
        Window& window;
        AssetManager& assetManager;

        GameContext(Window& window, AssetManager& assetManager)
            : window(window), assetManager(assetManager)
        {}
    };

} // namespace Core