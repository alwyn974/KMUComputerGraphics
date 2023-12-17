//
// Created by alwyn on 16/10/2023.
//

#ifndef KMU_MYGLWINDOW_HPP
#define KMU_MYGLWINDOW_HPP

#include "Loader.hpp"
#include "Viewer.hpp"
#include "MaterialColor.hpp"
#include "object/ColorCube.hpp"
#include "object/CheckeredFloor.hpp"
#include "object/Cow.hpp"
#include "object/Sphere.hpp"
#include "object/VBOTeapot.hpp"
#include "object/VBOTorus.hpp"
#include "object/Bunny.hpp"
#include "object/BunnyTextured.hpp"
#include "object/Earth.hpp"
#include "object/Ogre.hpp"
#include "Skybox.hpp"
#include "GL/gl3w.h"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <optional>

class MyGLWindow {
public:
    explicit MyGLWindow(int width, int height);

    void draw(float currentTime, float deltaTime);

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
    ShaderProgram _shaderProgramColor;
    ShaderProgram _shaderProgramTeapot;
    ShaderProgram _shaderProgramTorus;
    ShaderProgram _shaderProgramBunnyTextured;
    ShaderProgram _shaderProgramOgre;
    ShaderProgram _shaderProgramSkybox;
    int _width;
    int _height;
    std::optional<ColorCube> _cube;
    std::optional<CheckeredFloor> _floor;
    std::optional<Cow> _cow;
    std::optional<Sphere> _sphere;
    std::optional<VBOTeapot> _teapot;
    std::optional<VBOTorus> _torus;
    std::optional<Bunny> _bunny;
    std::optional<BunnyTextured> _bunnyTextured;
    std::optional<Earth> _earth;
    std::optional<Ogre> _ogre;
    std::optional<Skybox> _skybox;

    void initialize();
};

#endif //KMU_MYGLWINDOW_HPP
