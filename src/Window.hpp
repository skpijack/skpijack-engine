#pragma once
#include <GLFW/glfw3.h>
#include <string>

class Window {
    public:
    typedef GLFWwindow* window_t;
    uint32_t w, h;

    Window(std::string title, int width, int height, bool isResizable, bool isFullscreen);
    void update();
    bool shouldClose();
    window_t getPointer();
    ~Window();
};