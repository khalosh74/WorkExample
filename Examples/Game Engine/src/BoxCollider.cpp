#include "BoxCollider.h"
#include "System.h"
#include <iostream>

namespace gui {
	BoxCollider::BoxCollider() : Container()
	{
		sys.addCollider(this);
	}
	BoxCollider* BoxCollider::getInstance()
	{
		return new BoxCollider();
	}

	void BoxCollider::setPosition(Position& newPos)
	{
		Component::setPosition(newPos);
		for (Component* c : children) {
			c->setPosition(newPos);
			Resize(c);
		}
	}

	void BoxCollider::setPosition(int& newX, int& newY)
	{
		if (curentLayOut == HORIZONTAL) {
			int xOffset = newX;
			Component::setPosition(newX, newY);
			for (Component* c : children) {
				c->setPosition(xOffset, newY);
				xOffset += c->getSize().w;
			}
		}
		else if (curentLayOut == VERTICAL) {
			int yOffset = newY;
			Component::setPosition(newX, newY);
			for (Component* c : children) {
				c->setPosition(newX, yOffset);
				yOffset += c->getSize().h;
			}
		}
	}

	void BoxCollider::setLayOut(std::string typeName)
	{
		if(typeName == "H") curentLayOut = HORIZONTAL;
		else if(typeName == "V") curentLayOut = VERTICAL;
	}


	bool BoxCollider::intersects(const BoxCollider& other) const {
		int x1 = position.x;
		int y1 = position.y;
		int w1 = size.w;
		int h1 = size.h;
		int x2 = other.position.x;
		int y2 = other.position.y;
		int w2 = other.size.w;
		int h2 = other.size.h;

		return x1 < x2 + w2 &&
			x2 < x1 + w1 &&
			y1 < y2 + h2 &&
			y2 < y1 + h1;
	}

	void BoxCollider::onCollisionEnter(BoxCollider* other) {
		if (onCollisionEnterListener) {
			onCollisionEnterListener(other);
		}
	}
	void BoxCollider::onCollisionEnter(std::function<void(BoxCollider*)> listener) {
		onCollisionEnterListener = listener;
	}
}