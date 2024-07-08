#include "Component.h"

namespace gui {

	Component::Component(int x, int y, int w, int h) : position(x,y), size(w,h), rect{ x,y,w,h }
	{
	}

	Component::~Component()
	{
	}

	Component::Component()
	{
	}

	Component::Component(Position pos)
	{
		setPosition(pos);
	}

	Component::Component(Size size)
	{
		setSize(size);
	}

	Component::Component(Position pos, Size size)
	{
		setPosition(pos);
		setSize(size);
	}

	const Position& Component::getPosition()
	{
		return position;
	}

	void Component::setPosition(Position& newPos)
	{
		position = newPos;
		updateRect(position);
	}

	void Component::setPosition(int& x, int& y)
	{
		position.x = x;
		position.y = y;
		updateRect(position);
	}

	const Size& Component::getSize()
	{
		return size;
	}

	const std::string& Component::getName()
	{
		return name;
	}

	void Component::setSize(Size& newSize)
	{
		size = newSize;
		updateRect(size);
	}

	void Component::setSize(int& w, int& h)
	{
		size.w = w;
		size.h = h;
		updateRect(size);
	}

	void Component::setName(std::string& newName)
	{
		name = newName;
	}

	void Component::updateRect(Position pos) {
		rect = { pos.x, pos.y, rect.w, rect.h };		
		draw();
	}
	void Component::updateRect(Size size) {
		rect = { rect.x, rect.y, size.w, size.h};
		draw();
	}
}