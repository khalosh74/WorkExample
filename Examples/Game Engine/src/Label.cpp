#include "Label.h"

namespace gui {
    Label::Label(const std::string& text) : Component(), TextManager(text)
    {
        resize();
    }
    Label::Label(const std::string& text, const std::string& fontName)  : Component(), TextManager(text, fontName)
    {
        resize();
    }
    Label::Label(const std::string& text, const std::string& fontName, SDL_Color color) : Component(), TextManager(text, fontName, color)
    {
        resize();
        //setTexture(TextureManager::getTextInstance(font, text, color)->getTexture());
    }

    void Label::resize() {
        int width, height;
        TTF_SizeText(font, text.c_str(), &width, &height);
        setSize(width, height);
    }

    Label* Label::getInstance(const std::string& text)
    {
        return new Label(text);
    }

    Label* Label::getInstance(const std::string& text, const std::string& fontName)
    {
        return new Label(text, fontName);
    }

    Label* Label::getInstance(const std::string& text, const std::string& fontName, SDL_Color color)
    {
        return new Label(text, fontName, color);
    }

    Label::~Label() // safe
	{
	}

    void Label::draw() const
    {
        // Get the renderer from the parent component
        if (!sys.getRenderer()) {
            return;
        }
        SDL_Rect r = { position.x, position.y, size.w, size.h };
        SDL_RenderCopy(sys.getRenderer(), texture, nullptr, &r);
    }

    void Label::setText(const std::string& text)
    {
        TextManager::setText(text);
        resize();
    }

    void Label::setFont(TTF_Font* font)
    {
        TextManager::setFont(font);
        resize();
    }

    //void Label::setFontSize(const int newFontSize)
    //{
    //}

    //const int& Label::getFontSize()
    //{
    //    return fontSize;
    //}

}








//#include "Label.h"
//#include "System.h"
//#include <SDL_ttf.h>
//
//namespace gui {
//	Label::Label(int x, int y, int w, int h, std::string txt): Component(x,y,w,h), text(txt)
//	{
//		SDL_Surface* surface = TTF_RenderText_Solid(sys.getFont(), text.c_str(), {0,0,0});
//		texture = SDL_CreateTextureFromSurface(sys.getRenderer(), surface);
//		SDL_FreeSurface(surface);
//	}
//
//	Label* Label::getInstance(int x, int y, int w, int h, std::string txt)
//	{
//		return new Label(x,y,w,h,txt);
//	}
//
//	void Label::draw() const
//	{
//		SDL_RenderCopy(sys.getRenderer(), texture, NULL, &getRect());
//	}
//
//	Label::~Label()
//	{
//		SDL_DestroyTexture(texture);
//	}
//
//	std::string Label::getText() const
//	{
//		return text;
//	}
//
//	void Label::setText(std::string newText)
//	{
//		text = newText;
//		SDL_DestroyTexture(texture);
//		SDL_Surface* surface = TTF_RenderText_Solid(sys.getFont(), text.c_str(), {0,0,0});
//		texture = SDL_CreateTextureFromSurface(sys.getRenderer(), surface);
//		SDL_FreeSurface(surface);
//	}
//}
//
