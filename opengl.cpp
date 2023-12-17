//
// Created by alwyn on 11/10/2023.
//

#include "MyGlWindow.hpp"
#include <iostream>
//#include <format>
#include <memory>

#ifdef WIN32
#ifdef __cplusplus
extern "C" {
#endif

__declspec(dllexport) DWORD NvOptimusEnablement = 1;
__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;

#ifdef __cplusplus
}
#endif
#endif

std::unique_ptr<MyGLWindow> myGLWindow;
bool lButtonDown;
bool rButtonDown;
bool mButtonDown;
double lastMouseX;
double lastMouseY;
double cx, cy;

static void window_size_callback(GLFWwindow *window, int width, int height)
{
    if (!myGLWindow)
        return;
    myGLWindow->setSize(width, height);
    myGLWindow->setAspectRatio((float) width / (float) height);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
    cx = xpos;
    cy = ypos;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        lastMouseX = xpos;
        lastMouseY = ypos;
    }

    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (GLFW_PRESS == action)
            lButtonDown = true;
        else if (GLFW_RELEASE == action)
            lButtonDown = false;
    }

    else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        if (GLFW_PRESS == action)
            rButtonDown = true;
        else if (GLFW_RELEASE == action)
            rButtonDown = false;
    }

    else if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
        if (GLFW_PRESS == action)
            mButtonDown = true;
        else if (GLFW_RELEASE == action)
            mButtonDown = false;
    }
}

void mouseDragging(double width, double height)
{
    if (lButtonDown) {
        float fractionChangeX = static_cast<float>(cx - lastMouseX) / static_cast<float>(width);
        float fractionChangeY = static_cast<float>(lastMouseY - cy) / static_cast<float>(height);
        myGLWindow->viewer->rotate(fractionChangeX, fractionChangeY);
    }
    else if (mButtonDown) {
        float fractionChangeX = static_cast<float>(cx - lastMouseX) / static_cast<float>(width);
        float fractionChangeY = static_cast<float>(lastMouseY - cy) / static_cast<float>(height);
        myGLWindow->viewer->zoom(fractionChangeY);
    }
    else if (rButtonDown) {
        float fractionChangeX = static_cast<float>(cx - lastMouseX) / static_cast<float>(width);
        float fractionChangeY = static_cast<float>(lastMouseY - cy) / static_cast<float>(height);
        myGLWindow->viewer->translate(-fractionChangeX, -fractionChangeY, 1);
    }
    lastMouseX = cx;
    lastMouseY = cy;
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

    int width = 1280, height = 720;

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
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
//    glfwSwapInterval(1);

    glfwSetKeyCallback(window, key_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_pos_callback);

    glfwSetWindowTitle(window, "MyOpenGLWindow");

    myGLWindow = std::make_unique<MyGLWindow>(width, height);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();

    int frame = 0;
    double lastTime = glfwGetTime();
    while (!glfwWindowShouldClose(window)) {
        // clear screen
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!
        const double currentTime = glfwGetTime();
        const auto delta = static_cast<float>(currentTime - lastTime);
        lastTime = currentTime;

        // poll events
        glfwPollEvents();
        if (!io.WantCaptureMouse)
            mouseDragging(width, height);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        myGLWindow->draw(currentTime, delta);
        // draw fps
        frame++;
        if (currentTime - lastTime >= 1.0) {
            std::cout << "FPS: " << frame << std::endl;
            frame = 0;
            lastTime += 1.0;
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // swap buffers
        glfwSwapBuffers(window);
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
