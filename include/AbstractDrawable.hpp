//
// Created by alwyn on 17/12/2023.
//

#ifndef ABSTRACT_DRAWABLE_HPP
#define ABSTRACT_DRAWABLE_HPP

#include <stdexcept>
#include <string>

#include <glm/gtx/string_cast.hpp>
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
     * Generate the vertex array object
     */
    virtual void init()
    {
        glGenVertexArrays(1, &vaoHandle);
        glBindVertexArray(vaoHandle);
        initialized = true;
    };

    /**
     * \brief Update the drawable
     * \param currentTime The current time
     * \param deltaTime  The time since the last update
     */
    virtual void update(float currentTime, float deltaTime) = 0;

    /**
     * \brief Render imgui elements
     * \param mainWindowName The name of the main window
     * \param flags The flags to pass to ImGui::TreeNode
     */
    virtual void imgui(const std::string&mainWindowName, const ImGuiTreeNodeFlags_ &flags = ImGuiTreeNodeFlags_None) = 0;

    /**
     * \brief Draw the drawable
     * \throws std::runtime_error if the drawable is not initialized
     */
    virtual void draw() const
    {
        if (!initialized)
            throw std::runtime_error("Drawable not initialized");
    }

protected:
    GLuint vaoHandle = 0;
    bool initialized = false;
};

#endif //ABSTRACT_DRAWABLE_HPP
