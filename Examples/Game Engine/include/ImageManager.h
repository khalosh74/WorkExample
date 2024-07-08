#ifndef IMAGE_MANAGER_H
#define IMAGE_MANAGER_H

#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "TextureManager.h"

namespace gui {

    class ImageManager : public TextureManager {
    public:
        static ImageManager* getInstance(const std::string& imageName);
        virtual ~ImageManager();

        const std::string& getImageName();
        virtual void setImageName(const std::string& newImageName);

    protected:
        ImageManager(const std::string& imageName);
    private:
        ImageManager(const ImageManager&) = delete;
        const ImageManager& operator=(const ImageManager&) = delete;
        void createTexture() override;

        std::string imageName;
    };

}

#endif // IMAGE_MANAGER_H