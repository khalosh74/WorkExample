#include "ImageManager.h"
#include "System.h"


namespace gui {
    ImageManager::ImageManager(const std::string& fn) : imageName(fn) {
        createTexture();
    }
    ImageManager::~ImageManager() {
    }

    const std::string& ImageManager::getImageName()
    {
        return imageName;
    }

    void ImageManager::setImageName(const std::string& newFilename)
    {
        imageName = newFilename;
        createTexture();
    }

    void ImageManager::createTexture()
    {
        SDL_Surface* surface = IMG_Load((imagesAddress + imageName).c_str());
        texture = SDL_CreateTextureFromSurface(sys.getRenderer(), surface);
        SDL_FreeSurface(surface);
    }

    ImageManager* ImageManager::getInstance(const std::string& text) {
        return new ImageManager(text);
    }

}