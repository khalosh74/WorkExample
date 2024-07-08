#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SDL.h>
#include <string>

namespace gui {

    class TextureManager {
    public:
        virtual ~TextureManager();
        const SDL_Texture* getTexture();
    protected:
        virtual void createTexture() = 0;
        SDL_Texture* texture = nullptr;
        std::string imagesAddress = "../../resources/images/";
        std::string fontsAddress = "C:/Users/Admin/Downloads/GameEngine/GameEngine/resources/fonts/";
    };

}

#endif // TEXTURE_MANAGER_H