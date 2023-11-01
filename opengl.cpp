//
// Created by alwyn on 11/10/2023.
//

#include "MyGlWindow.hpp"
#include <iostream>
#include <format>
#include <memory>

std::unique_ptr<MyGLWindow> myGLWindow;

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

static void window_size_callback(GLFWwindow *window, int width, int height)
{
    if (!myGLWindow)
         return;
      myGLWindow->setSize(width, height);
}

int main(int ac, char **av)
{
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return 1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    int width = 800, height = 800;

    GLFWwindow *window = glfwCreateWindow(width, height, "My Title", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);
    if (gl3wInit()) {
        std::cerr << "Failed to initialize OpenGL" << std::endl;
        return 1;
    }
    if (!gl3wIsSupported(4, 6)) {
        std::cerr << "OpenGL 4.6 not supported" << std::endl;
        return 1;
    }
    std::cout << "OpenGL " << glGetString(GL_VERSION) << " " << "GLSL " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
//    glfwSwapInterval(1);

    glfwSetKeyCallback(window, key_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);
    glfwSetWindowTitle(window, "MyOpenGLWindow");

    myGLWindow = std::make_unique<MyGLWindow>(width, height);

    int frame = 0;
    double lastTime = glfwGetTime();
    while (!glfwWindowShouldClose(window)) {
        // clear screen
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

        myGLWindow->draw();
        // draw fps
        frame++;
        double currentTime = glfwGetTime();
        if (currentTime - lastTime >= 1.0) {
            std::cout << std::format("{} fps\n", frame);
            frame = 0;
            lastTime = currentTime;
        }

        // swap buffers
        glfwSwapBuffers(window);
        // poll events
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
