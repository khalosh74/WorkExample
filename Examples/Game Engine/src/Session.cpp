#include "Session.h"
#include <SDL.h>
#include "System.h"

namespace gui {

	void Session::run()
	{
		int  tickInterval = 1000 / fps;		//Track FPS
		while (running) {
			Uint32 nextTick = SDL_GetTicks() + tickInterval; //Track FPS

			// Create and handel events such as input
			SDL_Event eve; 
			while (SDL_PollEvent(&eve))
			{
				switch (eve.type) {
				case SDL_QUIT: running = false; break;
				case SDL_MOUSEBUTTONDOWN:
					if (mouseDownButtonCallbacks_.find(eve.button.button) != mouseDownButtonCallbacks_.end()) {
						mouseDownButtonCallbacks_[eve.button.button](eve.button.x, eve.button.y);
					}
					break;
				case SDL_MOUSEBUTTONUP:
					if (mouseUpButtonCallbacks_.find(eve.button.button) != mouseUpButtonCallbacks_.end()) {
						mouseUpButtonCallbacks_[eve.button.button](eve.button.x, eve.button.y);
					}
					break;
				case SDL_KEYDOWN:
					if (keyDownCallbacks_.find(eve.key.keysym.sym) != keyDownCallbacks_.end()) {
						keyDownCallbacks_[eve.key.keysym.sym]();
					}
					break;
				case SDL_KEYUP:
					if (keyUpCallbacks_.find(eve.key.keysym.sym) != keyUpCallbacks_.end()) {
						keyUpCallbacks_[eve.key.keysym.sym]();
					}
					break;
				}// switch event type
			}// inner while event queue
			update();
			sys.checkCollision();
			int delay = nextTick - SDL_GetTicks();

			//Render
			SDL_SetRenderDrawColor(sys.getRenderer(), 255, 255, 255, 255);
			SDL_RenderClear(sys.getRenderer());
			for (Component* c : components) c->draw();
			SDL_RenderPresent(sys.getRenderer());
			if (delay > 0) SDL_Delay(delay);
		}//outer while run
	}

	void Session::update(std::function<void()> functions) // add things to update
	{
		updateFunctions.push_back(functions);
	}

	void Session::update() // do the updating
	{
		for (auto& func : updateFunctions) {
			func();
		}
	}

	void Session::setFPS(const int& newFPS)
	{
		fps = newFPS;
	}

	const int& Session::getFPS()
	{
		return fps;
	}
	void Session::add(Component* c)
	{
		components.push_back(c);
	}


	void Session::remove(Component* c)
	{
		auto it = std::find(components.begin(), components.end(), c);
		if (it != components.end()) {
			components.erase(it);
		}
	}


	void Session::addAll(std::vector<Component*> cs)
	{
		for (Component* c : cs) add(c);
	}


	void Session::clear()
	{
		components.clear();
	}

	void Session::quit()
	{
		running = false;
	}

	Session::~Session()
	{
		clear();
	}
	//addKeyDownCallback
	void Session::addKeyDownCallback(SDL_Keycode key, KeyCallback callback) {
		keyDownCallbacks_[key] = callback;
	}
	void Session::addKeyUpCallback(SDL_Keycode key, KeyCallback callback) {
		keyUpCallbacks_[key] = callback;
	}
	void Session::addMouseDownButtonCallback(Uint8 button, MouseButtonCallback callback) {
		mouseDownButtonCallbacks_[button] = callback;
	}
		void Session::addMouseUpButtonCallback(Uint8 button, MouseButtonCallback callback) {
		mouseUpButtonCallbacks_[button] = callback;
	}
}