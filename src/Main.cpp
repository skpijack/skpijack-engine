#include <Window.hpp>

int main(int argc, char* argv[]) {
	Window::WindowConstructInfo window_construct_info{ .title = "Eclipse Editor", .width = 800, .height = 600, .resizable = false };
	Window window = Window::Window(window_construct_info);
	
	while (window.getEvents().type != Window::ECLIPSE_EVENT_QUIT) {
		window.update();
	}
}