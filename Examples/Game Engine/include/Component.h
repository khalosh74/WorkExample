#ifndef COMPONENT_H
#define COMPONENT_H
#include <SDL.h>
#include <string>
#include "Position.h"
#include "Size.h"

namespace gui {
	class Component
	{
	public:
		virtual ~Component();
		virtual void draw() const = 0;

		const Position& getPosition();
		const Size& getSize();
		const std::string& getName();

		virtual void setPosition(Position& newPos); // test make them protecred
		virtual void setPosition(int& x, int& y);
		virtual void setSize(Size& newSize);
		virtual void setSize(int& w, int& h);
		virtual void setName(std::string& newName);

	protected:
		Component();
		Component(Position pos);
		Component(Size size);
		Component(Position pos, Size size);
		Component(int x, int y, int w, int h);

		Position position = Position(0, 0); // default
		Size size = Size(50, 50); // default
		std::string name = "";
	private:
		Component(const Component&) = delete;
		const Component& operator =(const Component&) = delete;

		void updateRect(Position pos);
		void updateRect(Size size);

		SDL_Rect rect = {0, 0, 50, 50}; // default
	};
}
#endif