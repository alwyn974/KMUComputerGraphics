//
// Created by alwyn on 01/11/2023.
//

#ifndef KMU_COLORCUBE_HPP
#define KMU_COLORCUBE_HPP

#include "GL/gl3w.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include <vector>

class ColorCube {
public:
    explicit ColorCube(int width, int height);

    void draw() const;
private:
    GLuint vaoHandle;
    GLuint vboCubeVertices, vboCubeColors, iboCubeElements;
    int _width;
    int _height;
    std::vector<GLfloat> cubeVertices; // TODO: replace later with glm::vec3
    std::vector<GLfloat> cubeColors;
    std::vector<GLushort> cubeElements;

//    GLfloat cubeVertices[24];
//    GLfloat cubeColors[24];
//    GLshort cubeElements[36];

    void setup();
};


#endif //KMU_COLORCUBE_HPP
