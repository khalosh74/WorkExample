#include "Container.h"
#include "System.h"
#include <iostream>

namespace gui {
	Container::Container(): Component(){
	}

	Container* Container::getInstance()
	{
		return new Container();
	}

	Container::~Container(){
		clear();
	}

	const std::vector<Component*> Container::getChildren()
	{
		return children;
	}
	void Container::addAll(std::vector<Component*> cs)
	{
		for (Component* c : cs) {
			add(c);
		}
	}
	void Container::add(Component* c)
	{
        children.push_back(c);
		Resize(c);
	}
	void Container::remove(Component* c)
	{
        auto it = std::find(children.begin(), children.end(), c);
        if (it != children.end()) {
            children.erase(it);
        }
	}
	void Container::clear()
	{
		children.clear();
	}
	void Container::draw() const
	{
		SDL_SetRenderDrawColor(sys.getRenderer(), 50, 0, 0, 255);
		SDL_Rect r = { position.x, position.y, size.w, size.h };
		SDL_RenderDrawRect(sys.getRenderer(), &r);
	}
	void Container::Resize(Component* c)
	{ 
		for (Component* cs : children) {
			if (cs->getPosition().x > position.x) {
				position.x = cs->getPosition().x;
			}
			if (cs->getPosition().y > position.y) {
				position.y = cs->getPosition().y;
			}
			if (cs->getPosition().x + cs->getSize().w > position.x + size.w) {
				size.w += ((cs->getPosition().x + cs->getSize().w) - size.w);
			}
			if (cs->getPosition().y + c->getSize().h > position.y + size.h) {
				size.h += ((cs->getPosition().y + cs->getSize().h) - size.h);
			}
		}
		draw();
	}
}