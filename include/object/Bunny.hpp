//
// Created by alwyn on 23/11/2023.
//

#ifndef KMU_BUNNY_HPP
#define KMU_BUNNY_HPP

#include "Loader.hpp"
#include "MaterialColor.hpp"

class Bunny {
public:
    Bunny();

    void draw(const MaterialColor &materialColor = MaterialColor::emerald) const;

private:
    void initialize();
    GLuint vaoHandle;
    ShaderProgram shaderProgram;
};

#endif //KMU_BUNNY_HPP
