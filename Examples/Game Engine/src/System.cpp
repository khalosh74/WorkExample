#include "System.h"
#include <SDL.h>
#include <iostream>

namespace gui {
	System::System() {
		SDL_Init(SDL_INIT_EVERYTHING);
		win = SDL_CreateWindow("GUI", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
		ren = SDL_CreateRenderer(win, -1, 0);
	}
	System::~System() {
		SDL_DestroyWindow(win);
		SDL_DestroyRenderer(ren);
		SDL_Quit();
	}

	SDL_Renderer* System::getRenderer() const {
		return ren;
	}

	void System::addCollider(BoxCollider* c)
	{
		colliders.push_back(c);
	}

	void System::checkCollision()
	{
		for (int i = 0; i < colliders.size(); i++) {
			BoxCollider* collider1 = colliders[i];
			for (int j = i + 1; j < colliders.size(); j++) {
				BoxCollider* collider2 = colliders[j];
				if (collider1->intersects(*collider2)) {
					collider1->onCollisionEnter(collider2);
					collider2->onCollisionEnter(collider1);
				}
			}
		}
	}

	System sys;
}