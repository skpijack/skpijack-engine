#include <Window.hpp>
#include <EclipseVulkan/vkcore.hpp>

int main(int argc, char* argv[]) {
	// Initialize Window
	Window::WindowConstructInfo window_construct_info{ .title = "Eclipse Editor", .width = 800, .height = 600, .resizable = false };
	Window window = Window::Window(window_construct_info);
	
	// Initialize Vulkan
	evk::init_instance();
	evk::init_physical_devices();

	while (window.getEvents().type != Window::ECLIPSE_EVENT_QUIT) {
		window.update();
	}
}