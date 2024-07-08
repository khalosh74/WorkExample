#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include <string>
#include "Container.h"
//#include "CollisionListener.h"


namespace gui {
	class BoxCollider : public Container {
	public:
		static BoxCollider* getInstance();
		virtual void setPosition(Position& newPos) override;
		virtual void setPosition(int& x, int& y) override;
		bool intersects(const BoxCollider& other) const;
		//virtual void Resize(Component* c) override;
		
		virtual void setLayOut(std::string typeName);

		void onCollisionEnter(BoxCollider* other);
		void onCollisionEnter(std::function<void(BoxCollider*)> listener);

		void draw() const override { Container::draw(); };
		//void setListener(CollisionListener* listener);

		enum LayOut
		{
			HORIZONTAL, VERTICAL
		};

	protected:
		//CollisionListener* listener = nullptr;
		std::function<void(BoxCollider*)> onCollisionEnterListener;
		LayOut curentLayOut = HORIZONTAL;
		BoxCollider();

	};
}

#endif //!BOXCOLLIDER_H
