#include "TextManager.h"
#include "System.h"

namespace gui {
	TextManager::TextManager(const std::string& text) : text(text)
	{
        TTF_Init();
        font = TTF_OpenFont((fontsAddress + fontName + ".ttf").c_str(), fontSize);
        createTexture();
	}
	TextManager::TextManager(const std::string& text, const std::string& fontName)
	{
        TTF_Init();
        font = TTF_OpenFont((fontsAddress + fontName + ".ttf").c_str(), fontSize);
        createTexture();
	}
	TextManager::TextManager(const std::string& text, const std::string& fontName, SDL_Color color)
	{
        TTF_Init();
        font = TTF_OpenFont((fontsAddress + fontName + ".ttf").c_str(), fontSize);
        createTexture();
	}

    void TextManager::createTexture()
    {
        SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
        texture = SDL_CreateTextureFromSurface(sys.getRenderer(), surface);
        SDL_FreeSurface(surface);
    }

	TextManager::~TextManager()
	{
		if (font != nullptr) TTF_CloseFont(font);
		TTF_Quit();
	}

    void TextManager::setText(const std::string& text)
    {
        this->text = text;
        createTexture();
    }

    const std::string& TextManager::getText()
    {
        return text;
    }

    void TextManager::setFont(TTF_Font* font)
    {
        this->font = font;
        createTexture();
    }

    const TTF_Font* TextManager::getFont()
    {
        return font;
    }

    void TextManager::setFontSize(const int newFontSize)
    {
        fontSize = newFontSize;
        createTexture();
    }

    const int& TextManager::getFontSize()
    {
        return fontSize;
    }

    void TextManager::setColor(const SDL_Color newColor)
    {
        color = newColor;
        createTexture();
    }

    const SDL_Color& TextManager::getColor()
    {
        return color;
    }
}

