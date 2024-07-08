#ifndef SESSION_H
#define SESSION_H
#include <vector>
#include "Component.h"

#include <unordered_map>
#include <functional>
#include <SDL.h>

namespace gui {
	class Session {
	public:
		void add(Component* c);
		void remove(Component* c);
		void addAll(std::vector<Component*> cs);
		void clear();
		void run();
		void update(std::function<void()> functions);

		void setFPS(const int& newFPS);
		const int& getFPS();

		void quit();
		~Session();


		using KeyCallback = std::function<void()>;
		using MouseButtonCallback = std::function<void(int, int)>;

		void addKeyDownCallback(SDL_Keycode key, KeyCallback callback);
		void addKeyUpCallback(SDL_Keycode key, KeyCallback callback);

		void addMouseDownButtonCallback(Uint8 button, MouseButtonCallback callback);
		void addMouseUpButtonCallback(Uint8 button, MouseButtonCallback callback);

	private:
		bool running = true;

		std::unordered_map<SDL_Keycode, KeyCallback> keyDownCallbacks_;
		std::unordered_map<SDL_Keycode, KeyCallback> keyUpCallbacks_;
		std::unordered_map<Uint8, MouseButtonCallback> mouseDownButtonCallbacks_;
		std::unordered_map<Uint8, MouseButtonCallback> mouseUpButtonCallbacks_;

		int fps = 60;
		std::vector<Component*> components;
		std::vector<std::function<void()>> updateFunctions;
		void update();
	};
}

#endif
