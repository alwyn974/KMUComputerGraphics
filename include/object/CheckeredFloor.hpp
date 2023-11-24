//
// Created by alwyn on 15/11/2023.
//

#ifndef KMU_CHECKEREDFLOOR_HPP
#define KMU_CHECKEREDFLOOR_HPP

#include <vector>
#include "GL/gl3w.h"
#include "glm/glm.hpp"

class CheckeredFloor {
public:
    explicit CheckeredFloor(int size, int nsquare);

    void generate();

    void draw();

private:
    int _size;
    int _nsquare;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> colors;
    GLuint vao, vboVertices, vboColors;
};

#endif //KMU_CHECKEREDFLOOR_HPP
