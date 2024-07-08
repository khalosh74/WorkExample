#ifndef CONTAINER_H
#define CONTAINER_H
#include <vector>
#include "Component.h"
#include "TextureManager.h"
#include "Session.h"
#include <SDL.h>
#include <vector>
#include <SDL_image.h>

namespace gui {
	class Container : public Component {
	public:
		static Container* getInstance();

		virtual ~Container();
		const std::vector<Component*> getChildren();
		void addAll(std::vector<Component*> cs);
		void add(Component* c);
		void remove(Component* c);
		void clear();
		void draw() const override;
		virtual void Resize(Component* c);

		//enum MyEnum
		//{
		//	FREE,
		//	H_MID, H_LEFT, H_RIGHT,
		//	V_MID, V_TOP, V_DOWN,
		//	BORDER
		//};
	protected:
		Container();
		int spacing = 0;
		int padding = 0;
		std::vector<Component*> children;
	};
}

#endif
