#include "Image.h"
namespace gui {
    Image::Image(const std::string& imageName) : Component(), ImageManager(imageName)
    {
    }

    Image* Image::getInstance(const std::string& imageName)
    {
        return new Image(imageName);
    }
    Image::~Image()
    {
    }

    void Image::draw() const {
        // Draw button border
        //SDL_SetRenderDrawColor(sys.getRenderer(), 50, 0, 0, 255);
        SDL_Rect r = { position.x, position.y, size.w, size.h };
        SDL_RenderDrawRect(sys.getRenderer(), &r);
        // Draw the button texture
        SDL_RenderCopy(sys.getRenderer(), texture, nullptr, &r);

        // Draw label
        //label->draw();
    }
}