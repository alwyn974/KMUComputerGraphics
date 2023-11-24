//
// Created by alwyn on 23/11/2023.
//

#ifndef KMU_COW_HPP
#define KMU_COW_HPP

#include "GL/gl3w.h"
#include <GLFW/glfw3.h>
#include <vector>

class Cow {
public:
    Cow();

    void draw() const;
private:
    GLuint vaoHandle;

    void initialize();
};

#endif //KMU_COW_HPP
