#ifndef SYSTEM_H
#define SYSTEM_H
#include <SDL.h>
#include <vector>
#include "BoxCollider.h"

namespace gui {
	class System {
	public:
		System();
		~System();
		SDL_Renderer* getRenderer() const;
		void addCollider(BoxCollider*);
		void checkCollision();

	private:
		std::vector<BoxCollider*> colliders;
		SDL_Window* win;
		SDL_Renderer* ren;
	};
	extern System sys;
}

#endif
