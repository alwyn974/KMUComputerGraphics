//
// Created by alwyn on 01/11/2023.
//

#include "object/ColorCube.hpp"

#include <iostream>
#include <glm/ext/scalar_constants.hpp>

ColorCube::ColorCube(float width, float height, float depth, std::optional<glm::vec3> color) : vboCubeVertices(0), vboCubeColors(0), iboCubeElements(0)
{
    _width = width;
    _height = height;
    _depth = depth;

    cubeVertices = {
        // front
        {-_width, -_height, _depth},
        {_width, -_height, _depth},
        {_width, _height, _depth},
        {-_width, _height, _depth},
        // back
        {-_width, -_height, -_depth},
        {_width, -_height, -_depth},
        {_width, _height, -_depth},
        {-_width, _height, -_depth},
    };

    if (!color) {
        cubeColors = {
            // front colors
            {1.0, 0.0, 0.0},
            {0.0, 1.0, 0.0},
            {0.0, 0.0, 1.0},
            {1.0, 1.0, 1.0},
            // back colors
            {1.0, 0.0, 0.0},
            {0.0, 1.0, 0.0},
            {0.0, 0.0, 1.0},
            {1.0, 1.0, 1.0}
        };
    }
    else {
        for (int i = 0; i < 8; i++)
            cubeColors.push_back(*color);
    }

    cubeElements = {
        0, 1, 2, 2, 3, 0, 1, 5, 6,
        6, 2, 1, 7, 6, 5, 5, 4, 7,
        4, 0, 3, 3, 7, 4, 4, 5, 1,
        1, 0, 4, 3, 2, 6, 6, 7, 3
    };
}

void ColorCube::imgui(const std::string&mainWindowName, const ImGuiTreeNodeFlags_ &flags)
{
    ImGui::Begin(mainWindowName.c_str());
    if (ImGui::CollapsingHeader("Cube Properties", flags)) {
        if (ImGui::Button("Reset Color"))
            _resetColor = true;
        ImGui::Checkbox("Rotate Color", &_rotateColor);
        ImGui::SliderFloat("Rotating Speed", &_rotatingSpeed, 0.0f, 1.0f);
        ImGui::SliderFloat("Width", &_width, 0.1f, 10.0f);
        ImGui::SliderFloat("Height", &_height, 0.1f, 10.0f);
        ImGui::SliderFloat("Depth", &_depth, 0.1f, 10.0f);
    }
    ImGui::End();
}

void ColorCube::update(float currentTime, float deltaTime)
{
    static std::vector<glm::vec3> cubeColorCopy(cubeColors.size());
    static bool firstTime = true;
    if (firstTime) {
        cubeColorCopy = cubeColors;
        firstTime = false;
    }

    if (_resetColor) {
        cubeColorCopy = cubeColors;
        _resetColor = false;
    }

    for (int i = 0; this->_rotateColor && i < cubeColorCopy.size(); i++) {
        const float offset = (i / 3) * (2.0f * glm::pi<float>() / cubeColorCopy.size() * 3); // offset each face's color by a fraction of 2PI
        cubeColorCopy[i] = glm::vec3(
            (glm::sin(currentTime * _rotatingSpeed + offset) + 1.0f) / 2.0f,
            (glm::sin(currentTime * _rotatingSpeed + offset + 2.0f * glm::pi<float>() / 3.0f) + 1.0f) / 2.0f,
            (glm::sin(currentTime * _rotatingSpeed + offset + 4.0f * glm::pi<float>() / 3.0f) + 1.0f) / 2.0f
        );
    }

    glBindBuffer(GL_ARRAY_BUFFER, vboCubeColors); // select VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeColorCopy[0]) * cubeColorCopy.size(), cubeColorCopy.data(), GL_STATIC_DRAW); // copy data to VBO

    cubeVertices = {
        // front
        {-_width, -_height, _depth},
        {_width, -_height, _depth},
        {_width, _height, _depth},
        {-_width, _height, _depth},
        // back
        {-_width, -_height, -_depth},
        {_width, -_height, -_depth},
        {_width, _height, -_depth},
        {-_width, _height, -_depth},
    };

    // Update VBO for vertex position
    glBindBuffer(GL_ARRAY_BUFFER, vboCubeVertices); // select VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices[0]) * cubeVertices.size(), cubeVertices.data(), GL_STATIC_DRAW); // copy data to VBO
}

void ColorCube::draw() const
{
    AbstractDrawable::draw();

    glBindVertexArray(vaoHandle); // select _vaoHandle
    glDrawArrays(GL_TRIANGLES, 0, 8); // first: primitive type, second: start index, third: number of vertices
    int size = 0;
    glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
    glDrawElements(GL_TRIANGLES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, nullptr);
    glBindVertexArray(0); // close the current _vaoHandle
}

void ColorCube::init()
{
    AbstractDrawable::init();

    // Create VBO for vertex position
    glGenBuffers(1, &vboCubeVertices);
    glBindBuffer(GL_ARRAY_BUFFER, vboCubeVertices); // select VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices[0]) * cubeVertices.size(), cubeVertices.data(), GL_STATIC_DRAW); // copy data to VBO
    glVertexAttribPointer(
        0, // property or attribute index
        3, // number of components per vertex attribute
        GL_FLOAT, // data type
        GL_FALSE, // normalized?
        0, // stride
        nullptr // array buffer offset
    );
    glEnableVertexAttribArray(0); // enable this attribute index

    // Create VBO for color
    glGenBuffers(1, &vboCubeColors);
    glBindBuffer(GL_ARRAY_BUFFER, vboCubeColors); // select VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeColors[0]) * cubeColors.size(), cubeColors.data(), GL_STATIC_DRAW); // copy data to VBO
    glVertexAttribPointer(
        1, // property or attribute index
        3, // number of components per vertex attribute
        GL_FLOAT, // data type
        GL_FALSE, // normalized?
        0, // stride
        nullptr // array buffer offset
    );
    glEnableVertexAttribArray(1); // enable this attribute index

    // Create a buffer for vertex index
    glGenBuffers(1, &iboCubeElements);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboCubeElements);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeElements[0]) * cubeElements.size(), cubeElements.data(), GL_STATIC_DRAW);

    glBindVertexArray(0); // close the current _vaoHandle
}
