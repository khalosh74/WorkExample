#ifndef TEXT_MANAGER_H
#define TEXT_MANAGER_H

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include "TextureManager.h"

namespace gui {

    class TextManager : public TextureManager{
    public:
        virtual ~TextManager();

        const TTF_Font* getFont();
        virtual void setFont(TTF_Font* font);

        const std::string& getText();
        virtual void setText(const std::string& newText);

        const SDL_Color& getColor();
        void setColor(const SDL_Color newColor);

        void setFontSize(const int newFontSize);
        const int& getFontSize();

    protected:
        TextManager(const std::string& text);
        TextManager(const std::string& text, const std::string& fontName);
        TextManager(const std::string& text, const std::string& fontName, SDL_Color color);

        TTF_Font* font;
        std::string fontName = "arial";
        int fontSize = 36;
        std::string text;
        SDL_Color color = { 0,0,0,255 };
    private:
        TextManager(const TextManager&) = delete;
        const TextManager& operator=(const TextManager&) = delete;
        void createTexture() override;

    };

}

#endif // TEXT_MANAGER_H