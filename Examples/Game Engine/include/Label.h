#ifndef LABEL_H
#define LABEL_H
#include <string>
#include "Component.h"
#include "TextManager.h"
#include "System.h"
#include <SDL_ttf.h>
#include <SDL.h>

namespace gui {
    class Label : public Component, public TextManager
    {
    public:
        static Label* getInstance(const std::string& text);
        static Label* getInstance(const std::string& text, const std::string& fontName);
        static Label* getInstance(const std::string& text, const std::string& fontName, SDL_Color color);
        ~Label();
        void draw() const override;
        void setText(const std::string& newText) override;

        void setFont(TTF_Font* newFont) override;

    protected:
        Label(const std::string& text);
        Label(const std::string& text, const std::string& fontName);
        Label(const std::string& text, const std::string& fontName, SDL_Color color);
    private:
        void resize();
        Label(const Label&) = delete;
		const Label& operator =(const Label&) = delete;
    };
}






//#include <SDL.h>
//#include "Component.h"
//#include <string>
//
//namespace gui {
//	class Label: public Component
//	{
//	public:
//		static Label* getInstance(int x, int y, int w, int h, std::string txt);
//		void draw() const;
//		~Label();
//		std::string getText() const;
//		void setText(std::string newText);
//	protected:
//		Label(int x, int y, int w, int h, std::string txt);
//	private:
//		std::string text;
//		SDL_Texture* texture;
//		Label(const Label&) = delete;
//		const Label& operator =(const Label&) = delete;
//	};
//}
#endif

