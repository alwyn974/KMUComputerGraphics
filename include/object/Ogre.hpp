//
// Created by alwyn on 06/12/2023.
//

#ifndef KMU_OGRE_HPP
#define KMU_OGRE_HPP

#include "Loader.hpp"
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <tuple>

class Ogre {
public:
    explicit Ogre(const std::string &texturePath, const std::string &normalMapPath);

    void draw(ShaderProgram &shaderProgram) const;

private:
    void initialize();

    std::tuple<std::vector<glm::vec3>, std::vector<glm::vec3>> computeTangentBasis();

    std::string _texturePath;
    std::string _normalMapPath;

    GLuint _vaoHandle;
    GLuint _textureIds[2];
};

#endif //KMU_OGRE_HPP
