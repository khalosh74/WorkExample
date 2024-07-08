#include "TextureManager.h"
#include "System.h"


namespace gui {

    TextureManager::~TextureManager() {
        SDL_DestroyTexture(texture);
    }

    const SDL_Texture* TextureManager::getTexture() {
        return texture;
    }
}