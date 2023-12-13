//
// Created by alwyn on 11/12/2023.
//

#ifndef SKYBOX_HPP
#define SKYBOX_HPP

#include "Loader.hpp"
#include <vector>
#include <string>
#include "glm/gtc/type_ptr.hpp"

class Skybox {
public:
    explicit Skybox(/*const std::vector<std::string> &faces*/);

    void draw(ShaderProgram &shaderProgram);

private:
    unsigned int textureID;
    unsigned int VAO, VBO;
    /*std::vector<std::string> faces;*/

    void initialize();
};

#endif //SKYBOX_HPP
