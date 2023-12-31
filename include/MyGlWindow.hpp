//
// Created by alwyn on 16/10/2023.
//

#ifndef KMU_MYGLWINDOW_HPP
#define KMU_MYGLWINDOW_HPP

#include <memory>

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
#include "object/Cylinder.hpp"
#include "object/LaserBeam.hpp"
#include "Skybox.hpp"
#include "GL/gl3w.h"
#include "ParticleSystem.hpp"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/glm.hpp>
#include <optional>


// Ray, ray for raycasting
typedef struct Ray {
    glm::vec3 position;       // Ray position (origin)
    glm::vec3 direction;      // Ray direction
} Ray;

// RayCollision, ray hit information
typedef struct RayCollision {
    bool hit;               // Did the ray hit something?
    float distance;         // Distance to the nearest hit
    glm::vec3 point;          // Point of the nearest hit
    glm::vec3 normal;         // Surface normal of hit
} RayCollision;

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

    const glm::vec2 &getMousePosition() const
    {
        return _mousePosition;
    }

    void setMousePosition(const glm::vec2 &mouse_position)
    {
        _mousePosition = mouse_position;
    }

    const glm::vec2 &getLastMousePosition() const
    {
        return _lastMousePosition;
    }

    void setLastMousePosition(const glm::vec2 &last_mouse_position)
    {
        _lastMousePosition = last_mouse_position;
    }

    bool isLButtonDown() const
    {
        return _lButtonDown;
    }

    void setLButtonDown(bool l_button_down)
    {
        _lButtonDown = l_button_down;
    }

    bool isRButtonDown() const
    {
        return _rButtonDown;
    }

    void setRButtonDown(bool r_button_down)
    {
        _rButtonDown = r_button_down;
    }

    bool isMButtonDown() const
    {
        return _mButtonDown;
    }

    void setMButtonDown(bool m_button_down)
    {
        _mButtonDown = m_button_down;
    }

    Ray getMouseRay(glm::mat4 view, mat4 projection);

    std::optional<Viewer> viewer;
private:
    ShaderProgram _shaderProgramLaserBeam;
    ShaderProgram _shaderProgramColor;
    ShaderProgram _shaderProgramParticle;

    int _width;
    int _height;
    std::optional<ColorCube> _cube;
    std::optional<CheckeredFloor> _floor;
//    std::optional<Cow> _cow;
//    std::optional<Sphere> _sphere;
//    std::optional<VBOTeapot> _teapot;
//    std::optional<VBOTorus> _torus;
//    std::optional<Bunny> _bunny;
//    std::optional<BunnyTextured> _bunnyTextured;
//    std::optional<Earth> _earth;
//    std::optional<Ogre> _ogre;
//    std::optional<Skybox> _skybox;
//    std::optional<Cylinder> _cylinder;

    std::optional<ParticleSystem> _particleSystem;
    std::optional<LaserBeam> _laserBeam;
    std::unique_ptr<AbstractDrawable> _drawable;

    glm::vec2 _mousePosition;
    glm::vec2 _lastMousePosition;
    bool _lButtonDown = false;
    bool _rButtonDown = false;
    bool _mButtonDown = false;

    void initialize();
};

#endif //KMU_MYGLWINDOW_HPP
