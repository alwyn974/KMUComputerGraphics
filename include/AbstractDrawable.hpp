//
// Created by alwyn on 17/12/2023.
//

#ifndef ABSTRACT_DRAWABLE_HPP
#define ABSTRACT_DRAWABLE_HPP

#include <string>

#include "GL/gl3w.h"
#include "imgui.h"
#include "imgui_stdlib.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class AbstractDrawable {
public:
    AbstractDrawable() = default;
    virtual ~AbstractDrawable() = default;

    /**
     * \brief Initialize the drawable
     */
    virtual void init() = 0;

    /**
     * \brief Update the drawable
     * \param currentTime The current time
     * \param deltaTime  The time since the last update
     */
    virtual void update(float currentTime, float deltaTime) = 0;

    /**
     * \brief Render imgui elements
     * \param mainWindowName The name of the main window
     */
    virtual void imgui(const std::string &mainWindowName) = 0;

    /**
     * \brief Draw the drawable
     */
    virtual void draw() const = 0;

protected:
    GLuint vaoHandle = 0;
};

#endif //ABSTRACT_DRAWABLE_HPP
