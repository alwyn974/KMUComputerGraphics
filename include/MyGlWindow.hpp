//
// Created by alwyn on 16/10/2023.
//

#ifndef KMU_MYGLWINDOW_HPP
#define KMU_MYGLWINDOW_HPP

#include "Loader.hpp"
#include "ColorCube.hpp"
#include "Viewer.hpp"
#include "GL/gl3w.h"
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <optional>

class MyGLWindow {
public:
    explicit MyGLWindow(int width, int height);

    void draw();

    void setSize(int width, int height);

private:
    ShaderProgram _shaderProgram;
    int _width;
    int _height;
    std::optional<ColorCube> _cube;

    void setupBuffer();
};


#endif //KMU_MYGLWINDOW_HPP
