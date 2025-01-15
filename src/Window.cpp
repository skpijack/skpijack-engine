#include "Window.hpp"

Window::window_t gWindow{ nullptr };
Window::surface_t gSurface{ nullptr };
SDL_Event gEvent;

Window::Window(Window::WindowConstructInfo& window_construct_info) {
	// Check if SDL not intialized
	if (!SDL_Init(SDL_INIT_VIDEO))
		io::printErrorAndExit("Failed to Load SDL!");
	
	// Create Window
	gWindow = SDL_CreateWindow(window_construct_info.title.c_str(), window_construct_info.width, window_construct_info.height, 0);
	
	// Check for success
	if (gWindow == nullptr)
		io::printError("Window Couldn't be created!");

	// Get Surface
	gSurface = SDL_GetWindowSurface(gWindow);
}

void Window::update() const {
	SDL_FillSurfaceRect(gSurface, nullptr, SDL_MapSurfaceRGB(gSurface, 0x00, 0xFF, 0xFF));
	SDL_UpdateWindowSurface(gWindow);
}

Window::event_t Window::getEvents() const {
	SDL_PollEvent(&gEvent);
	return gEvent;
}

Window::~Window() {
	// Destroy Window
	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;
	gSurface = nullptr;

	// Quit SDL Subsystems
	SDL_Quit();
}