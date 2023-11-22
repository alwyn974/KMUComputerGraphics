//
// Created by alwyn on 16/10/2023.
//

#ifndef KMU_MYGLWINDOW_HPP
#define KMU_MYGLWINDOW_HPP

#include "Loader.hpp"
#include "ColorCube.hpp"
#include "CheckeredFloor.hpp"
#include "Viewer.hpp"
#include "VBOTeapot.hpp"
#include "VBOTorus.hpp"
#include "GL/gl3w.h"
#include <glfw/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <optional>

class MyGLWindow {
public:
    explicit MyGLWindow(int width, int height);

    void draw();

    void setSize(int width, int height)
    {
        _width = width;
        _height = height;
    };

    void setAspectRatio(float aspectRatio)
    {
        viewer->setAspectRatio(aspectRatio);
    }

    std::optional<Viewer> viewer;
private:
    ShaderProgram _shaderProgram;
    ShaderProgram _shaderProgramFloor;
    ShaderProgram _shaderProgramTeapot;
    ShaderProgram _shaderProgramTorus;
    int _width;
    int _height;
    std::optional<ColorCube> _cube;
    std::optional<CheckeredFloor> _floor;
    std::optional<VBOTeapot> _teapot;
    std::optional<VBOTorus> _torus;

    void initialize();
};

#endif //KMU_MYGLWINDOW_HPP
