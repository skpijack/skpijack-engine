#include "Window.hpp"
#include "Logger.hpp"

Window::window_t pointerWindow;

Window::Window(std::string title, int width, int height, bool isResizable, bool isFullscreen) {
    
    if (!glfwInit())
        mog::it("failed to initialize window manager!", 0);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, isResizable);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    pointerWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

    if (pointerWindow == NULL) {
        mog::it("failed to create window!", 1);
        glfwTerminate();
        std::exit(-2);
    }

    glfwMakeContextCurrent(pointerWindow);
}

void Window::update() {
    glfwSwapBuffers(pointerWindow);
    glfwPollEvents();
}

Window::window_t Window::getPointer() {
    return pointerWindow;
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(pointerWindow);
}

Window::~Window() {
    if (pointerWindow != NULL)
        glfwTerminate();
}