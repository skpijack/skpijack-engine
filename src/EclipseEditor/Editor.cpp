#include <EclipseUtils/IO.hpp>
#include <EclipseSystem/Window.hpp>
#include <EclipseFilesystem/Loader.hpp>

// Global functions
static void resize_cb(et::window, et::i32, et::i32);

// Gobal Variables
et::u32 delta{};
std::shared_ptr<e::window> pwindow;

int main() {
	et::windowCreateInfo window_create_info{};
	window_create_info.title = "Eclipse Editor";
	window_create_info.width = 960;
	window_create_info.height = 540;
	window_create_info.resizable = true;
	window_create_info.fullscreen = false;
	window_create_info.maximised = true;
	window_create_info.samples = 4;
	window_create_info.vsync = true;
	window_create_info.resize_callback = resize_cb;
	window_create_info.cursor_pos_callback = nullptr;

	// Create window
	std::shared_ptr<e::window> window = std::make_shared<e::window>(window_create_info);

	// Make window global
	pwindow = window;

	// MainLoop
	while (!window->shouldClose()) {
		// Calculate Delta
		delta = window->getIntervalToPreviousCall();

		// Swap Framebuffer
		window->update();
	}
}

// Resize callback function
static void resize_cb(et::window window, et::i32 width, et::i32 height) {
	pwindow->width = width;
	pwindow->height = height;
	io::logMessage(io::LogLevel::DEBUG, "Window resized to w:{} h:{}", pwindow->width, pwindow->height);
}