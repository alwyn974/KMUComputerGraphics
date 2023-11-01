//
// Created by alwyn on 01/11/2023.
//

#include "ColorCube.hpp"

ColorCube::ColorCube(int width, int height) : vaoHandle(0), vboCubeVertices(0), vboCubeColors(0), iboCubeElements(0)
{
    _width = width;
    _height = height;

    cubeVertices = {
        // front
        -1.0, -1.0, 1.0,
        1.0, -1.0, 1.0,
        1.0, 1.0, 1.0,
        -1.0, 1.0, 1.0,
        // back
        -1.0, -1.0, -1.0,
        1.0, -1.0, -1.0,
        1.0, 1.0, -1.0,
        -1.0, 1.0, -1.0
    };

    cubeColors = {
        // front colors
        1.0, 0.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 0.0, 1.0,
        1.0, 1.0, 1.0,
        // back colors
        1.0, 0.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 0.0, 1.0,
        1.0, 1.0, 1.0
    };

    cubeElements = {
        0, 1, 2, 2, 3, 0, 1, 5, 6,
        6, 2, 1, 7, 6, 5, 5, 4, 7,
        4, 0, 3, 3, 7, 4, 4, 5, 1,
        1, 0, 4, 3, 2, 6, 6, 7, 3
    };

    this->setup();
}

void ColorCube::draw() const
{
    glBindVertexArray(vaoHandle); // select VAO
    glDrawArrays(GL_TRIANGLES, 0, 8); // first: primitive type, second: start index, third: number of vertices
    int size = 0;
    glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
    glDrawElements(GL_TRIANGLES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, nullptr);
}

void ColorCube::setup()
{
    // Create VAO vertex position
    glGenVertexArrays(1, &vaoHandle);
    glBindVertexArray(vaoHandle); // select VAO
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

    glBindVertexArray(0); // close the current VAO
}
