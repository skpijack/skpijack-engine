#pragma once

#include <SDL3/SDL.h>
#include <Logger.hpp>
#include <string>

class Window {
public:
	typedef SDL_Window* window_t;
	typedef SDL_Surface* surface_t;
	typedef SDL_Event event_t;

	struct WindowConstructInfo {
		const std::string title;
		const int width;
		const int height;
		const bool resizable;
	};

	enum EVENTS {
		ECLIPSE_EVENT_QUIT = SDL_EVENT_QUIT
	};

	Window(WindowConstructInfo& window_construct_info);
	void update() const;
	event_t getEvents() const;
	~Window();
};