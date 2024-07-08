#ifndef IMAGE_H
#define IMAGE_H
#include <string>
#include "Component.h"
#include "ImageManager.h"
#include "System.h"
#include <SDL_ttf.h>
#include <SDL.h>

namespace gui {
    class Image : public Component, public ImageManager
    {
    public:
        static Image* getInstance(const std::string& imageName);

        ~Image();
        void draw() const override;

    protected:
        Image(const std::string& imageName);

    private:
        Image(const Image&) = delete;
        const Image& operator =(const Image&) = delete;
    };
}
#endif
