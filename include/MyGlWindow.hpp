//
// Created by alwyn on 16/10/2023.
//

#ifndef KMU_MYGLWINDOW_HPP
#define KMU_MYGLWINDOW_HPP

#include "GL/gl3w.h"
#include "Loader.hpp"
#include <glfw/glfw3.h>
#include <glm/glm.hpp>

class MyGLWindow {
public:
    explicit MyGLWindow(int width, int height);

    void draw();

private:
    ShaderProgram _shaderProgram;
    int _width;
    int _height;

    void setupBuffer();
};


#endif //KMU_MYGLWINDOW_HPP
