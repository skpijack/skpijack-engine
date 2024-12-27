constexpr int INIT_WINDOW_WIDTH = 800;
constexpr int INIT_WINDOW_HEIGHT = 800;

#include "GLAD/glad.h"
#include "Window.hpp"
#include "Logger.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

Window::window_t pWindow;

float vertices[] = {
    // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
};

uint32_t indices[] = {
    0, 1, 3,
    1, 2, 3
};

void framebuffer_size_callback(Window::window_t pwindow, int width, int height);
void process_input(Window::window_t pwindow);

void framebuffer_size_callback(Window::window_t pwindow, int width, int height) {
    glViewport(0, 0, width, height);
}

void process_input(Window::window_t pwindow) {
    if (glfwGetKey(pwindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(pwindow, true);
}

int main(int argc, char* argv[]) {
    // Open window
    Window window("Eclipse Model Viewer", INIT_WINDOW_WIDTH, INIT_WINDOW_HEIGHT, true, false);

    // Init glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        mog::it("Failed to find opengl context!", 0);
    }

    glViewport(0, 0, INIT_WINDOW_WIDTH, INIT_WINDOW_HEIGHT);

    pWindow = window.getPointer();

    glfwSetFramebufferSizeCallback(pWindow, framebuffer_size_callback);

    Shader ourShader("../src/Shaders/shader_v.glsl", "../src/Shaders/shader_f.glsl");

    // GL Context Start here
    uint32_t VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
        
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    Texture texture1("../assets/valo.png");
    Texture texture2("../assets/cs2.jpg");

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    ourShader.setValue("texture1", 0);
    ourShader.setValue("texture2", 1);

    while (!window.shouldClose()) {
        process_input(pWindow);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        texture1.bind(GL_TEXTURE0);
        texture2.bind(GL_TEXTURE1);

        ourShader.use();
        ourShader.setValue("texture1", 0);
        ourShader.setValue("texture2", 1);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        window.update();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // Cleanup

    return 0;
}